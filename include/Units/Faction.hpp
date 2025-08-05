#pragma once
// Autor: Tomasz Nejman
/* zawartość klasy Faction:
  - Klasa Faction odpowiada za zarządzanie frakcjami w grze.
  - Zawiera metody do tworzenia jednostek, zarządzania dostępnością jednostek i ich typami.
*/
#include <array>
#include <memory>

#include "Miscellaneous/UnitLib.h"
#include "Units/Unit.h"

/**
 * @Warning
 * Inheritance twice is purposeful here.
 * Faction cannot start as a template class because a handle
 * to complete interface is required.
 */
class Faction : public std::enable_shared_from_this<Faction> {
 private:
  UnitLib::FactionAttitude faction_attitude_;

 protected:
  std::array<std::shared_ptr<const Unit>, 7> available_units_ = {
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
  int faction_type_;
  std::weak_ptr<Faction> getWeakPtr() {
    return shared_from_this();
  }

 public:
  Faction( UnitLib::FactionAttitude faction_attitude ) : faction_attitude_( faction_attitude ) {}
  virtual ~Faction() = default;
  [[nodiscard]] UnitLib::FactionAttitude getFactionAttitude() const { return this->faction_attitude_; }
  [[nodiscard]] virtual UnitLib::FactionType getFactionType() const = 0;
};

template <typename FactionUnitEnum>
class GenericFaction : public Faction {
 protected:
  const std::map<FactionUnitEnum, const std::shared_ptr<const UnitLib::UnitData>>& UNITS_PRESET_;

  std::shared_ptr<const Unit> createUnit( FactionUnitEnum faction_unit_type ) {
    const std::shared_ptr<const UnitLib::UnitData> unit_data = UNITS_PRESET_.find( faction_unit_type )->second;
    return std::make_shared<Unit>( unit_data );
  };

 public:
  GenericFaction( UnitLib::FactionAttitude faction_attitude, const std::map<FactionUnitEnum, const std::shared_ptr<const UnitLib::UnitData>>& units_preset )
      : Faction::Faction( faction_attitude ), UNITS_PRESET_( units_preset ) {};
  virtual ~GenericFaction() = default;

  const std::shared_ptr<const Unit> getUnit( FactionUnitEnum faction_unit_type ) {
    const auto unit_idx = uint32_t( faction_unit_type );
    if ( available_units_[unit_idx] == nullptr ) {
      available_units_[unit_idx] = createUnit( faction_unit_type );
    }
    return available_units_[unit_idx];
  }
  [[nodiscard]] virtual UnitLib::FactionType getFactionType() const = 0;
};

class FactionConflux : public GenericFaction<UnitLib::ConfluxUnitType> {
 public:
  FactionConflux() : GenericFaction( UnitLib::FactionAttitude::NEUTRAL, UnitLib::UNITS_PRESET_CONFLUX ) {};
  ~FactionConflux() override = default;
  [[nodiscard]] UnitLib::FactionType getFactionType() const override { return UnitLib::FactionType::CONFLUX; }
};

class FactionCastle : public GenericFaction<UnitLib::CastleUnitType> {
 public:
  FactionCastle() : GenericFaction( UnitLib::FactionAttitude::GOOD, UnitLib::UNITS_PRESET_CASTLE ) {};
  ~FactionCastle() override = default;
  [[nodiscard]] UnitLib::FactionType getFactionType() const override { return UnitLib::FactionType::CASTLE; }
};