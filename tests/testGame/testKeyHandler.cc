#include <gtest/gtest.h>

#include <SFML/Window/Keyboard.hpp>

#include "Game/KeyHandler.h"

TEST( KeyHandlerTest, mockInput ) {
  auto key_handler = std::make_shared<KeyHandler>( true, true );
  auto mock_input = std::make_shared<MockKeyboardInput>();

  // frame 0
  mock_input->set( { ProjectLib::W } );
  key_handler->debugMockInput( mock_input );
  key_handler->monitorKeyPresses();
  auto move_direction_frame0 = key_handler->getMove();
  ASSERT_EQ( ProjectLib::CharacterMoveDirection::NONE, move_direction_frame0 );

  // for frames 1,2,3,4,5
  mock_input->set( {} );
  key_handler->debugMockInput( mock_input );

  // frame 1 (buffer 1/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame1 = key_handler->getMove();
  ASSERT_EQ( ProjectLib::CharacterMoveDirection::NONE, move_direction_frame1 );

  // frame 2 (buffer 2/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame2 = key_handler->getMove();
  ASSERT_EQ( ProjectLib::CharacterMoveDirection::NONE, move_direction_frame2 );

  // frame 3 (buffer 3/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame3 = key_handler->getMove();
  ASSERT_EQ( ProjectLib::CharacterMoveDirection::NONE, move_direction_frame3 );

  // frame 4 (buffer 4/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame4 = key_handler->getMove();
  ASSERT_EQ( ProjectLib::CharacterMoveDirection::NONE, move_direction_frame4 );

  // frame 5 (buffer 5/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame5 = key_handler->getMove();
  ASSERT_EQ( ProjectLib::CharacterMoveDirection::UP, move_direction_frame5 );
}

// TEST( KeyHandlerTest, mockInput ) {
//   auto key_handler = std::make_shared<KeyHandler>( true, true );
//   // frame 1
//   // frame 2
//   // frame 3
//   // frame 4
//   // frame 5
//   // frame 6
//   // frame 7
//   // frame 8
//   // frame 9
//   // frame 10
// }