#include "WorldMap/Building.h"

Building::Building( CoordPair coords, ProjectLib::BuildingType type )
    : MapObject( coords ), type_( type ) {}

sf::Texture& Building::accept( Visitor& v ) const {
  return v.visit( *this );
}

ProjectLib::BuildingType Building::getType() const noexcept {
  return type_;
}