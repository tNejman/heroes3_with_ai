#include <gtest/gtest.h>

#include "Miscellaneous/UnitLib.h"
#include "Units/Faction.hpp"
#include "Units/Unit.h"

TEST( UnitTest, findUnitData ) {
  std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  UnitLib::CastleUnitType unit_type = UnitLib::CastleUnitType::ANGEL;
  auto unit_data_itr = UnitLib::UNITS_PRESET_CASTLE.find( unit_type );
  ASSERT_NE( unit_data_itr, UnitLib::UNITS_PRESET_CASTLE.end() );
}

TEST( UnitTest, constructor ) {
  std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  UnitLib::CastleUnitType unit_type = UnitLib::CastleUnitType::ANGEL;
  auto unit_data_ptr = UnitLib::UNITS_PRESET_CASTLE.find( unit_type )->second;  // not .end(), checked in previous test
  std::shared_ptr<Unit> unit = std::make_shared<Unit>( unit_data_ptr );
  // no assert, just checking if anything is thrown
}

TEST( UnitTest, getters ) {
  std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  UnitLib::CastleUnitType unit_type = UnitLib::CastleUnitType::ANGEL;
  auto unit_data_ptr = UnitLib::UNITS_PRESET_CASTLE.find( unit_type )->second;  // not .end(), checked in previous test
  std::shared_ptr<Unit> unit = std::make_shared<Unit>( unit_data_ptr );

  ASSERT_EQ( unit->getLevel(), unit_data_ptr->level_ );
  ASSERT_EQ( unit->getAttack(), unit_data_ptr->attack_ );
  ASSERT_EQ( unit->getDefense(), unit_data_ptr->defense_ );
  ASSERT_EQ( unit->getMinDamage(), unit_data_ptr->min_damage_ );
  ASSERT_EQ( unit->getMaxDamage(), unit_data_ptr->max_damage_ );
  ASSERT_EQ( unit->getHealth(), unit_data_ptr->health_ );
  ASSERT_EQ( unit->getSpeed(), unit_data_ptr->speed_ );
  ASSERT_EQ( unit->getCounterAttack(), unit_data_ptr->counter_attack_ );
  ASSERT_EQ( unit->getGrowth(), unit_data_ptr->growth_ );
  ASSERT_EQ( unit->getCost(), unit_data_ptr->cost_ );
  // getDmg gets checked later
  ASSERT_EQ( unit->getRange(), UnitLib::MELEE_UNIT_RANGE );  // range is melee
  ASSERT_EQ( unit->getFightValue(), unit_data_ptr->fight_value_ );
}

TEST( UnitTest, getDmgCalculations ) {
  std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  UnitLib::CastleUnitType unit_type = UnitLib::CastleUnitType::ANGEL;
  auto unit_data_ptr = UnitLib::UNITS_PRESET_CASTLE.find( unit_type )->second;  // not .end(), checked in previous test
  std::shared_ptr<Unit> unit = std::make_shared<Unit>( unit_data_ptr );

  // getDmg = min_dmg + rand() % (max_dmg - min_dmg + 1)
  for ( auto i = 0u; i < 1000; ++i ) {
    auto dmg_calculated = unit->getDmg();
    ASSERT_TRUE( dmg_calculated >= unit->getMinDamage() );
    ASSERT_TRUE( dmg_calculated <= unit->getMaxDamage() );
  }
}