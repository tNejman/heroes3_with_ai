#pragma once
// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'Character' implementuje obiekt postaci
    - postać zawiera:
      - statystyki
      - zdolności (secondary_skills_)
      - miejsca na artefakty (equipment_)
      - miejsca na maszyny bojowe (war_machines_)
      - nieużywane obecnie artefakty (backpack_)
      - podwładne jednostki (party_)
*/
// #include <SFML/Graphics.hpp>

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Artifacts/Artifact.h"
#include "Characters/SecondarySkill.h"
#include "Exceptions/EmptySlotException.hpp"
#include "Exceptions/FullBackpackException.hpp"
#include "Exceptions/InvalidSecondarySkillException.hpp"
#include "Exceptions/InvalidSlotException.hpp"
#include "Exceptions/NotEmptySlotException.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "Magic/SpellBook.h"
#include "Miscellaneous/ProjectLib.h"
#include "Units/UnitStack.h"
#include "Units/WarMachine.hpp"
#include "WorldMap/MapObject.h"

class Character : public MapObject {
 private:
  // Coords already implemented in MapObject

  ProjectLib::CharacterMoveDirection orientation_ = ProjectLib::CharacterMoveDirection::RIGHT;
  const ProjectLib::CharacterType character_type_ = ProjectLib::CharacterType::FIRE_HERO;

  // Basic information
  const std::string name_;
  bool alive_;
  CoordPair coords_;
  bool is_user_character_ = true;

  // Primary Skills
  uint32_t attack_;
  uint32_t defense_;
  uint32_t power_;
  uint32_t knowledge_;

  // Miscellanous values
  uint32_t level_;
  uint32_t experience_;
  uint32_t max_mana_;
  uint32_t current_mana_;
  uint32_t movement_points_;
  short morale_;
  short luck_;

  std::array<std::unique_ptr<const SecondarySkill>, ProjectLib::SECONDARY_SKILLS_SLOTS_COUNT> secondary_skills_{
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
  std::map<ProjectLib::EquipmentSlots, std::unique_ptr<const Artifact>> equipment_;
  std::map<UnitLib::WarMachineUnitType, std::shared_ptr<UnitStack>> war_machines_;
  std::unique_ptr<SpellBook> spell_book_ = nullptr;
  std::vector<std::unique_ptr<const Artifact>> backpack_;
  std::array<std::shared_ptr<UnitStack>, ProjectLib::MAX_PARTY_SIZE> party_{
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

  void initializeEquipment() noexcept;
  void initializeWarMachines() noexcept;
  std::optional<ProjectLib::EquipmentSlots> checkSlotIfEmpty( ProjectLib::EquipmentSlots slot ) const;

 public:
  friend class CharacterSaver;
  //   Character() = default;
  //   Character(const Character&) = default;
  //   Character(Character&&) = default;
  Character(
      const std::string& name,
      const CoordPair coords,
      const uint32_t attack,
      const uint32_t defense,
      const uint32_t power,
      const uint32_t knowledge,
      const uint32_t max_mana,
      const short morale,
      const short luck );
  ~Character();
  sf::Texture& accept( Visitor& v ) const override;

  ProjectLib::CharacterMoveDirection getOrientation() const;
  void setOrientation( ProjectLib::CharacterMoveDirection new_orientation );

  [[nodiscard]] ProjectLib::CharacterType getCharacterType() const;

  [[nodiscard]] const std::string& getName() const;

  [[nodiscard]] bool getIfUser() const;
  void setIfUser( bool is_user );

  [[nodiscard]] uint32_t getAttack() const;
  void setAttack( const uint32_t new_attack );
  void modifyAttack( const uint32_t attack_diff );

  [[nodiscard]] uint32_t getDefense() const;
  void setDefense( const uint32_t new_defense );
  void modifyDefense( const uint32_t defense_diff );

  [[nodiscard]] uint32_t getPower() const;
  void setPower( const uint32_t new_power );
  void modifyPower( const uint32_t power_diff );

  [[nodiscard]] uint32_t getKnowledge() const;
  void setKnowledge( const uint32_t new_knowledge );
  void modifyKnowledge( const uint32_t knowledge_diff );

  [[nodiscard]] uint32_t getMovementPoints() const;
  void setMovementPoints( const uint32_t new_movement );
  void modifyMovementPoints( const uint32_t movement_diff );

  [[nodiscard]] uint32_t getLevel() const;
  void levelUp();

  [[nodiscard]] uint32_t getExperience() const;
  void gainExperience( const uint32_t experience );

  [[nodiscard]] uint32_t getMaxMana() const;
  void setMaxMana( const uint32_t new_max_mana );
  void modifyMaxMana( const uint32_t max_mana_diff );

  [[nodiscard]] uint32_t getCurrentMana() const;
  void setCurrentMana( const uint32_t new_current_mana );
  void modifyCurrentMana( const uint32_t current_mana_diff );

  [[nodiscard]] short getMorale() const;
  void setMorale( const short new_morale );
  void modifyMorale( const short morale_diff );

  [[nodiscard]] short getLuck() const;
  void setLuck( const short new_luck );
  void modifyLuck( const short luck_diff );

  [[nodiscard]] uint32_t getEffectiveSpeed();

  [[nodiscard]] bool getIfAlive() const;
  bool die();

  void learnSecondarySkill( std::unique_ptr<SecondarySkill> secondary_skill );

  [[nodiscard]] bool getIfBackpackFull() const;

  void pickUpArtifact( std::unique_ptr<const Artifact> artifact );
  void equipArtifact( ArtifactLib::ArtifactType type, ProjectLib::EquipmentSlots slot );
  void unequipArtifact( ProjectLib::EquipmentSlots slot );

  void recruitWarMachine( std::shared_ptr<UnitStack> war_machine );
  void unequipWarMachine( UnitLib::WarMachineUnitType machine_type );

  void equipSpellBook( std::unique_ptr<SpellBook> spell_book );
  [[nodiscard]] std::unique_ptr<SpellBook> unequipSpellBook();

  [[nodiscard]] const std::vector<std::unique_ptr<const Artifact>>& getBackpack();
  [[nodiscard]] std::array<std::shared_ptr<UnitStack>, ProjectLib::MAX_PARTY_SIZE>& getParty();
  [[nodiscard]] uint32_t getPartySize();

  void recruitUnitStack( std::shared_ptr<UnitStack> unit_stack );
  //  std::unique_ptr<UnitStack>& getPartyMember(uint32_t backpack_id);

  //  void learnSpell( const std::unique_ptr<Spell>& spell );
  //  void forgetSpell( const std::unique_ptr<Spell>& spell );
  //  void castSpell( const std::unique_ptr<Spell>& spell );
  [[nodiscard]] std::shared_ptr<Character> copy();
};
