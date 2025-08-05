#include "LoadAndSaveTools/CharacterSaver.h"

// TODO fix to save enum instead of Name

void CharacterSaver::saveStats( std::ofstream& out ) const {
  auto character_save_marker_start_int_vec = convertStringToInVec( "CHARACTER" );
  for ( const auto position : character_save_marker_start_int_vec ) {
    out << position << ' ';
  }
  out << std::endl;
  auto character_name_as_int_vec = convertStringToInVec( c_->getName() );
  for ( const auto position : character_name_as_int_vec ) {
    out << position << ' ';
  }
  out << std::endl;
  out << c_->getCoords().x_ << ' ' << c_->getCoords().y_ << std::endl;
  out << ( c_->getIfAlive() ? '1' : '0' ) << std::endl;
  out << c_->getAttack() << ' ' << c_->getDefense() << ' ' << c_->getPower() << ' ' << c_->getKnowledge()
      << c_->getLevel() << ' ' << c_->getExperience() << ' ' << c_->getMaxMana() << ' ' << c_->getCurrentMana() << ' ' << c_->getMovementPoints() << std::endl;
  out << c_->getMorale() << ' ' << c_->getLuck() << std::endl;
}

void CharacterSaver::saveSecondarySkills( std::ofstream& out ) const {
  // out << "DEBUG: Secondary skills" << std::endl;
  for ( const auto& secondary_skill_ptr : c_->secondary_skills_ ) {
    if ( secondary_skill_ptr == nullptr )
      out << "-1 -1 ";
    else {
      out << int( secondary_skill_ptr->getType() ) << ' ';
      out << int( secondary_skill_ptr->getLevel() ) << ' ';
    }
  }
  out << std::endl;
}

void CharacterSaver::saveEquipment( std::ofstream& out ) const {
  // out << "DEBUG: Artifacts" << std::endl;
  for ( const auto& [_, artifact_ptr] : c_->equipment_ ) {
    if ( artifact_ptr == nullptr )
      out << "-1 ";
    else
      out << int( artifact_ptr->getType() ) << ' ';
  }
  out << std::endl;
}

void CharacterSaver::saveWarMachines( std::ofstream& out ) const {
  // out << "DEBUG: War Machines" << std::endl;
  for ( const auto& [_, war_machine_ptr] : c_->war_machines_ ) {
    if ( war_machine_ptr == nullptr )
      out << -1 << ' ';
    else
      out << war_machine_ptr->getName() << ' ';
  }
  out << std::endl;
}

void CharacterSaver::saveSpellBook( std::ofstream& out ) const {
  // out << "DEBUG: SpellBook" << std::endl;
  if ( c_->spell_book_ == nullptr )
    out << -2 << std::endl;
  else {
    for ( const auto& spell_ptr : c_->spell_book_->spells_ ) {
      out << int( spell_ptr->getType() ) << ' ';
      out << int( spell_ptr->getLevel() ) << ' ';
    }
  }
}

void CharacterSaver::saveBackpack( std::ostream& out ) const {
  // out << "DEBUG: Backpack" << std::endl;
  if ( c_->backpack_.size() == 0 ) {
    out << -2 << std::endl;
    return;
  }

  for ( const auto& artifact_ptr : c_->backpack_ ) {
    out << int( artifact_ptr->getType() ) << ' ';
  }
  out << std::endl;
}

void CharacterSaver::saveParty( std::ofstream& out ) const {
  // out << "DEBUG: Party" << std::endl;
  for ( const auto& unit_stack_ptr : c_->party_ ) {
    if ( unit_stack_ptr == nullptr ) {
      out << "-1 -1 -1 -1 -1 -1 ";
    } else {
      out << static_cast<int>( unit_stack_ptr->getFactionType() ) << ' ';

      int unit_type_int;
      std::visit( [&unit_type_int]( auto&& value ) {
        using T = std::decay_t<decltype( value )>;
        unit_type_int = static_cast<std::underlying_type_t<T>>( value );
      },
                  unit_stack_ptr->getUnitType() );
      out << unit_type_int << ' ';
      out << unit_stack_ptr->getMorale() << ' ';
      out << unit_stack_ptr->getLuck() << ' ';
      out << unit_stack_ptr->getSize() << ' ';
      out << unit_stack_ptr->getCurrentHealth() << ' ';
    }
  }
  out << std::endl;
}

CharacterSaver::CharacterSaver( std::string&& path, std::shared_ptr<const Character> character )
    : ISaver( path ), c_( character ) {}

void CharacterSaver::doSave( std::ofstream& out ) const {
  this->saveStats( out );
  this->saveSecondarySkills( out );
  this->saveEquipment( out );
  this->saveWarMachines( out );
  this->saveSpellBook( out );
  this->saveBackpack( out );
  this->saveParty( out );
}

std::vector<int> CharacterSaver::convertStringToInVec( const std::string& str ) const {
  std::vector<int> str_as_vec;
  for ( auto character : str ) {
    str_as_vec.push_back( int( character ) );  // reintepret cast to int is on purpose
  }
  return str_as_vec;
}
