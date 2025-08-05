#pragma once

#include <memory>
#include <set>
#include <string>

#include "Exceptions/InvalidArtifactTypeException.hpp"
#include "Miscellaneous/ProjectLib.h"

namespace ArtifactLib {

enum class ArtifactType : int {
  // Helmets
  CROWN_OF_THE_SUPREME_MAGI,
  HELM_OF_THE_ALABASTER_UNICORN,
  THUNDER_HELMET,

  // Capes
  DRAGON_WING_TABARD,
  CAPE_OF_VELOCITY,

  // Necklaces
  NECKLACE_OF_DRAGONTEETH,
  CELESTIAL_NECKLACE_OF_BLISS,
  NECKLACE_OF_SWIFTNESS,

  // Weapons
  CENTAURS_AXE,
  TITANS_GLADIUS,
  SWORD_OF_JUDGEMENT,

  // Shields
  SHIELD_OF_THE_DWARVEN_LORDS,
  DRAGON_SCALE_SHIELD,
  SENTINELS_SHIELD,

  // Torsos
  RIB_CAGE,
  DRAGON_SCALE_ARMOR,
  TITANS_CUIRASS,

  // Rings
  QUIET_EYE_OF_THE_DRAGON,
  EQUESTRIAN_GLOVES,
  RING_OF_VITALITY,
  RING_OF_WAYFARER,
  RING_OF_LIFE,

  // Feet
  DRAGONBONE_GREAVES,
  SANDALS_OF_THE_SAINT,
  BOOTS_OF_SPEED,

  // Misc
};

class ArtifactData {
 public:
  const ArtifactType type_;
  const ProjectLib::EquipmentSlots slot_;
  const int attack_;
  const int defense_;
  const int power_;
  const int knowledge_;
  const int speed_;
  const uint32_t cost_;

