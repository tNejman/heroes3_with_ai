#pragma once
// Autor: Tomasz Nejman

// #include <SFML/Graphics.hpp>

#include <string>

#include "Graphic/Printable.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/MapObject.h"

class Building : public MapObject {
 private:
  const ProjectLib::BuildingType type_;

 public:
  Building( CoordPair coords, ProjectLib::BuildingType type );
  ~Building() = default;

  [[nodiscard]] sf::Texture& accept( Visitor& v ) const override;
  [[nodiscard]] ProjectLib::BuildingType getType() const noexcept;
};