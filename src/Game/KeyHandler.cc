#include "Game/KeyHandler.h"

void KeyHandler::processBufferedInput() {
  removeEmptyFramesFromFront();
  if ( key_press_history_.empty() ) {
    return;
  }
  auto &current_frame_keys = key_press_history_.front();

  if ( isDoublePress( current_frame_keys ) ) {
    // double press is not buffered or ambiguous => transform instantly
    pending_moves_.push_back( getMoveFromKeys( current_frame_keys ) );
    key_press_history_.pop_front();
    return;

  } else if ( isSinglePress( current_frame_keys ) ) {
    // searching for a match to combine to a double-press
    sf::Keyboard::Key key_to_be_matched = current_frame_keys[0];
    int matched_idx = -1;
    bool force_solo = false;
    bool incompatible_pair = false;

    ProjectLib::FrameCount max_frames_forward = getBufferDurationAdjusted();

    for ( ProjectLib::FrameCount i = 1; i <= max_frames_forward; ++i ) {
      std::cout << "Checking " << i << "th frame forward" << std::endl;
      auto &ith_frame_keys = key_press_history_[i];

      if ( isDoublePress( ith_frame_keys ) ) {
        // single press (current) followed by double (i-th); force execute and skip waiting
        force_solo = true;
        break;

      } else if ( isSinglePress( ith_frame_keys ) && isValidDiagonalPair( key_to_be_matched, ith_frame_keys[0] ) ) {
        matched_idx = static_cast<int>( i );
        break;

      } else if ( isSinglePress( ith_frame_keys ) && !isValidDiagonalPair( key_to_be_matched, ith_frame_keys[0] ) ) {
        incompatible_pair = true;
        break;

      } else {
        // empty frame
        continue;
      }
    }
    if ( matched_idx != -1 ) {
      std::vector<sf::Keyboard::Key> matched_key_pair{
          current_frame_keys[0],
          key_press_history_[matched_idx][0] };

      current_frame_keys.clear();  // key_press_history_[0]
      key_press_history_[matched_idx].clear();

      pending_moves_.push_back( getMoveFromKeys( matched_key_pair ) );
      // key_press_history_.pop_front();

    } else if ( force_solo || incompatible_pair || ( is_buffered_input_ && max_frames_forward == ProjectLib::KEY_BUFFER_DURATION ) ) {
      // 1) force_solo means next press was a double and no pair can be created
      // 2) incompatible_pair means a next key was an incompatible key and no pair can be created
      // 3) ( is_buffered_input_ && max_frames_forward == KEY_BUFFER_DURATION ) all next frames were empty and buffer is sufficiently big
      // all three cases mean that we can execute a single move
      pending_moves_.push_back( getMoveFromKeys( current_frame_keys ) );
      key_press_history_.pop_front();

      if ( is_buffered_input_ && max_frames_forward == ProjectLib::KEY_BUFFER_DURATION ) {
        std::cout << "5 frames passed, executing" << std::endl;
      }

    } else if ( is_buffered_input_ && max_frames_forward < ProjectLib::KEY_BUFFER_DURATION ) {
      // not eligible for override or execution; wait for more frames
      return;
    } else {
      throw UnknownStateException( "KeyHandler::processBufferedInput -> SinglePress registered (and buffer sufficiently big) but no matching or overriding operation performed " );
    }

  } else {
    throw UnknownStateException( "KeyHandler::processBufferedInput -> first key was neither a single nor a double press" );
  }
}

