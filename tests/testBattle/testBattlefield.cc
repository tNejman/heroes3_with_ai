#include <gtest/gtest.h>

#include <array>
#include <memory>

#include "Battle/BattleField.h"
#include "Battle/Tile.h"
#include "Battle/TileObject.h"

TEST( LayoutTest, check_up_right_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF - 1; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::UR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::EVEN_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::UR] ) );
    };
  }
  // top row
  const uint32_t max_y = ProjectLib::MAP_HEIGHT_BF - 1;
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, max_y ) )[ProjectLib::BATTLE_DIRECTIONS::UR],
               nullptr );
  }
  // right column
  const uint32_t max_x = ProjectLib::MAP_WIDTH_BF - 1;
  for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::UR],
               nullptr );
  }
}  // done

TEST( LayoutTest, check_right_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF; ++y ) {
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::R],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::EVEN_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::R] ) );
    }
  }
  // right column
  const uint32_t max_x = ProjectLib::MAP_WIDTH_BF - 1;
  for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::R], nullptr );
  }
}  // done

TEST( LayoutTest, check_down_right_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 2; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::DR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::EVEN_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::DR] ) );
    }
  }
  // max right col
  const uint32_t max_x = ProjectLib::MAP_WIDTH_BF - 1;
  for ( uint32_t y = 2; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::DR],
               nullptr );
  }
  // max bottom row
  const uint32_t min_y = 0u;
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF - 1; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, min_y ) )[ProjectLib::BATTLE_DIRECTIONS::DR],
               nullptr );
  }
}  // done

TEST( LayoutTest, check_down_left_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 2; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::DL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::EVEN_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::DL] ) );
    }
  }
  // max bottom row
  const uint32_t min_y = 0u;
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, min_y ) )[ProjectLib::BATTLE_DIRECTIONS::DL], nullptr );
  }
}  // done

TEST( LayoutTest, check_left_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 1; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::L],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::EVEN_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::L] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::L],
               nullptr );
  }
}  // done

TEST( LayoutTest, check_up_left_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF - 1; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::UL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::EVEN_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::UL] ) );
    }
  }
  const uint32_t max_y = ProjectLib::MAP_HEIGHT_BF - 1;
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, max_y ) )[ProjectLib::BATTLE_DIRECTIONS::UL],
               nullptr );
  }
}  // done

TEST( LayoutTest, check_up_right_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::UR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::ODD_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::UR] ) );
    }
  }
}  // done

TEST( LayoutTest, check_right_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::R],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::ODD_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::R] ) );
    }
  }
  const uint32_t max_x = ProjectLib::MAP_WIDTH_BF - 1;
  for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::R],
               nullptr );
  }
}  // done

TEST( LayoutTest, check_down_right_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::DR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::ODD_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::DR] ) );
    }
  }
}  // done

TEST( LayoutTest, check_down_left_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 1; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::DL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::ODD_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::DL] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::DL],
               nullptr );
  }
}  // done

TEST( LayoutTest, check_left_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 1; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::L],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::ODD_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::L] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::L],
               nullptr );
  }
}  // done

TEST( LayoutTest, check_up_left_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( ProjectLib::Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 1; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[ProjectLib::BATTLE_DIRECTIONS::UL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ProjectLib::ODD_DIRECTIONS_BATTLE[ProjectLib::BATTLE_DIRECTIONS::UL] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 1; y < ProjectLib::MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= ProjectLib::MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[ProjectLib::BATTLE_DIRECTIONS::UL],
               nullptr );
  }
}

// WIP
// TEST( LayoutConnection, checkingIfConnected ) {
//   std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>();
//   ASSERT_EQ(2,battlefield->ifConnected(0,0,2,1));
// }

// TEST( LayoutConnection, checkingIfConnectedfar ) {
//   std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>();
//   ASSERT_EQ(19,battlefield->ifConnected(0,0,14,10));
// }