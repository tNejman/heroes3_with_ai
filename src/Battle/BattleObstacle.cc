#include "Battle/BattleObstacle.h"

BattleObstacle::BattleObstacle( const ProjectLib::BattleObstacleType type )
    : Printable(), TileObject( false ), type_( type ) {}

ProjectLib::BattleObstacleType BattleObstacle::getType() const noexcept {
  return type_;
}

sf::Texture& BattleObstacle::accept( Visitor& v ) const {
  return v.visit( *this );
}