#include <gtest/gtest.h>

#include "WorldMap/Building.h"
#include "WorldMap/GridTile.h"

TEST( GridTileTest, construtor1 ) {
  GridTile grid_tile = GridTile( ProjectLib::Terrain::DIRT );
  ASSERT_EQ( grid_tile.getCoords(), CoordPair( 0u, 0u ) );
  ASSERT_EQ( grid_tile.getTerrain(), ProjectLib::Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );
}

TEST( GridTileTest, constructor2 ) {
  GridTile grid_tile = GridTile( ProjectLib::Terrain::DIRT, CoordPair( 15u, 3u ) );
  ASSERT_EQ( grid_tile.getCoords(), CoordPair( 15u, 3u ) );
  ASSERT_EQ( grid_tile.getTerrain(), ProjectLib::Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );
}

TEST( GridTileTest, constructor3 ) {
  auto building = std::make_shared<Building>( CoordPair( 17u, 29u ), ProjectLib::BuildingType::BARRACKS );
  GridTile grid_tile = GridTile( ProjectLib::Terrain::DIRT, CoordPair( 15u, 3u ), building );
  ASSERT_EQ( grid_tile.getCoords(), CoordPair( 15u, 3u ) );
  ASSERT_EQ( grid_tile.getTerrain(), ProjectLib::Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), building );
}

TEST( GridTileTest, objectPresentModifications ) {
  GridTile grid_tile = GridTile( ProjectLib::Terrain::DIRT, CoordPair( 15u, 3u ) );
  ASSERT_EQ( grid_tile.getCoords(), CoordPair( 15u, 3u ) );
  ASSERT_EQ( grid_tile.getTerrain(), ProjectLib::Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );

  auto building = std::make_shared<Building>( CoordPair( 17u, 29u ), ProjectLib::BuildingType::BARRACKS );
  grid_tile.setMapObject( building );
  ASSERT_EQ( grid_tile.getMapObject(), building );
  ASSERT_FALSE( grid_tile.getIfTraversable() );

  grid_tile.deleteObject();
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );
  ASSERT_TRUE( grid_tile.getIfTraversable() );
}