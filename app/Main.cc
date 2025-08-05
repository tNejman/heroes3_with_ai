#include <optional>

#include "Game/Game.h"
#include "LoadAndSaveTools/CharacterSaver.h"

int main() {
  auto castle = std::make_shared<FactionCastle>();
  auto pikeman = castle->getUnit( UnitLib::CastleUnitType::PIKEMAN );
  auto swordsman = castle->getUnit( UnitLib::CastleUnitType::SWORDSMAN );
  auto angel = castle->getUnit( UnitLib::CastleUnitType::ANGEL );
  auto archer = castle->getUnit( UnitLib::CastleUnitType::ARCHER );
  auto monk = castle->getUnit( UnitLib::CastleUnitType::MONK );

  auto unit_stack_1 = std::make_shared<UnitStack>( pikeman, 10 );
  auto unit_stack_3 = std::make_shared<UnitStack>( pikeman, 15 );
  auto unit_stack_4 = std::make_shared<UnitStack>( angel, 10 );

  auto unit_stack_2 = std::make_shared<UnitStack>( swordsman, 5 );
  auto unit_stack_5 = std::make_shared<UnitStack>( archer, 10 );

  auto unit_stack_6 = std::make_shared<UnitStack>( monk, 5 );
  auto unit_stack_7 = std::make_shared<UnitStack>( pikeman, 5 );

  std::vector<std::shared_ptr<Character>> characters;
  characters.push_back(
      std::make_shared<Character>( "fire_hero_down_right", CoordPair( 0u, 0u ), 10, 10, 10, 10, 50, 2, -3 ) );

  characters[0]->recruitUnitStack( unit_stack_1 );
  characters[0]->recruitUnitStack( unit_stack_3 );
  characters[0]->recruitUnitStack( unit_stack_4 );

  std::vector<std::shared_ptr<Character>> characters_2;
  characters_2.push_back(
      std::make_shared<Character>( "black_hero_white_horse_down_right", CoordPair( 0u, 0u ), 10, 10, 10, 10, 50, 2, -3 ) );
  characters_2.push_back(
      std::make_shared<Character>( "black_hero_white_horse_down_right", CoordPair( 0u, 0u ), 12, 15, 8, 2, 43, 5, -2 ) );

  characters_2[0]->setIfUser( false );
  characters_2[0]->recruitUnitStack( unit_stack_2 );
  characters_2[0]->recruitUnitStack( unit_stack_5 );
  characters_2[0]->setCoords( CoordPair( 10u, 10u ) );

  characters_2[1]->setIfUser( false );
  characters_2[1]->recruitUnitStack( unit_stack_6 );
  characters_2[1]->recruitUnitStack( unit_stack_7 );
  characters_2[1]->setCoords( CoordPair( 12u, 12u ) );

  std::vector<std::shared_ptr<Player>> players;
  players.push_back(
      // std::make_shared<Player>( std::move( characters ) ) );
      std::make_shared<Player>( characters ) );
  players.push_back(
      // std::make_shared<Player>( std::move( characters_2 ) ) );
      std::make_shared<Player>( characters ) );

  const uint32_t obstacle_count = 1'000u;
  std::vector<std::shared_ptr<OverworldObstacle>> obstacles;
  double step = std::sqrt( ( ProjectLib::WORLD_MAP_WIDTH * ProjectLib::WORLD_MAP_HEIGHT ) / static_cast<double>( obstacle_count ) );
  uint32_t count = 0;
  for ( double y = step / 2; y < ProjectLib::WORLD_MAP_HEIGHT && count < obstacle_count; y += step ) {
    for ( double x = step / 2; x < ProjectLib::WORLD_MAP_WIDTH && count < obstacle_count; x += step ) {
      auto x_loc = uint32_t( x );
      auto y_loc = uint32_t( y );
      // if ( int( x * y ) % 3 == 0 )
      // obstacles.push_back( std::make_shared<OverworldObstacle>( "AVLs11s0", CoordPair( x_loc, y_loc ) ) );
      if ( int( x * y ) % 2 == 0 )
        obstacles.push_back( std::make_shared<OverworldObstacle>( "AVLtRo06", CoordPair( x_loc, y_loc ) ) );
      else
        obstacles.push_back( std::make_shared<OverworldObstacle>( "AVLswt15", CoordPair( x_loc, y_loc ) ) );
    }
  }

  std::shared_ptr<Game> game = nullptr;
  try {
    game = std::make_shared<Game>( players, true );
  } catch ( const std::exception& e ) {
    std::cout << e.what() << std::endl;
    return -1;
  }
  game->mapLoadObstacles( obstacles );

  std::ofstream out( "CharacterSave2.txt" );
  CharacterSaver character_saver = CharacterSaver( "CharacterSave2.txt", characters[0] );
  character_saver.save();
  CharacterSaver character_saver2 = CharacterSaver( "CharacterSave2.txt", characters_2[0] );
  character_saver2.save();
  CharacterSaver character_saver3 = CharacterSaver( "CharacterSave2.txt", characters_2[1] );
  character_saver3.save();

  std::shared_ptr<sf::RenderWindow> window = game->getRenderWindow();
  window->setSize( sf::Vector2u( SpriteNumericLib::WINDOW_WIDTH, SpriteNumericLib::WINDOW_HEIGHT ) );
  while ( window->isOpen() ) {
    if ( window->getSize() != sf::Vector2u( SpriteNumericLib::WINDOW_WIDTH, SpriteNumericLib::WINDOW_HEIGHT ) ) {
      window->setSize( { SpriteNumericLib::WINDOW_WIDTH, SpriteNumericLib::WINDOW_HEIGHT } );
    }
    // sf::Time start_time = clock.getElapsedTime();
    while ( std::optional event = window->pollEvent() ) {
      if ( event->is<sf::Event::Closed>() ||
           ( event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape ) ) {
        window->close();
        return 0;
      } else if ( event->is<sf::Event::MouseButtonPressed>() &&
                  event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left ) {
        int mouse_x = event->getIf<sf::Event::MouseButtonPressed>()->position.x;
        int mouse_y = event->getIf<sf::Event::MouseButtonPressed>()->position.y;
        game->setMouseCoords( mouse_x, mouse_y );
      }
    }
    window->clear( sf::Color( 4 ) );
    game->performGameLoopIteration();
    // if ( game->getFramesCountSinceStart() == 4 ) {
    //   std::chrono::milliseconds timespan( 5'000 );
    //   std::this_thread::sleep_for( timespan );
    // }
    window->display();
  }
};