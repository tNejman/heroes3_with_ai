#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Obstacle:
  - Klasa Obstacle odpowiada za przeszkody na polu bitwy.
  - Przeszkody są reprezentowane jako obiekty, które mogą być umieszczane na polu bitwy.
*/
#include "Battle/TileObject.h"
#include "Graphic/Printable.h"
#include "Miscellaneous/ProjectLib.h"

class BattleObstacle : public Printable, public TileObject {
 public:
  BattleObstacle( const ProjectLib::BattleObstacleType type );

  [[nodiscard]] ProjectLib::BattleObstacleType getType() const noexcept;
  sf::Texture& accept( Visitor& v ) const override;

 private:
  ProjectLib::BattleObstacleType type_;
};