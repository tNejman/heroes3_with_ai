#include "LoadAndSaveTools/CharacterJsonLoader.h"

std::shared_ptr<Character> CharacterJsonLoader::doGetObject() {
  try {
    if ( !verifySaveMarker( data_["marker"] ) ) {
      std::string message;
      message += "CharacterJsonLoader expected json to begin with \"CHARACTER\" marker but instead read: ";
      message += data_["marker"];
      throw DamagedSaveException( message );
    }
    auto name = loadName();
    auto coords = loadCoords();
    auto if_alive = loadAlive();
    auto primary_skills = loadPrimarySkills();
    auto misc_values = loadMiscValues();
    auto secondary_skills = loadSecondarySkills();
    auto artifacts_equipped = loadArtifactsEquipped();
    auto war_machines = loadWarMachines();
    auto spell_book = loadSpells();
    auto artifacts_backpack = loadArtifactsBackpack();
    auto party = loadParty();

    uint32_t attack = primary_skills[0];
    uint32_t defense = primary_skills[1];
    uint32_t power = primary_skills[2];
    uint32_t knowledge = primary_skills[3];

    // uint32_t level = static_cast<uint32_t>( misc_values[0] );       // unused in constructor
    uint32_t experience = static_cast<uint32_t>( misc_values[1] );  // unused in constructor
    uint32_t max_mana = static_cast<uint32_t>( misc_values[2] );
    uint32_t current_mana = static_cast<uint32_t>( misc_values[3] );     // unused in constructor
    uint32_t movement_points = static_cast<uint32_t>( misc_values[4] );  // unused in constructor
    short morale = static_cast<short>( misc_values[5] );
    short luck = static_cast<short>( misc_values[6] );
    auto character = std::make_shared<Character>( name, coords,
                                                  attack, defense, power, knowledge, max_mana, morale, luck );

    if ( !if_alive ) {
      character->die();
    }

    character->gainExperience( experience );

    character->setCurrentMana( current_mana );
    character->setMovementPoints( movement_points );

    for ( auto& sec_skill : secondary_skills ) {
      character->learnSecondarySkill( std::move( sec_skill ) );
    }

    for ( auto& artifact : artifacts_equipped ) {
      if ( artifact != nullptr ) {
        ArtifactLib::ArtifactType type = artifact->getType();
        ProjectLib::EquipmentSlots slot = artifact->getSlot();
        character->pickUpArtifact( std::move( artifact ) );
        character->equipArtifact( type, slot );
      }
    }

    // auto make_character_recruit_war_machines = [&]<typename T>( std::unique_ptr<WarMachine> war_machine ) {
    //   if ( war_machine != nullptr ) {
    //     const T* raw_ptr = dynamic_cast<const T*>( war_machine.get() );
    //     if ( raw_ptr != nullptr ) {
    //       std::unique_ptr<const T> unq_ptr( const_cast<T*>( raw_ptr ) );
    //       war_machine.release();
    //       character->recruitWarMachine( std::move( unq_ptr ) );
    //     }
    //   }
    // };
    // make_character_recruit_war_machines.operator()<Ballista>( std::move( war_machines[0] ) );
    // make_character_recruit_war_machines.operator()<AmmoCart>( std::move( war_machines[1] ) );
    // make_character_recruit_war_machines.operator()<FirstAidTent>( std::move( war_machines[2] ) );
    // make_character_recruit_war_machines.operator()<Catapult>( std::move( war_machines[3] ) );
    for ( const auto& war_machine : war_machines ) {
      character->recruitWarMachine( war_machine->copy() );
    }

    character->equipSpellBook( std::move( spell_book ) );
    for ( auto& artifact_unq_ptr : artifacts_backpack ) {
      character->pickUpArtifact( std::move( artifact_unq_ptr ) );
    }
    for ( auto& unit_stack_ptr : party ) {
      character->recruitUnitStack( unit_stack_ptr );
    }

    throw NotImplementedException( "CharacterJsonLoader::doGetObject() is not finished" );
  } catch ( const std::exception& e ) {
    std::cout << "Error occured when creating Character from save: " << e.what() << std::endl;
    return nullptr;
  }
}

bool CharacterJsonLoader::verifySaveMarker( const std::string& marker ) const {
  return marker == ProjectLib::CHARACTER_SAVE_START_MARKER;
}

std::string CharacterJsonLoader::loadName() const {
  return data_["name"];
}

CoordPair CharacterJsonLoader::loadCoords() const {
  uint32_t x = data_["coords"][0];
  uint32_t y = data_["coords"][1];
  return CoordPair( x, y );
}

bool CharacterJsonLoader::loadAlive() const {
  return data_["alive"];
}

std::array<uint32_t, 4> CharacterJsonLoader::loadPrimarySkills() const {
  std::array<uint32_t, 4> primary_skills{
      data_["primary_skills"]["atk"],
      data_["primary_skills"]["def"],
      data_["primary_skills"]["pow"],
      data_["primary_skills"]["knwl"] };
  return primary_skills;
}

std::array<int, 7> CharacterJsonLoader::loadMiscValues() const {
  std::array<int, 7> misc_values{
      data_["misc_values"]["lvl"],
      data_["misc_values"]["exp"],
      data_["misc_values"]["mm"],
      data_["misc_values"]["cm"],
      data_["misc_values"]["movpts"],
      data_["misc_values"]["mor"],
      data_["misc_values"]["lck"] };
  return misc_values;
}

