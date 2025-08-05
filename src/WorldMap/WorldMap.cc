#include "WorldMap/WorldMap.h"

void WorldMap::loadGrid( std::array<std::array<int, ProjectLib::WORLD_MAP_HEIGHT>, ProjectLib::WORLD_MAP_WIDTH>& new_grid ) {
  if ( is_initialized_ ) {
    throw UnknownStateException( "WorldMap::loadGrid -> is called again but WorldMap is already initialized" );
  }
  for ( uint32_t col = 0; col < ProjectLib::WORLD_MAP_WIDTH; ++col ) {
    for ( uint32_t row = 0; row < ProjectLib::WORLD_MAP_HEIGHT; ++row ) {
      auto terrain = static_cast<ProjectLib::Terrain>( new_grid[col][row] );
      grid_[col][row].reset();
      grid_[col][row] = std::make_shared<GridTile>( terrain, CoordPair( col, row ) );
      assert( grid_[col][row] != nullptr && "WorldMap::loadGrid -> GridTile pointer is null after initialization" );
    }
  }
  is_initialized_ = true;
}

bool WorldMap::getIfCoordsInBounds( CoordPair coords ) const {
  return ( coords.x_ < ProjectLib::WORLD_MAP_WIDTH && coords.y_ < ProjectLib::WORLD_MAP_HEIGHT );
}

bool WorldMap::getIfCoordsInBounds( CoordPair coords, ShiftPair shift ) const {
  CoordPair new_coords = coords + shift;
  return getIfCoordsInBounds( new_coords );
}

WorldMap::WorldMap( std::array<std::array<int, ProjectLib::WORLD_MAP_HEIGHT>, ProjectLib::WORLD_MAP_WIDTH>& new_grid ) {
  this->loadGrid( new_grid );
}

void WorldMap::loadObstacles( std::vector<std::shared_ptr<OverworldObstacle>>& obstacles ) {
  for ( auto& obstacle : obstacles ) {
    try {
      setMapObject( obstacle->getCoords(), obstacle );
    } catch ( const std::exception& e ) {
      std::cout << e.what() << std::endl;
    }
  }
}

void WorldMap::setMapObject( CoordPair coords, std::shared_ptr<MapObject> object ) {
  if ( !getIfCoordsInBounds( coords ) ) {
    throw CoordinateOutOfBoundsException( "WorldMap::setMapObject -> Cannot set object out of bounds: " + coords.toString() );
  }
  auto tile = this->getTile( coords );
  tile->setMapObject( object );
}

void WorldMap::moveMapObject( CoordPair old_coords, CoordPair new_coords ) {
  if ( old_coords == new_coords ) {
    // std::cout << "DEBUG: moveMapObj old==new; xo=" << old_coords.x_ << " yo=" << old_coords.y_
    //  << " xn=" << new_coords.x_ << " yn=" << new_coords.y_ << std::endl;
    return;
  }
  if ( !getIfCoordsInBounds( old_coords ) ) {
    throw CoordinateOutOfBoundsException( "WorldMap::moveMapObject -> Origin out of bounds: " + old_coords.toString() );
  }
  if ( !getIfCoordsInBounds( new_coords ) ) {
    throw CoordinateOutOfBoundsException( "WorldMap::moveMapObject -> Destination out of bounds: " + new_coords.toString() );
  }
  auto old_tile = this->getTile( old_coords );
  auto new_tile = this->getTile( new_coords );
  auto map_obj_src = old_tile->getMapObject();
  auto map_obj_dest = new_tile->getMapObject();

  if ( !map_obj_src ) {
    throw InvalidMapMoveException( "WorldMap::moveMapObject -> Tried moving object from an empty tile" + old_coords.toString() );
  }
  if ( map_obj_dest ) {
    throw InvalidMapMoveException( "WorldMap::moveMapObject -> Tried moving object onto an occupied tile" + new_coords.toString() );
  }
  new_tile->setMapObject( map_obj_src );
  old_tile->deleteObject();
  map_obj_src->setCoords( new_coords );

  // DEBUG SECTION
  // int diff_x = new_coords.x_ - old_coords.x_;
  // int diff_y = new_coords.y_ - old_coords.y_;
  // if (std::abs(diff_x) + std::abs(diff_y) == 2) {
  //     std::cout << "DEBUG: Diagonal ";
  // } else {
  //     std::cout << "DEBUG: Cardinal ";
  // }
  // std::cout << "move. New coords: x=" << new_coords.x_ << " y=" << new_coords.y_ << std::endl;
}

void WorldMap::moveMapObject( CoordPair old_coords, ShiftPair shift ) {
  CoordPair new_coords = old_coords;
  new_coords += shift;
  this->moveMapObject( old_coords, new_coords );
}

std::shared_ptr<GridTile> WorldMap::getTile( const CoordPair coords ) {
  if ( !getIfCoordsInBounds( coords ) )
    throw CoordinateOutOfBoundsException( "WorldMap::getTile -> Coordinates out of bounds: " + coords.toString() );
  auto tile = grid_[coords.x_][coords.y_];
  // tile is never null, because we always initialize the grid with GridTile objects
  return tile;
}

