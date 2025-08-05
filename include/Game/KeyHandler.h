#pragma once

#include <SFML/Window.hpp>
#include <algorithm>
#include <deque>
#include <map>
#include <memory>
#include <set>

#include "Characters/Character.h"
#include "Exceptions/UnknownStateException.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Game/KeyboardInput.hpp"

// Movement OverworldOnly
class KeyHandler {
 private:
  bool is_buffered_input_ = false;
  std::vector<ProjectLib::CharacterMoveDirection> pending_moves_;  // Game extracts one move per frame
  std::deque<std::vector<sf::Keyboard::Key>> key_press_history_;
  std::set<sf::Keyboard::Key> held_keys_;
  std::shared_ptr<IKeyboardInput> input_;

  void processBufferedInput();
  ProjectLib::CharacterMoveDirection getMoveFromKeys( const std::vector<sf::Keyboard::Key>& key_vec );
  [[nodiscard]] bool isValidDiagonalPair( sf::Keyboard::Key first, sf::Keyboard::Key second ) const;
  [[nodiscard]] bool isDoublePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  [[nodiscard]] bool isSinglePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  // void convertKeyPressesToMoves();
  void removeEmptyFramesFromFront();
  [[nodiscard]] ProjectLib::FrameCount getBufferDurationAdjusted() const noexcept;

 public:
  KeyHandler();
  KeyHandler( bool is_buffered_input );
  KeyHandler( bool is_buffered_input, bool is_mock_input );

  // monitoring is split with getMove because there may be more than 1 move queued
  void debugMockInput( std::shared_ptr<MockKeyboardInput> input );
  void monitorKeyPresses();
  ProjectLib::CharacterMoveDirection getMove();
};