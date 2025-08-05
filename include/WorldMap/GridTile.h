#pragma once
// Autor: Tomasz Naszkowski

// #include <SFML/Graphics.hpp>

#include <memory>

#include "Miscellaneous/ProjectLib.h"

// #include "Characters/Character.h"
#include "WorldMap/MapObject.h"

class Character;

class GridTile {
 private:
  ProjectLib::Terrain terrain_;
  CoordPair coords_;
  std::shared_ptr<MapObject> object_present_ = nullptr;

 public:
  GridTile( ProjectLib::Terrain terrain );
  GridTile( ProjectLib::Terrain terrain, CoordPair coords );
  GridTile( ProjectLib::Terrain terrain, CoordPair coords, std::shared_ptr<MapObject> object );

  [[nodiscard]] ProjectLib::Terrain getTerrain() const;
  void setTerrain( ProjectLib::Terrain new_terrain );

  [[nodiscard]] CoordPair getCoords() const;
  void setCoords( CoordPair new_coords );

  [[nodiscard]] const std::shared_ptr<MapObject> getMapObject();
  void setMapObject( std::shared_ptr<MapObject> new_object );
  void deleteObject();

  bool getIfTraversable() const;
};