  ArtifactData(
      const ArtifactType type,
      const ProjectLib::EquipmentSlots slot,
      const int attack,
      const int defense,
      const int power,
      const int knowledge,
      const int speed,
      const uint32_t cost ) : type_( type ),
                              slot_( slot ),
                              attack_( attack ),
                              defense_( defense ),
                              power_( power ),
                              knowledge_( knowledge ),
                              speed_( speed ),
                              cost_( cost ) {};
};

const std::map<ArtifactType, std::shared_ptr<const ArtifactData>> ARTIFACTS_PRESET = {
    { ArtifactType::CROWN_OF_THE_SUPREME_MAGI, std::make_shared<ArtifactData>( ArtifactType::CROWN_OF_THE_SUPREME_MAGI, ProjectLib::EquipmentSlots::HELMET, 0, 0, 5, 5, 0, 10'000u ) },
    { ArtifactType::HELM_OF_THE_ALABASTER_UNICORN, std::make_shared<ArtifactData>( ArtifactType::HELM_OF_THE_ALABASTER_UNICORN, ProjectLib::EquipmentSlots::HELMET, 0, 0, 0, 0, 2, 5'000u ) },
    { ArtifactType::THUNDER_HELMET, std::make_shared<ArtifactData>( ArtifactType::THUNDER_HELMET, ProjectLib::EquipmentSlots::HELMET, 3, 3, 0, 0, 0, 6'000u ) },

    { ArtifactType::DRAGON_WING_TABARD, std::make_shared<ArtifactData>( ArtifactType::DRAGON_WING_TABARD, ProjectLib::EquipmentSlots::CAPE, -1, -1, -1, -1, -1, 5'000u ) },
    { ArtifactType::CAPE_OF_VELOCITY, std::make_shared<ArtifactData>( ArtifactType::CAPE_OF_VELOCITY, ProjectLib::EquipmentSlots::CAPE, -2, -2, -2, -2, -2, 8'000u ) },

    { ArtifactType::NECKLACE_OF_DRAGONTEETH, std::make_shared<ArtifactData>( ArtifactType::NECKLACE_OF_DRAGONTEETH, ProjectLib::EquipmentSlots::NECKLACE, -1, -1, -1, -1, -1, 3'000u ) },
    { ArtifactType::CELESTIAL_NECKLACE_OF_BLISS, std::make_shared<ArtifactData>( ArtifactType::CELESTIAL_NECKLACE_OF_BLISS, ProjectLib::EquipmentSlots::NECKLACE, -2, -2, -2, -2, -2, -2 ) },
    { ArtifactType::NECKLACE_OF_SWIFTNESS, std::make_shared<ArtifactData>( ArtifactType::NECKLACE_OF_SWIFTNESS, ProjectLib::EquipmentSlots::NECKLACE, -3, -3, -3, -3, -3, -3 ) },

    { ArtifactType::CENTAURS_AXE, std::make_shared<ArtifactData>( ArtifactType::CENTAURS_AXE, ProjectLib::EquipmentSlots::WEAPON, 2, 0, 0, 0, 0, 2'000u ) },
    { ArtifactType::TITANS_CUIRASS, std::make_shared<ArtifactData>( ArtifactType::TITANS_GLADIUS, ProjectLib::EquipmentSlots::WEAPON, 12, -3, 0, 0, 0, 10'000u ) },
    { ArtifactType::SWORD_OF_JUDGEMENT, std::make_shared<ArtifactData>( ArtifactType::SWORD_OF_JUDGEMENT, ProjectLib::EquipmentSlots::WEAPON, 5, 5, 5, 5, 0, 20'000u ) },

    { ArtifactType::SHIELD_OF_THE_DWARVEN_LORDS, std::make_shared<ArtifactData>( ArtifactType::SHIELD_OF_THE_DWARVEN_LORDS, ProjectLib::EquipmentSlots::SHIELD, 0, 2, 0, 0, 0, 2'000u ) },
    { ArtifactType::DRAGON_SCALE_SHIELD, std::make_shared<ArtifactData>( ArtifactType::DRAGON_SCALE_SHIELD, ProjectLib::EquipmentSlots::SHIELD, 3, 3, 0, 0, 0, 6'000u ) },
    { ArtifactType::SENTINELS_SHIELD, std::make_shared<ArtifactData>( ArtifactType::SENTINELS_SHIELD, ProjectLib::EquipmentSlots::SHIELD, 0, 0, 0, 0, 0, 8'000u ) },

    { ArtifactType::RIB_CAGE, std::make_shared<ArtifactData>( ArtifactType::RIB_CAGE, ProjectLib::EquipmentSlots::TORSO, 0, 0, 2, 0, 0, 3'000u ) },
    { ArtifactType::DRAGON_SCALE_ARMOR, std::make_shared<ArtifactData>( ArtifactType::DRAGON_SCALE_ARMOR, ProjectLib::EquipmentSlots::TORSO, 4, 4, 0, 0, 0, 8'000u ) },
    { ArtifactType::TITANS_CUIRASS, std::make_shared<ArtifactData>( ArtifactType::TITANS_CUIRASS, ProjectLib::EquipmentSlots::TORSO, 6, 6, 0, 0, 0, 12'000u ) },

    { ArtifactType::QUIET_EYE_OF_THE_DRAGON, std::make_shared<ArtifactData>( ArtifactType::QUIET_EYE_OF_THE_DRAGON, ProjectLib::EquipmentSlots::RING, 0, 0, 0, 0, 0, 5'000u ) },
    { ArtifactType::EQUESTRIAN_GLOVES, std::make_shared<ArtifactData>( ArtifactType::EQUESTRIAN_GLOVES, ProjectLib::EquipmentSlots::RING, 0, 0, 0, 0, 0, 3'000u ) },
    { ArtifactType::RING_OF_VITALITY, std::make_shared<ArtifactData>( ArtifactType::RING_OF_VITALITY, ProjectLib::EquipmentSlots::RING, 0, 0, 0, 0, 0, 4'000u ) },
    { ArtifactType::RING_OF_WAYFARER, std::make_shared<ArtifactData>( ArtifactType::RING_OF_WAYFARER, ProjectLib::EquipmentSlots::RING, 0, 0, 0, 0, 0, 3'000u ) },
    { ArtifactType::RING_OF_LIFE, std::make_shared<ArtifactData>( ArtifactType::RING_OF_LIFE, ProjectLib::EquipmentSlots::RING, 0, 0, 0, 0, 0, 6'000u ) },

    { ArtifactType::DRAGONBONE_GREAVES, std::make_shared<ArtifactData>( ArtifactType::DRAGONBONE_GREAVES, ProjectLib::EquipmentSlots::FEET, 0, 0, 0, 0, 0, 4'000u ) },
    { ArtifactType::SANDALS_OF_THE_SAINT, std::make_shared<ArtifactData>( ArtifactType::SANDALS_OF_THE_SAINT, ProjectLib::EquipmentSlots::FEET, 0, 0, 0, 0, 0, 5'000u ) },
    { ArtifactType::BOOTS_OF_SPEED, std::make_shared<ArtifactData>( ArtifactType::BOOTS_OF_SPEED, ProjectLib::EquipmentSlots::FEET, 0, 0, 0, 0, 0, 6'000u ) } };
}  // namespace ArtifactLib