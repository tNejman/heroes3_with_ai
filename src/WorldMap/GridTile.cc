#include "WorldMap/GridTile.h"

GridTile::GridTile( ProjectLib::Terrain terrain )
    : terrain_( terrain ), coords_( CoordPair( 0u, 0u ) ) {}

GridTile::GridTile( ProjectLib::Terrain terrain, CoordPair coords )
    : terrain_( terrain ), coords_( coords ) {}

GridTile::GridTile( ProjectLib::Terrain terrain, CoordPair coords, std::shared_ptr<MapObject> object )
    : terrain_( terrain ), coords_( coords ), object_present_( object ) {
  object_present_->setCoords( this->coords_ );
}

ProjectLib::Terrain GridTile::getTerrain() const {
  return this->terrain_;
}

void GridTile::setTerrain( ProjectLib::Terrain new_terrain ) {
  this->terrain_ = new_terrain;
}

CoordPair GridTile::getCoords() const {
  return this->coords_;
}

void GridTile::setCoords( CoordPair new_coords ) {
  this->coords_ = new_coords;
}

const std::shared_ptr<MapObject> GridTile::getMapObject() {
  return this->object_present_;
}

void GridTile::setMapObject( std::shared_ptr<MapObject> new_object ) {
  this->object_present_ = new_object;
  this->object_present_->setCoords( this->coords_ );
}

void GridTile::deleteObject() {
  this->object_present_.reset();
}

bool GridTile::getIfTraversable() const {
  return this->object_present_ == nullptr;
}