#pragma once
// Autor: Tomasz Nejman i Naszkowski
/* Zawartość klasy Unit:
  - Klasa Unit odpowiada za jednostki w grze.
  - Zawiera metody do zarządzania statystykami jednostek, ich poziomem, obrażeniami i innymi parametrami.
*/
// #include <SFML/Graphics.hpp>

#include <stdint.h>

#include <iostream>
#include <string>

#include "Battle/TileObject.h"
#include "Exceptions/ExpiredWeakPtrException.hpp"
#include "Exceptions/InvalidUnitNameException.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Graphic/Printable.h"
#include "Miscellaneous/ProjectLib.h"
#include "Miscellaneous/UnitLib.h"
#include "Units/Faction.hpp"

class Faction;

class Unit : public TileObject, public Printable {
 protected:
  const std::shared_ptr<const UnitLib::UnitData> unit_data_;

 public:
  Unit( const std::shared_ptr<const UnitLib::UnitData> unit_data ) noexcept;
  ~Unit() = default;

  [[nodiscard]] sf::Texture& accept( Visitor& v ) const override;
  [[nodiscard]] UnitLib::UnitType getUnitType() const noexcept;
  [[nodiscard]] UnitLib::FactionType getFactionType() const noexcept;
  [[nodiscard]] uint32_t getLevel() const noexcept;
  [[nodiscard]] uint32_t getAttack() const noexcept;
  [[nodiscard]] uint32_t getDefense() const noexcept;
  [[nodiscard]] uint32_t getMinDamage() const noexcept;
  [[nodiscard]] uint32_t getMaxDamage() const noexcept;
  [[nodiscard]] uint32_t getHealth() const noexcept;
  [[nodiscard]] uint32_t getSpeed() const noexcept;
  [[nodiscard]] uint32_t getCounterAttack() const noexcept;
  [[nodiscard]] uint32_t getGrowth() const noexcept;
  [[nodiscard]] uint32_t getCost() const noexcept;
  [[nodiscard]] uint32_t getDmg() const noexcept;
  [[nodiscard]] virtual uint32_t getRange() const noexcept;
  [[nodiscard]] uint32_t getFightValue() const noexcept;
};