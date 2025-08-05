#include "Units/Unit.h"

Unit::Unit( const std::shared_ptr<const UnitLib::UnitData> unit_data ) noexcept
    : unit_data_( unit_data ) {
  assert( unit_data != nullptr && "Unit::Unit -> UnitData is nullptr" );
}

[[nodiscard]] sf::Texture& Unit::accept( Visitor& v ) const {
  return v.visit( *this );
}

[[nodiscard]] UnitLib::UnitType Unit::getUnitType() const noexcept {
  return unit_data_->unit_type_;
}

[[nodiscard]] UnitLib::FactionType Unit::getFactionType() const noexcept {
  return unit_data_->faction_type_;
}

[[nodiscard]] uint32_t Unit::getLevel() const noexcept {
  return unit_data_->level_;
}

[[nodiscard]] uint32_t Unit::getAttack() const noexcept {
  return unit_data_->attack_;
}

[[nodiscard]] uint32_t Unit::getDefense() const noexcept {
  return unit_data_->defense_;
}

[[nodiscard]] uint32_t Unit::getMinDamage() const noexcept {
  return unit_data_->min_damage_;
}

[[nodiscard]] uint32_t Unit::getMaxDamage() const noexcept {
  return unit_data_->max_damage_;
}

[[nodiscard]] uint32_t Unit::getHealth() const noexcept {
  return unit_data_->health_;
}

[[nodiscard]] uint32_t Unit::getSpeed() const noexcept {
  return unit_data_->speed_;
}

[[nodiscard]] uint32_t Unit::getCounterAttack() const noexcept {
  return unit_data_->counter_attack_;
}

[[nodiscard]] uint32_t Unit::getGrowth() const noexcept {
  return unit_data_->growth_;
}

[[nodiscard]] uint32_t Unit::getCost() const noexcept {
  return unit_data_->cost_;
}

[[nodiscard]] uint32_t Unit::getDmg() const noexcept {
  return getMinDamage() + ( uint32_t( rand() ) % ( getMaxDamage() - getMinDamage() + 1 ) );
}

[[nodiscard]] uint32_t Unit::getRange() const noexcept {
  return UnitLib::MELEE_UNIT_RANGE;
}

[[nodiscard]] uint32_t Unit::getFightValue() const noexcept {
  return unit_data_->fight_value_;
}