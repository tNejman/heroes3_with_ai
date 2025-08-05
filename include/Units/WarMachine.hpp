#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy WarMachine:
  - Klasa WarMachine odpowiada za maszyny wojenne w grze.
  - Czyli trebusz, katapulta, balista, wóz amunicyjny i namiot medyczny.
*/

#include "Exceptions/InvalidWarMachineException.hpp"
#include "Units/Unit.h"

// class WarMachine : public Unit {
//  public:
//   WarMachine( const std::shared_ptr<const UnitLib::UnitData> unit_data )
//       : Unit( unit_data, nullptr ) {};

//   virtual std::unique_ptr<WarMachine> copy() const = 0;
// };

// class Ballista : public WarMachine {
//  public:
//   Ballista( const std::shared_ptr<const UnitLib::UnitData> unit_data, const int unit_type )
//       : WarMachine( unit_data, unit_type ) {};

//   std::unique_ptr<WarMachine> copy() const override {
//     return std::make_unique<Ballista>( this->unit_data_, this->unit_type_ );
//   }
// };
// class AmmoCart : public WarMachine {
//  public:
//   AmmoCart( const std::shared_ptr<const UnitLib::UnitData> unit_data, const int unit_type )
//       : WarMachine( unit_data, unit_type ) {};

//   std::unique_ptr<WarMachine> copy() const override {
//     return std::make_unique<AmmoCart>( this->unit_data_, this->unit_type_ );
//   }
// };

// class FirstAidTent : public WarMachine {
//  public:
//   FirstAidTent( const std::shared_ptr<const UnitLib::UnitData> unit_data, const int unit_type )
//       : WarMachine( unit_data, unit_type ) {};

//   std::unique_ptr<WarMachine> copy() const override {
//     return std::make_unique<FirstAidTent>( this->unit_data_, this->unit_type_ );
//   }
// };

// class Catapult : public WarMachine {
//  public:
//   Catapult( const std::shared_ptr<const UnitLib::UnitData> unit_data, const int unit_type )
//       : WarMachine( unit_data, unit_type ) {};

//   std::unique_ptr<WarMachine> copy() const override {
//     return std::make_unique<Catapult>( this->unit_data_, this->unit_type_ );
//   }
// };

class WarMachineFactory {
 public:
  WarMachineFactory() = delete;
  ~WarMachineFactory() = delete;

  static std::shared_ptr<Unit> createWarMachine( UnitLib::WarMachineUnitType machine_type ) {
    switch ( machine_type ) {
      case UnitLib::WarMachineUnitType::BALLISTA:
        return std::make_shared<Unit>( UnitLib::WAR_MACHINES_PRESET.at( UnitLib::WarMachineUnitType::BALLISTA ) );
      case UnitLib::WarMachineUnitType::AMMO_CART:
        return std::make_shared<Unit>( UnitLib::WAR_MACHINES_PRESET.at( UnitLib::WarMachineUnitType::AMMO_CART ) );
      case UnitLib::WarMachineUnitType::FIRST_AID_TENT:
        return std::make_shared<Unit>( UnitLib::WAR_MACHINES_PRESET.at( UnitLib::WarMachineUnitType::FIRST_AID_TENT ) );
      case UnitLib::WarMachineUnitType::CATAPULT:
        return std::make_shared<Unit>( UnitLib::WAR_MACHINES_PRESET.at( UnitLib::WarMachineUnitType::CATAPULT ) );
      default:
        throw InvalidWarMachineException( "WarMachineFactory::createWarMachine -> Invalid war machine type: " + std::to_string( static_cast<int>( machine_type ) ) );
    }
  }
};