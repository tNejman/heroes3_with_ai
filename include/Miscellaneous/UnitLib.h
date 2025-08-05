#pragma once
// Autor: Tomasz Nejman i Tomasz Naszkowski
/* Zawartość klasy unitlib:
    - klasa pozwala na przechowywanie jednostek
    - klasa pozwala na tworzenie jednostek
    - klasa pozwala na dodawanie jednostek do armii
*/
#include <stdint.h>

#include <array>
#include <map>
#include <memory>
#include <string>

namespace UnitLib {

enum class FactionAttitude { EVIL,
                             NEUTRAL,
                             GOOD };

enum class FactionType : int {
  NONE = -1,
  CONFLUX,
  CASTLE
};

enum class WarMachineUnitType : int {
  BALLISTA = 0,
  AMMO_CART = 1,
  FIRST_AID_TENT = 2,
  CATAPULT = 3
};

enum class ConfluxUnitType : int {
  PIXIE = 0,
  AIR_ELEMENTAL = 1,
  WATER_ELEMENTAL = 2,
  FIRE_ELEMENTAL = 3,
  EARTH_ELEMENTAL = 4,
  PSYCHIC_ELEMENTAL = 5,
  FIREBIRD = 6
};

enum class CastleUnitType : int {
  PIKEMAN = 0,
  ARCHER = 1,
  GRIFFIN = 2,
  SWORDSMAN = 3,
  MONK = 4,
  CAVALIER = 5,
  ANGEL = 6
};

constexpr uint32_t MELEE_UNIT_RANGE = 1;

using UnitType = std::variant<UnitLib::WarMachineUnitType,
                              UnitLib::ConfluxUnitType,
                              UnitLib::CastleUnitType>;

template <class... Ts>
struct UnitTypeForwardLambdaCombiner : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
UnitTypeForwardLambdaCombiner( Ts... ) -> UnitTypeForwardLambdaCombiner<Ts...>;

class UnitData {
 public:
  const UnitType unit_type_;
  const FactionType faction_type_;
  const uint32_t level_;
  const uint32_t attack_;
  const uint32_t defense_;
  const uint32_t min_damage_;
  const uint32_t max_damage_;
  const uint32_t health_;
  const uint32_t speed_;
  const uint32_t counter_attack_;
  const uint32_t growth_;
  const uint32_t cost_;
  const uint32_t fight_value_;

  UnitData(
      const UnitType unit_type,
      const FactionType faction_type,
      const uint32_t level,
      const uint32_t attack,
      const uint32_t defense,
      const uint32_t min_damage,
      const uint32_t max_damage,
      const uint32_t health,
      const uint32_t speed,
      const uint32_t counter_attack,
      const uint32_t growth,
      const uint32_t cost,
      const uint32_t fight_value ) : unit_type_( unit_type ),
                                     faction_type_( faction_type ),
                                     level_( level ),
                                     attack_( attack ),
                                     defense_( defense ),
                                     min_damage_( min_damage ),
                                     max_damage_( max_damage ),
                                     health_( health ),
                                     speed_( speed ),
                                     counter_attack_( counter_attack ),
                                     growth_( growth ),
                                     cost_( cost ),
                                     fight_value_( fight_value ) {};
};

const std::map<WarMachineUnitType, const std::shared_ptr<const UnitData>> WAR_MACHINES_PRESET = {
    { WarMachineUnitType::BALLISTA, std::make_shared<const UnitData>( WarMachineUnitType::BALLISTA, FactionType::NONE, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 100u ) },
    { WarMachineUnitType::AMMO_CART, std::make_shared<const UnitData>( WarMachineUnitType::AMMO_CART, FactionType::NONE, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 100u ) },
    { WarMachineUnitType::FIRST_AID_TENT, std::make_shared<const UnitData>( WarMachineUnitType::FIRST_AID_TENT, FactionType::NONE, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 100u ) },
    { WarMachineUnitType::CATAPULT, std::make_shared<const UnitData>( WarMachineUnitType::CATAPULT, FactionType::NONE, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 100u ) } };

const std::map<ConfluxUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_CONFLUX;

const std::map<CastleUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_CASTLE = {
    { CastleUnitType::PIKEMAN,
      std::make_shared<const UnitData>( CastleUnitType::PIKEMAN, FactionType::CASTLE, 1u, 4u, 5u, 1u, 3u, 10u, 4u, 1u, 14u, 60u, 100u ) },
    { CastleUnitType::ARCHER,
      std::make_shared<const UnitData>( CastleUnitType::ARCHER, FactionType::CASTLE, 2u, 6u, 3u, 2u, 3u, 10u, 4u, 1u, 9u, 100u, 115u ) },
    { CastleUnitType::GRIFFIN,
      std::make_shared<const UnitData>( CastleUnitType::GRIFFIN, FactionType::CASTLE, 3u, 8u, 8u, 3u, 6u, 25u, 6u, 2u, 7u, 200u, 324u ) },
    { CastleUnitType::SWORDSMAN,
      std::make_shared<const UnitData>( CastleUnitType::SWORDSMAN, FactionType::CASTLE, 4u, 10u, 12u, 6u, 9u, 35u, 5u, 1u, 4u, 300u, 445u ) },
    { CastleUnitType::MONK,
      std::make_shared<const UnitData>( CastleUnitType::MONK, FactionType::CASTLE, 5u, 12u, 7u, 10u, 12u, 30u, 5u, 1u, 3u, 400u, 485u ) },
    { CastleUnitType::CAVALIER,
      std::make_shared<const UnitData>( CastleUnitType::CAVALIER, FactionType::CASTLE, 6u, 15u, 15u, 15u, 25u, 100u, 7u, 1u, 2u, 1000u, 1668u ) },
    { CastleUnitType::ANGEL,
      std::make_shared<const UnitData>( CastleUnitType::ANGEL, FactionType::CASTLE, 7u, 30u, 30u, 50u, 50u, 200u, 12u, 1u, 1u, 3000u, 3585u ) } };

};  // namespace UnitLib