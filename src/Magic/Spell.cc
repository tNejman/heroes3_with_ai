#include "Magic/Spell.h"

Spell::Spell( const ProjectLib::SpellType spell_type ) noexcept
    : type_( spell_type ) {
  // magic_school_ = TODO automatyczne przypisanie
}

std::unique_ptr<Spell> Spell::create( const ProjectLib::SpellType spell_type ) noexcept {
  return std::make_unique<Spell>( spell_type );
}

sf::Texture& Spell::accept( Visitor& v ) const {
  return v.visit( *this );
}

ProjectLib::SpellType Spell::getType() const noexcept {
  return this->type_;
}

ProjectLib::MagicSchool Spell::getSchool() const noexcept {
  return this->magic_school_;
}

uint32_t Spell::getLevel() const noexcept {
  return this->level_;
}

uint32_t Spell::getManaCost() const noexcept {
  return this->mana_cost_;
}

std::unique_ptr<Spell> Spell::copy() const noexcept {
  return std::make_unique<Spell>( this->type_ );
}
