#pragma once
// Autor: Tomasz Nejman
// zawartość: zawiera stałe używane w grze

#include <SFML/Graphics.hpp>
#include <array>
#include <map>
#include <unordered_map>

#include "Miscellaneous/Coords.h"

namespace ProjectLib {

/*
====== WORLD MAP ======
*/

constexpr uint32_t WORLD_MAP_WIDTH = 100;   // 20
constexpr uint32_t WORLD_MAP_HEIGHT = 100;  // 20

constexpr double INF_SCORE = 1e9;

constexpr std::array<ShiftPair, 8> WORLD_MAP_DIRECTIONS = {
    ShiftPair( -1, 1 ),   // up left
    ShiftPair( 0, 1 ),    // up
    ShiftPair( 1, 1 ),    // up right
    ShiftPair( 1, 0 ),    // right
    ShiftPair( 1, -1 ),   // down right
    ShiftPair( 0, -1 ),   // down
    ShiftPair( -1, -1 ),  // down left
    ShiftPair( -1, 0 )    // left
};

enum class CharacterMoveDirection : int {
  UP_LEFT = 0,
  UP = 1,
  UP_RIGHT = 2,
  RIGHT = 3,
  DOWN_RIGHT = 4,
  DOWN = 5,
  DOWN_LEFT = 6,
  LEFT = 7,
  NONE = 8
};

enum class BuildingType {
  BARRACKS,
  BLACKSMITH
};

/*
====== BATTLE ======
*/

constexpr uint32_t MAP_WIDTH_BF = 15;
constexpr uint32_t MAP_HEIGHT_BF = 11;

enum class BattleState {
  PREPPING,  //@Warning remove later possibly
  //   DEFENDING,
  MOVING,
  ATTACKING,
  //   CASTING_SPELL,
  //   SELECTING_TARGET
  WIN_ATTACKER,
  WIN_DEFENDER
};

enum BATTLE_DIRECTIONS : int {
  UR,
  R,
  DR,
  DL,
  L,
  UL
};

// {0,0} in the middle, top and bottom rows are shifted right
constexpr std::array<ShiftPair, 6> EVEN_DIRECTIONS_BATTLE = {
    ShiftPair( 1, 1 ), ShiftPair( 1, 0 ), ShiftPair( 1, -1 ),
    //         UR                R                 DR
    ShiftPair( 0, -1 ), ShiftPair( -1, 0 ), ShiftPair( 0, 1 )
    //          DL                 L               UL
};
/*
   EVEN_DIRECTIONS_BATTLE visual below
        {0, 1}, {1, 1},
   {-1,0},         {1, 0},
        {0,-1}, {1,-1}
*/

// {0,0} in the middle, top and bottom rows are shifted left
constexpr std::array<ShiftPair, 6> ODD_DIRECTIONS_BATTLE = {
    ShiftPair( 0, 1 ), ShiftPair( 1, 0 ), ShiftPair( 0, -1 ),
    //          UR                 R                DR
    ShiftPair( -1, -1 ), ShiftPair( -1, 0 ), ShiftPair( -1, 1 )
    //          DL                 L                UL
};
/*
    ODD_DIRECTIONSS_BATTLE visual below
        {-1, 1}, { 0, 1},
    {-1, 0},        { 1, 0},
        {-1,-1}, {0, -1}
*/

constexpr CoordPair BATTLE_MAP_TOP_RIGHT_COORDS = CoordPair( MAP_WIDTH_BF - 1, MAP_HEIGHT_BF - 1 );
constexpr CoordPair BATTLE_MAP_NOT_FOUND_COORDS = CoordPair( 69'420u, 69'420u );
// constexpr CoordPair BATTLE_MAP_PASS_COORDS = CoordPair( 100u, 100u );

enum class BattleObstacleType {
  ROCK,
  TREE,
  BUSH
};

/*
====== TERRAIN ======
*/

enum class Terrain {
  GRASS = 0,
  DIRT = 1,
  MOSTLY_GRASS = 2,
  ROCKS = 3,
  ROCKS_CRUSHED = 4,
  SAND = 5
};

const std::unordered_map<Terrain, double> TERRAIN_MOVEMENT_PENALTY = {
    { Terrain::GRASS, 1.0 },
    { Terrain::DIRT, 1.2 } };

/*
====== CHARACTER ======
*/

constexpr uint32_t SECONDARY_SKILLS_SLOTS_COUNT = 8;
constexpr uint32_t EQUIPMENT_SLOTS_COUNT = 14;
constexpr uint32_t MAX_BACKPACK_SIZE = 64;
constexpr uint32_t MAX_PARTY_SIZE = 7;

enum class CharacterType {
  FIRE_HERO,
  BLACK_HERO_WHITE_HORSE
};

enum class EquipmentSlots {
  HELMET = 0,
  CAPE = 1,
  NECKLACE = 2,
  WEAPON = 3,
  SHIELD = 4,
  TORSO = 5,
  RING = 6,
  RING_1 = 7,
  RING_2 = 8,
  FEET = 9,
  MISC = 10,
  MISC_1 = 10,
  MISC_2 = 11,
  MISC_3 = 12,
  MISC_4 = 13,
  MISC_5 = 14
};

constexpr uint32_t EXPERIENCE_THRESHHOLD_ARR_CAP = 10u;
constexpr std::array<uint32_t, 11> EXPERIENCE_THRESHHOLDS = {
    0,      // 0
    0,      // 1
    1000,   // 2
    2000,   // 3
    3200,   // 4
    4600,   // 5
    6200,   // 6
    8000,   // 7
    10000,  // 8
    12200,  // 9
    14700   // 10 and above
};

const std::map<uint32_t, uint32_t> SpeedToMovement = {
    { 3, 1500 },
    { 4, 1560 },
    { 5, 1630 },
    { 6, 1700 },
    { 7, 1760 },
    { 8, 1830 },
    { 9, 1900 },
    { 10, 1960 },
    { 11, 2000 }  // accounts for 11 or more
};

enum class SecondarySkillType : int {
  AIR_MAGIC = 0,
  FIRE_MAGIC = 1,
  EARTH_MAGIC = 2,
  WATER_MAGIC = 3
};

enum class SecondarySkillLevel : int {
  BASIC = 0,
  ADVANCED = 1,
  EXPERT = 2
};

/*
====== MAGIC ======
*/
enum class MagicSchool : int {
  EARTH = 0,
  AIR = 1,
  FIRE = 2,
  WATER = 3
};

enum class SpellType : int {
  MAGIC_ARROW = 0,
  LIGHTNING_BOLT = 1,
  DESTROY_UNDEAD = 2
};

/*
===== RENDERING =====
*/

typedef uint32_t FrameCount;

// constexpr sf::Time FRAME_DURATION = sf::seconds( 1.f / 30.f );

constexpr FrameCount KEY_BUFFER_DURATION = 5;

constexpr sf::Keyboard::Key W = sf::Keyboard::Key::W;
constexpr sf::Keyboard::Key S = sf::Keyboard::Key::S;
constexpr sf::Keyboard::Key A = sf::Keyboard::Key::A;
constexpr sf::Keyboard::Key D = sf::Keyboard::Key::D;
constexpr std::array<sf::Keyboard::Key, 4> MOVEMENT_KEYS = { W, S, A, D };

const std::map<sf::Keyboard::Key, std::vector<sf::Keyboard::Key>> VALID_DIAGONAL_MOVE_COMP = {
    { W, { A, D } },
    { S, { A, D } },
    { A, { W, S } },
    { D, { W, S } } };

/*
====== MISC ======
*/

constexpr std::size_t AMOUNT_OF_RESOURCES = 7;

enum class GameState {
  OVERWORLD,
  BATTLE,
  MENU
};

constexpr uint32_t FACTION_FORGE_ID_MARKER = 0;
constexpr uint32_t FACTION_CONFLUX_ID_MARKER = 1;
constexpr uint32_t FACTION_CASTLE_ID_MARKER = 2;

/*
====== MINIMAX ======
*/

constexpr uint32_t MINIMAX_MAX_DEPTH = 5u;

/*
====== SAVING AND LOADING ======
*/
const std::string CHARACTER_SAVE_START_MARKER = "CHARACTER";

/*
====== RESOURCE ======
*/
enum class ResourceType {
  TIMBER,
  MERCURY,
  STONE,
  SULFUR,
  CRYSTAL,
  GEMSTONE,
  MONEY
};

}  // namespace ProjectLib