std::vector<std::unique_ptr<SecondarySkill>> CharacterJsonLoader::loadSecondarySkills() const {
  std::vector<std::unique_ptr<SecondarySkill>> secondary_skills;
  for ( auto& sec_skill : data_["secondary_skills"] ) {
    int sec_skill_type = sec_skill[0];
    int sec_skill_level = sec_skill[1];

    auto sec_skill_type_s = static_cast<ProjectLib::SecondarySkillType>( sec_skill_type );
    auto sec_skill_level_s = static_cast<ProjectLib::SecondarySkillLevel>( sec_skill_level );
    secondary_skills.push_back( SecondarySkill::create( sec_skill_type_s, sec_skill_level_s ) );
  }
  return secondary_skills;
}

std::array<std::unique_ptr<const Artifact>, 14> CharacterJsonLoader::loadArtifactsEquipped() const {
  std::array<std::unique_ptr<const Artifact>, 14> artifacts;
  size_t i = 0;
  for ( const int artifact_type_int : data_["equipped_artifacts"] ) {
    if ( artifact_type_int == -1 ) {
      artifacts[i] = nullptr;
    } else {
      ArtifactLib::ArtifactType artifact_type = static_cast<ArtifactLib::ArtifactType>( artifact_type_int );
      artifacts[i] = Artifact::create( artifact_type );
    }
  }
  return artifacts;
}

std::array<std::shared_ptr<UnitStack>, 4> CharacterJsonLoader::loadWarMachines() const {
  std::array<std::shared_ptr<UnitStack>, 4> war_machines;
  size_t i = 0;
  for ( const int war_machine_type : data_["war_machines"] ) {
    if ( war_machine_type == -1 ) {
      war_machines[i] = nullptr;
    } else if ( war_machine_type == 0 || war_machine_type == 1 || war_machine_type == 2 ) {
      war_machines[i] = std::make_shared<UnitStack>( WarMachineFactory::createWarMachine( static_cast<UnitLib::WarMachineUnitType>( war_machine_type ) ), 1 );
    } else {
      throw DamagedSaveException( "CharacterJsonLoader::loadWarMachines -> Encountered invalid war machine type: " + std::to_string( war_machine_type ) );
    }
  }
  return war_machines;
}

std::unique_ptr<SpellBook> CharacterJsonLoader::loadSpells() const {
  std::vector<int> spell_ids = data_["spells"];
  if ( spell_ids.empty() ) {
    return nullptr;
  }
  auto spell_book = std::make_unique<SpellBook>();
  for ( const int spell_id : spell_ids ) {
    auto spell = Spell::create( static_cast<ProjectLib::SpellType>( spell_id ) );
    if ( spell ) {
      spell_book->learnSpell( std::move( spell ) );
    }
  }
  return spell_book;
}

std::vector<std::unique_ptr<const Artifact>> CharacterJsonLoader::loadArtifactsBackpack() const {
  std::vector<std::unique_ptr<const Artifact>> artifacts;
  for ( const int artifact_type_int : data_["artifacts_backpack"] ) {
    ArtifactLib::ArtifactType artifact_type = static_cast<ArtifactLib::ArtifactType>( artifact_type_int );
    artifacts.push_back( Artifact::create( artifact_type ) );
  }
  return artifacts;
}

std::array<std::shared_ptr<UnitStack>, 7> CharacterJsonLoader::loadParty() const {
  std::array<std::shared_ptr<UnitStack>, 7> party;
  size_t i = 1;
  for ( auto& unit_stack : data_["party"] ) {
    UnitLib::FactionType faction_type = static_cast<UnitLib::FactionType>( unit_stack["faction"] );
    std::shared_ptr<const Unit> unit;
    switch ( faction_type ) {
      case UnitLib::FactionType::CONFLUX: {
        UnitLib::ConfluxUnitType unit_type_conflux = static_cast<UnitLib::ConfluxUnitType>( unit_stack["unit_type"] );
        auto faction_conflux = std::dynamic_pointer_cast<FactionConflux>( factions_[ProjectLib::FACTION_CONFLUX_ID_MARKER] );
        unit = faction_conflux->getUnit( unit_type_conflux );
        break;
      }
      case UnitLib::FactionType::CASTLE: {
        UnitLib::CastleUnitType unit_type_castle = static_cast<UnitLib::CastleUnitType>( unit_stack["unit_type"] );
        auto faction_castle = std::dynamic_pointer_cast<FactionCastle>( factions_[ProjectLib::FACTION_CASTLE_ID_MARKER] );
        unit = faction_castle->getUnit( unit_type_castle );
        break;
      }
      case UnitLib::FactionType::NONE: {
        throw DamagedSaveException( "CharacterJsonLoader::loadParty -> encountered Factiontype::NONE but expected actual FactionType" );
      }
    }
    party[i] = std::make_shared<UnitStack>( unit, data_["party"]["unit" + std::to_string( i )]["size"] );
    party[i]->setMorale( data_["party"]["unit" + std::to_string( i )]["morale"] );
    party[i]->setLuck( data_["party"]["unit" + std::to_string( i )]["luck"] );
    party[i]->setSize( data_["party"]["unit" + std::to_string( i )]["size"] );
    party[i]->setCurrentHealth( data_["party"]["unit" + std::to_string( i )]["current_health"] );
  }
  return party;
}

CharacterJsonLoader::CharacterJsonLoader( std::vector<std::shared_ptr<Faction>>& factions )
    : factions_( factions ) {}