// std::array<std::array<std::shared_ptr<GridTile>, WORLD_MAP_WIDTH>, WORLD_MAP_HEIGHT> WorldMap::getGridTransposed() {
//     std::array<std::array<std::shared_ptr<GridTile>, WORLD_MAP_WIDTH>, WORLD_MAP_HEIGHT> grid_transposed;
// }
// std::array<std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>& WorldMap::getGrid() const {

// }
// std::array<std::unique_ptr<GridTile>, WORLD_MAP_WIDTH>& WorldMap::getRow( const uint32_t row_num ) const {

// }
// std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>& WorldMap::getColumn( const uint32_t column_num ) const {

// }

// std::shared_ptr<MapObject>& WorldMap::getObject( const CoordPair coords ) const {

// }
// std::shared_ptr<MapObject>& WorldMap::getObject( const std::unique_ptr<GridTile>& base_tile ) const {

// }

// CoordPair WorldMap::getTileCoords( const std::unique_ptr<GridTile>& tile ) const {
//     for (int i = 0; i < WORLD_MAP_WIDTH; ++i) {
//         for (int j = 0; j < WORLD_MAP_HEIGHT; ++j) {
//             if (grid_[i][j] == tile) {
//                 return {i, j};
//             }
//         }
//     }
//     throw TileNotFoundException("Tile not found.");
// }
// CoordPair WorldMap::getObjectCoords( const std::unique_ptr<MapObject>& object ) const {
//     for (int i = 0; i < WORLD_MAP_WIDTH; ++i) {
//         for (int j = 0; j < WORLD_MAP_HEIGHT; ++j) {
//             if (grid_[i][j]->getMapObject() == object) {
//                 return {i, j};
//             }
//         }
//     }
//     throw ObjectNotFoundException("Object not found.");
// }
// CoordPair WorldMap::getCharacterCoords( const std::string& character_name ) const {
//     for (const std::shared_ptr<Character>& c :  characters_) {
//         if (c->getName() == character_name)
//             return c->getCoords();
//     }
//     throw ObjectNotFoundException("Character not found.");
// }
// CoordPair WorldMap::getBuildingCoords( const std::string& building_name ) const {
//     for (int i = 0; i < WORLD_MAP_WIDTH; ++i) {
//         for (int j = 0; j < WORLD_MAP_HEIGHT; ++j) {
//             if (grid_[i][j]->getMapObject()) {
//             }
//         }
//     }
// }

// std::vector<std::unique_ptr<Character>>& WorldMap::getCharacters() const {
//     return this->characters_;
// }
// std::vector<std::unique_ptr<Building>>& WorldMap::getBuildings() const {

// }

// void WorldMap::setGrid( std::array<std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>& new_grid ) {

// }
// void WorldMap::setRow( std::array<std::unique_ptr<GridTile>, WORLD_MAP_WIDTH>& new_row ) {

// }
// void WorldMap::setColumn( std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>& new_column ) {

// }

// void WorldMap::setTile( std::unique_ptr<GridTile>& tile, const CoordPair where ) {`
//     grid_[where.first][where.second] = std::move(tile);
// }
// void WorldMap::swapTiles( const CoordPair coords_a, const CoordPair coords_b ) {
//     std::unique_ptr<GridTile> temp = std::move(grid_[coords_a.first][coords_a.second]);
//     grid_[coords_a.first][coords_a.second] = std::move(grid_[coords_b.first][coords_b.second]);
//     grid_[coords_b.first][coords_b.second] = std::move(temp);
// }

// void WorldMap::setMapObject( std::unique_ptr<MapObject>& map_object, std::unique_ptr<GridTile>& grid_tile ) {
//     grid_tile->setMapObject(map_object);
// }
// void WorldMap::setMapObject( std::unique_ptr<MapObject>& map_object, const CoordPair coords ) {
//     grid_[coords.first][coords.second]->setMapObject(map_object);
// }
// void WorldMap::swapMapObjects( const CoordPair coords_a, const CoordPair coords_b ) {
//     std::unique_ptr<MapObject> temp = std::move(grid_[coords_a.first][coords_a.second]->getMapObject());
//     grid_[coords_a.first][coords_a.second]->setMapObject(grid_[coords_b.first][coords_b.second]->getMapObject());
//     grid_[coords_b.first][coords_b.second]->setMapObject(temp);
// }

// void WorldMap::addCharacter( const std::shared_ptr<Character>& character ) {
//     characters_.push_back(std::make_shared<Character>(character));
// }
// void WorldMap::removeCharacter( const std::string& character_name ) {
//     // TODO also remove from map
//     for (auto i = characters_.begin(); i != characters_.end(); ++i) {
//         if((*i)->getName() == character_name) {
//             characters_.erase(i);
//             return;
//         }
//     }
//     throw ObjectNotFoundException("Character not found.");
// }
// void WorldMap::removeCharacters() {
//     characters_.empty();
// }

// void WorldMap::addBuilding( const std::unique_ptr<Building>& building ) {
//     buildings_.push_back(std::make_shared<Building>(building));
// }
// void WorldMap::removeBuilding( const std::string& building_name ) {
//     // TODO also remove from map
//     for (auto i = buildings_.begin(); i != buildings_.end(); ++i) {
//         if( (*i)->getName() == building_name) {
//             buildings_.erase(i);
//             return;
//         }
//     }
//     throw ObjectNotFoundException("Building not found");
// }
// void WorldMap::removeBuildings() {
//     buildings_.empty();
// }
