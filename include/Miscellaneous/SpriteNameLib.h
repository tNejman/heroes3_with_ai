#pragma once

#include <map>
#include <string>

#include "Miscellaneous/ArtifactLib.h"
#include "Miscellaneous/ProjectLib.h"

namespace SpriteNameLib {

const std::string SPRITE_DIR_PREFIX = "Sprites/";
const std::string SPRITE_ARTIFACTS_DIR_PREFIX = SPRITE_DIR_PREFIX + "artifacts/";
const std::string SPRITE_OBSTACLES_DIR_PREFIX = SPRITE_DIR_PREFIX + "obstacles/";
const std::string SPRITE_BUILDINGS_DIR_PREFIX = SPRITE_DIR_PREFIX + "buildings/";
const std::string SPRITE_HEROES_DIR_PREFIX = SPRITE_DIR_PREFIX + "heroes/";
const std::string SPRITE_SECONDARY_SKILLS_DIR_PREFIX = SPRITE_DIR_PREFIX + "secondary_skills/";
const std::string SPRITE_SPELLS_DIR_PREFIX = SPRITE_DIR_PREFIX + "spells/";
const std::string SPRITE_UNITS_DIR_PREFIX = SPRITE_DIR_PREFIX + "units/";
const std::string SPRITE_RESOURCE_DIR_PREFIX = SPRITE_DIR_PREFIX + "resource/";
const std::string SPRITE_TERRAIN_TILES_DIR_PREFIX = SPRITE_DIR_PREFIX + "terrain/tiles/";
const std::string SPRITE_OVERWORLD_OBSTACLE_DIR_PREFIX = SPRITE_DIR_PREFIX + "terrain/Overworld_obstacles/";

const std::string SPRITE_FILE_TYPE_SUFFIX = ".png";

/*
 * Character
 */
const std::map<ProjectLib::CharacterType, std::string> CHARACTER_TYPE_TO_STRING{
    { ProjectLib::CharacterType::FIRE_HERO, "fire_hero" },
    { ProjectLib::CharacterType::BLACK_HERO_WHITE_HORSE, "black_her_white_horse" } };

const std::map<ProjectLib::CharacterMoveDirection, std::string> CHARACTER_ORIENTATION_TO_STRING{
    { ProjectLib::CharacterMoveDirection::UP, "_up" },
    { ProjectLib::CharacterMoveDirection::UP_RIGHT, "_up_right" },
    { ProjectLib::CharacterMoveDirection::RIGHT, "_right" },
    { ProjectLib::CharacterMoveDirection::DOWN_RIGHT, "_down_right" },
    { ProjectLib::CharacterMoveDirection::DOWN, "_down" },
    { ProjectLib::CharacterMoveDirection::DOWN_LEFT, "_down_left" },
    { ProjectLib::CharacterMoveDirection::LEFT, "_left" },
    { ProjectLib::CharacterMoveDirection::UP_LEFT, "_up_left" } };

/*
 * Secondary Skill
 */
const std::map<ProjectLib::SecondarySkillType, std::string> SECONDARY_SKILL_TYPE_TO_STRING{
    { ProjectLib::SecondarySkillType::AIR_MAGIC, "air_magic" },
    { ProjectLib::SecondarySkillType::FIRE_MAGIC, "fire_magic" },
    { ProjectLib::SecondarySkillType::EARTH_MAGIC, "earth_magic" },
    { ProjectLib::SecondarySkillType::WATER_MAGIC, "water_magic" } };

/*
 * Artifact
 */
const std::map<ArtifactLib::ArtifactType, std::string> ARTIFACT_TYPE_TO_STRING{
    { ArtifactLib::ArtifactType::CROWN_OF_THE_SUPREME_MAGI, "crown_of_the_supreme_magi" },
    { ArtifactLib::ArtifactType::HELM_OF_THE_ALABASTER_UNICORN, "helm_of_the_alabaster_unicorn" },
    { ArtifactLib::ArtifactType::THUNDER_HELMET, "thunder_helmet" },
    { ArtifactLib::ArtifactType::DRAGON_WING_TABARD, "dragon_wing_tabard" },
    { ArtifactLib::ArtifactType::CAPE_OF_VELOCITY, "cape_of_velocity" },
    { ArtifactLib::ArtifactType::NECKLACE_OF_DRAGONTEETH, "necklace_of_dragonteeth" },
    { ArtifactLib::ArtifactType::CELESTIAL_NECKLACE_OF_BLISS, "celestial_necklace_of_bliss" },
    { ArtifactLib::ArtifactType::NECKLACE_OF_SWIFTNESS, "necklace_of_swiftness" },
    { ArtifactLib::ArtifactType::CENTAURS_AXE, "centaurs_axe" },
    { ArtifactLib::ArtifactType::TITANS_GLADIUS, "titans_gladius" },
    { ArtifactLib::ArtifactType::SWORD_OF_JUDGEMENT, "sword_of_judgement" },
    { ArtifactLib::ArtifactType::SHIELD_OF_THE_DWARVEN_LORDS, "shield_of_the_dwarven_lords" },
    { ArtifactLib::ArtifactType::DRAGON_SCALE_SHIELD, "dragon_scale_shield" },
    { ArtifactLib::ArtifactType::SENTINELS_SHIELD, "sentinels_shield" },
    { ArtifactLib::ArtifactType::RIB_CAGE, "rib_cage" },
    { ArtifactLib::ArtifactType::DRAGON_SCALE_ARMOR, "dragon_scale_armor" },
    { ArtifactLib::ArtifactType::TITANS_CUIRASS, "titans_cuirass" },
    { ArtifactLib::ArtifactType::QUIET_EYE_OF_THE_DRAGON, "quiet_eye_of_the_dragon" },
    { ArtifactLib::ArtifactType::EQUESTRIAN_GLOVES, "equestrian_gloves" },
    { ArtifactLib::ArtifactType::RING_OF_VITALITY, "ring_of_vitality" },
    { ArtifactLib::ArtifactType::RING_OF_WAYFARER, "ring_of_wayfarer" },
    { ArtifactLib::ArtifactType::RING_OF_LIFE, "ring_of_life" },
    { ArtifactLib::ArtifactType::DRAGONBONE_GREAVES, "dragonbone_greaves" },
    { ArtifactLib::ArtifactType::SANDALS_OF_THE_SAINT, "sandals_of_the_saint" },
    { ArtifactLib::ArtifactType::BOOTS_OF_SPEED, "boots_of_speed" } };

/*
 * Battle
 */
const std::map<ProjectLib::BattleObstacleType, std::string> BATTLE_OBSTACLE_TYPE_TO_STRING{
    { ProjectLib::BattleObstacleType::ROCK, "rock" },
    { ProjectLib::BattleObstacleType::TREE, "tree" },
    { ProjectLib::BattleObstacleType::BUSH, "bush" } };

const std::string HEXAGON_SPRITE_DEFAULT_PATH = "Sprites/Battle/Auxiliary/Hexagon.png";
const std::string HEXAGON_MOVEMENT_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Movement.png";
const std::string HEXAGON_ATTACK_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Attack.png";

/*
 * Magic
 */
const std::map<ProjectLib::SpellType, std::string> SPELL_TYPE_TO_STRING{
    { ProjectLib::SpellType::MAGIC_ARROW, "Magic_Arrow" },
    { ProjectLib::SpellType::LIGHTNING_BOLT, "Lightning_Bolt" },
    { ProjectLib::SpellType::DESTROY_UNDEAD, "Destroy_Undead" } };

/*
 * Units
 */
const std::map<UnitLib::WarMachineUnitType, std::string> WAR_MACHINE_TYPE_TO_STRING{
    { UnitLib::WarMachineUnitType::BALLISTA, "Ballista" },
    { UnitLib::WarMachineUnitType::AMMO_CART, "Ammo_Cart" },
    { UnitLib::WarMachineUnitType::FIRST_AID_TENT, "First_Aid_Tent" },
    { UnitLib::WarMachineUnitType::CATAPULT, "Catapult" } };

const std::map<UnitLib::ConfluxUnitType, std::string> CONFLUX_UNIT_TYPE_TO_STRING{
    { UnitLib::ConfluxUnitType::PIXIE, "Pixie" },
    { UnitLib::ConfluxUnitType::AIR_ELEMENTAL, "Air_Elemental" },
    { UnitLib::ConfluxUnitType::WATER_ELEMENTAL, "Water_Elemental" },
    { UnitLib::ConfluxUnitType::FIRE_ELEMENTAL, "Fire_Elemental" },
    { UnitLib::ConfluxUnitType::EARTH_ELEMENTAL, "Earth_Elemental" },
    { UnitLib::ConfluxUnitType::PSYCHIC_ELEMENTAL, "Psychic_Elemental" },
    { UnitLib::ConfluxUnitType::FIREBIRD, "Firebird" } };

const std::map<UnitLib::CastleUnitType, std::string> CASTLE_UNIT_TYPE_TO_STRING{
    { UnitLib::CastleUnitType::PIKEMAN, "Pikeman" },
    { UnitLib::CastleUnitType::ARCHER, "Archer" },
    { UnitLib::CastleUnitType::GRIFFIN, "Griffin" },
    { UnitLib::CastleUnitType::SWORDSMAN, "Swordsman" },
    { UnitLib::CastleUnitType::MONK, "Monk" },
    { UnitLib::CastleUnitType::CAVALIER, "Cavalier" },
    { UnitLib::CastleUnitType::ANGEL, "Angel" } };

/*
 * Resource
 */
const std::map<ProjectLib::ResourceType, std::string> RESOURCE_TYPE_TO_STRING{
    { ProjectLib::ResourceType::TIMBER, "timber" },
    { ProjectLib::ResourceType::MERCURY, "mercury" },
    { ProjectLib::ResourceType::STONE, "stone" },
    { ProjectLib::ResourceType::SULFUR, "sulfur" },
    { ProjectLib::ResourceType::CRYSTAL, "crystal" },
    { ProjectLib::ResourceType::GEMSTONE, "gemstone" },
    { ProjectLib::ResourceType::MONEY, "money" } };

/*
 * Building
 */
const std::map<ProjectLib::BuildingType, std::string> BUILDING_TYPE_TO_STRING{
    { ProjectLib::BuildingType::BARRACKS, "barracks" },
    { ProjectLib::BuildingType::BLACKSMITH, "blacksmith" } };

/*
 * Terrain
 */
const std::map<ProjectLib::Terrain, std::string> TERRAIN_TYPE_TO_STRING{
    { ProjectLib::Terrain::GRASS, "tgrb000" },
    { ProjectLib::Terrain::DIRT, "tdtb000" },
    { ProjectLib::Terrain::MOSTLY_GRASS, "tgrb022" },
    { ProjectLib::Terrain::ROCKS, "trob000" },
    { ProjectLib::Terrain::ROCKS_CRUSHED, "trob024" },
    { ProjectLib::Terrain::SAND, "tsub000" } };

// const std::map<ProjectLib

}  // namespace SpriteNameLib