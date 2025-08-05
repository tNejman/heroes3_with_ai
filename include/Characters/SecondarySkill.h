#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy SecondarySkill:
  - Klasa SecondarySkill odpowiada za umiejętności drugorzędne postaci.
  - Zawiera metody do zarządzania poziomem umiejętności, kosztami i typem umiejętności.
*/
// #include <SFML/Graphics.hpp>

#include <stdint.h>

#include <memory>
#include <string>

#include "Exceptions/BadCopyException.hpp"
#include "Graphic/Printable.h"
#include "Miscellaneous/ProjectLib.h"

class SecondarySkill : public Printable {
  const ProjectLib::SecondarySkillType type_;
  ProjectLib::SecondarySkillLevel level_;
  uint32_t cost_;

 public:
  SecondarySkill( ProjectLib::SecondarySkillType skill_type );
  SecondarySkill( ProjectLib::SecondarySkillType skill_type, ProjectLib::SecondarySkillLevel skill_level );
  static std::unique_ptr<SecondarySkill> create( ProjectLib::SecondarySkillType type, ProjectLib::SecondarySkillLevel level );
  static std::unique_ptr<SecondarySkill> create( ProjectLib::SecondarySkillType type );

  sf::Texture& accept( Visitor& v ) const;
  ProjectLib::SecondarySkillType getType() const;
  ProjectLib::SecondarySkillLevel getLevel() const;
  std::unique_ptr<SecondarySkill> copy() const;
};

// class AirMagic : public SecondarySkill {};
// class EarthMagic : public SecondarySkill {};
// class FireMagic : public SecondarySkill {};
// class WaterMagic : public SecondarySkill {};
// class Wisdom : public SecondarySkill {};
