#include "Battle/BattleField.h"

[[nodiscard]] bool BattleField::getIfCoordsInBounds( const CoordPair& coords ) const noexcept {
  return coords.x_ < ProjectLib::MAP_WIDTH_BF && coords.y_ < ProjectLib::MAP_HEIGHT_BF;
}

BattleField::BattleField( std::shared_ptr<GridTile> background )
    : background_( background ) {
  for ( auto& col : battle_grid_ ) {
    for ( auto& tile_ptr : col ) {
      tile_ptr = nullptr;
    }
  }
};

BattleField::~BattleField() {
  // empty
}

std::vector<std::shared_ptr<Tile>> BattleField::getTileNeighbours( const CoordPair coords ) {
  const uint32_t x = coords.x_;
  const uint32_t y = coords.y_;

  const auto& directions = ( y % 2 == 0 ) ? ProjectLib::EVEN_DIRECTIONS_BATTLE : ProjectLib::ODD_DIRECTIONS_BATTLE;
  std::vector<std::shared_ptr<Tile>> neighbours;

  for ( const ShiftPair& delta : directions ) {
    int nx = (int)x + delta.dx_;
    int ny = (int)y + delta.dy_;

    if ( nx >= 0 && nx < static_cast<int>( ProjectLib::MAP_WIDTH_BF ) &&
         ny >= 0 && ny < static_cast<int>( ProjectLib::MAP_HEIGHT_BF ) ) {
      const auto& tile_ptr = getTileByProxy( CoordPair( uint32_t( nx ), uint32_t( ny ) ) );
      neighbours.push_back( tile_ptr );
    } else {
      neighbours.push_back( nullptr );
    }
  }

  return neighbours;
};

std::vector<std::shared_ptr<Tile>> BattleField::getTileNeighbours( const std::shared_ptr<Tile> tile ) {
  return getTileNeighbours( tile->getCoords() );
}

std::shared_ptr<Tile> BattleField::getTileByProxy( CoordPair coords ) {
  uint32_t x = coords.x_;
  uint32_t y = coords.y_;
  if ( !getIfCoordsInBounds( coords ) ) {
    throw CoordinateOutOfBoundsException( "Battlefield::getTileByProxy expected coordinates in bounds ([0,99],[0,99]) but instead got: " + coords.toStringExtended() );
  }
  if ( battle_grid_[x][y] == nullptr ) {
    battle_grid_[x][y] = std::make_shared<Tile>( coords );
  };
  return battle_grid_[x][y];
}

std::vector<CoordPair> BattleField::getCoordPairs( CoordPair coords ) {
  uint32_t x = coords.x_;
  uint32_t y = coords.y_;
  std::vector<CoordPair> tmp;
  if ( !( y % 2 ) ) {
    if ( y < static_cast<int>( ProjectLib::MAP_HEIGHT_BF ) - 1 && x < static_cast<int>( ProjectLib::MAP_WIDTH_BF ) - 1 ) tmp.push_back( CoordPair( x + 1, y + 1 ) );
    if ( x < static_cast<int>( ProjectLib::MAP_WIDTH_BF ) - 1 ) tmp.push_back( CoordPair( x + 1, y ) );
    if ( y > 0 && x < static_cast<int>( ProjectLib::MAP_WIDTH_BF ) - 1 ) tmp.push_back( CoordPair( x + 1, y - 1 ) );
    if ( y > 0 ) tmp.push_back( CoordPair( x, y - 1 ) );
    if ( x > 0 ) tmp.push_back( CoordPair( x - 1, y ) );
    if ( y < static_cast<int>( ProjectLib::MAP_HEIGHT_BF ) - 1 ) tmp.push_back( CoordPair( x, y + 1 ) );
  } else {
    if ( y < static_cast<int>( ProjectLib::MAP_HEIGHT_BF ) - 1 ) tmp.push_back( CoordPair( x, y + 1 ) );
    if ( x < static_cast<int>( ProjectLib::MAP_WIDTH_BF ) - 1 ) tmp.push_back( CoordPair( x + 1, y ) );
    if ( y > 0 ) tmp.push_back( CoordPair( x, y - 1 ) );
    if ( x > 0 && y > 0 ) tmp.push_back( CoordPair( x - 1, y - 1 ) );
    if ( x > 0 ) tmp.push_back( CoordPair( x - 1, y ) );
    if ( x > 0 && y < static_cast<int>( ProjectLib::MAP_HEIGHT_BF ) - 1 ) tmp.push_back( CoordPair( x - 1, y + 1 ) );
  }
  return tmp;
}

std::shared_ptr<GridTile> BattleField::getBackground() {
  return background_;
}

void BattleField::eraseEmptyTiles() {
  for ( auto& col : battle_grid_ ) {
    for ( auto& tile_ptr : col ) {
      if ( tile_ptr->getObject() == nullptr ) {
        tile_ptr.reset();
      }
    }
  }
}