ProjectLib::CharacterMoveDirection KeyHandler::getMoveFromKeys( const std::vector<sf::Keyboard::Key> &key_vec ) {
  int dx = 0;
  int dy = 0;
  for ( auto &key : key_vec ) {
    switch ( key ) {
      case ProjectLib::W:
        dy += 1;
        break;
      case ProjectLib::S:
        dy -= 1;
        break;
      case ProjectLib::A:
        dx -= 1;
        break;
      case ProjectLib::D:
        dx += 1;
        break;
      default:
        throw UnknownStateException( "KeyHandler::getMoveFromKey -> Unexpected key passed to movement control" );
    };
  }
  ShiftPair shift = ShiftPair( dx, dy );

  auto itr = std::find( ProjectLib::WORLD_MAP_DIRECTIONS.begin(), ProjectLib::WORLD_MAP_DIRECTIONS.end(), shift );
  if ( itr == ProjectLib::WORLD_MAP_DIRECTIONS.end() ) {
    return ProjectLib::CharacterMoveDirection::NONE;
  }
  auto dist = std::distance( ProjectLib::WORLD_MAP_DIRECTIONS.begin(), itr );
  assert( dist <= 7u );
  return static_cast<ProjectLib::CharacterMoveDirection>( dist );
}

bool KeyHandler::isValidDiagonalPair( sf::Keyboard::Key first, sf::Keyboard::Key second ) const {
  auto it = ProjectLib::VALID_DIAGONAL_MOVE_COMP.find( first );
  if ( it == ProjectLib::VALID_DIAGONAL_MOVE_COMP.end() ) return false;

  return second == it->second[0] || second == it->second[1];
}

bool KeyHandler::isDoublePress( const std::vector<sf::Keyboard::Key> &keys ) const {
  return keys.size() == 2;
}

bool KeyHandler::isSinglePress( const std::vector<sf::Keyboard::Key> &keys ) const {
  return keys.size() == 1;
}

void KeyHandler::removeEmptyFramesFromFront() {
  while ( key_press_history_.size() > 0 && key_press_history_.front().size() == 0 ) {
    key_press_history_.pop_front();
  }
}

ProjectLib::FrameCount KeyHandler::getBufferDurationAdjusted() const noexcept {
  if ( is_buffered_input_ ) {
    // size - 1, because the 0idx is the reference point for buffer
    return std::min<ProjectLib::FrameCount>( ProjectLib::KEY_BUFFER_DURATION, key_press_history_.size() - 1 );
  } else {
    return 1;
  }
}

KeyHandler::KeyHandler()
    : input_( std::make_shared<RealKeyboardInput>() ) {};

KeyHandler::KeyHandler( bool is_buffered_input )
    : is_buffered_input_( is_buffered_input ), input_( std::make_shared<RealKeyboardInput>() ) {};

KeyHandler::KeyHandler( bool is_buffered_input, bool is_mock_input )
    : is_buffered_input_( is_buffered_input ), input_( std::make_shared<RealKeyboardInput>() ) {
  if ( is_mock_input ) {
    input_ = std::make_shared<MockKeyboardInput>();
  }
}

void KeyHandler::debugMockInput( std::shared_ptr<MockKeyboardInput> input ) {
  input_ = input;
}

void KeyHandler::monitorKeyPresses() {
  std::vector<sf::Keyboard::Key> keys_this_frame;
  std::set<sf::Keyboard::Key> currently_pressed = input_->pressedNow();

  for ( auto &key : ProjectLib::MOVEMENT_KEYS ) {
    if ( currently_pressed.find( key ) != currently_pressed.end() ) {
      if ( held_keys_.count( key ) == 0 && keys_this_frame.size() < 2 ) {
        keys_this_frame.push_back( key );
      }
    }
  }
  held_keys_ = currently_pressed;
  key_press_history_.push_back( keys_this_frame );
}

ProjectLib::CharacterMoveDirection KeyHandler::getMove() {
  // convertKeyPressesToMoves();
  processBufferedInput();

  if ( pending_moves_.empty() ) {
    return ProjectLib::CharacterMoveDirection::NONE;
  }
  auto ret_move = pending_moves_.front();
  pending_moves_.erase( pending_moves_.begin() );
  // std::cout << "DEBUG: KeyHandler returns move: dx=" << ret_move.dx_ << " dy=" << ret_move.dy_ << std::endl;
  return ret_move;
}