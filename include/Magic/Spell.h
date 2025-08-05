#pragma once
// autor: Tomasz Nejman i Tomasz Naszkowski
/* zawarość klasa spell:
    - klasa ma pozwalać na rzucanie zaklęć
*/
// #include <SFML/Graphics.hpp>
#include <stdint.h>

#include <memory>
#include <string>

#include "Graphic/Printable.h"
#include "Miscellaneous/ProjectLib.h"

class Spell : public Printable {
 private:
  const ProjectLib::SpellType type_;
  ProjectLib::MagicSchool magic_school_;
  uint32_t level_;
  uint32_t mana_cost_;

 public:
  Spell( const ProjectLib::SpellType spell_type ) noexcept;
  Spell( const Spell& ) = delete;
  ~Spell() = default;
  [[nodiscard]] static std::unique_ptr<Spell> create( const ProjectLib::SpellType spell_type ) noexcept;
  [[nodiscard]] sf::Texture& accept( Visitor& v ) const override;
  [[nodiscard]] ProjectLib::SpellType getType() const noexcept;
  [[nodiscard]] ProjectLib::MagicSchool getSchool() const noexcept;
  [[nodiscard]] uint32_t getLevel() const noexcept;
  [[nodiscard]] uint32_t getManaCost() const noexcept;
  [[nodiscard]] std::unique_ptr<Spell> copy() const noexcept;
};