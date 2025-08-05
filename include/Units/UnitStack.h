#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy UnitStack:
  - Klasa jest obiektem reprezentującym oddział jednostki w grze. Posiada informacje o jednostce oraz jej ilości.
*/

#include "Battle/TileObject.h"
#include "Exceptions/ExpiredWeakPtrException.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "Units/Unit.h"

class UnitStack : public TileObject {
 private:
  CoordPair coords_in_battle_ = CoordPair( 0u, 0u );
  std::shared_ptr<const Unit> unit_;
  short morale_;
  short luck_;
  uint32_t size_;
  uint32_t current_health_;

  // void checkUnit() const;

 public:
  UnitStack( std::shared_ptr<const Unit> unit, uint32_t size );
  ~UnitStack() = default;
  void setCoordsInBattle( CoordPair new_coords );
  CoordPair getCoordsInBattle() const;
  uint32_t getSpeed() const;
  UnitLib::FactionType getFactionType() const;
  UnitLib::UnitType getUnitType() const;
  short getMorale() const;
  void setMorale( short new_morale );
  short getLuck() const;
  void setLuck( short new_luck );
  uint32_t getRange() const;
  uint32_t getSize() const;
  void setSize( uint32_t new_size );
  uint32_t getCurrentHealth() const;
  void setCurrentHealth( uint32_t new_health );
  double getEffectiveFightValue() const;
  std::shared_ptr<const Unit> getUnit() const;
  bool modifyCurrentHealth( int health_diff );
  uint32_t getHealthPool() const;
  bool getIfAlive() const;
  std::shared_ptr<UnitStack> copy() const;
  void die();
};