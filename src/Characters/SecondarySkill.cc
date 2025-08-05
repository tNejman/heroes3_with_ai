#include "Characters/SecondarySkill.h"

SecondarySkill::SecondarySkill( ProjectLib::SecondarySkillType skill_type )
    : type_( skill_type ), level_( ProjectLib::SecondarySkillLevel::BASIC ), cost_( 0 ) {};

SecondarySkill::SecondarySkill( ProjectLib::SecondarySkillType skill_type, ProjectLib::SecondarySkillLevel skill_level )
    : type_( skill_type ), level_( skill_level ), cost_( 0 ) {};

std::unique_ptr<SecondarySkill> SecondarySkill::create( ProjectLib::SecondarySkillType type, ProjectLib::SecondarySkillLevel level ) {
  return std::make_unique<SecondarySkill>( type, level );
}

std::unique_ptr<SecondarySkill> SecondarySkill::create( ProjectLib::SecondarySkillType type ) {
  return std::make_unique<SecondarySkill>( type );
}

sf::Texture& SecondarySkill::accept( Visitor& v ) const {
  return v.visit( *this );
}

ProjectLib::SecondarySkillType SecondarySkill::getType() const {
  return this->type_;
}

ProjectLib::SecondarySkillLevel SecondarySkill::getLevel() const {
  return this->level_;
}

std::unique_ptr<SecondarySkill> SecondarySkill::copy() const {
  std::unique_ptr<SecondarySkill> copy =
      std::make_unique<SecondarySkill>( this->type_ );
  copy->level_ = this->level_;
  copy->cost_ = this->cost_;
  return copy;
}