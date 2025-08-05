#pragma once

#include <stdint.h>

#include <string>

namespace SpriteNumericLib {

constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_LEFT = 12u;
constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_RIGHT = 12u;
constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_UP = 9u;
constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_DOWN = 9u;

constexpr uint32_t WINDOW_WIDTH = 800;
constexpr uint32_t WINDOW_HEIGHT = 600;

constexpr uint32_t TERRAIN_SPRITE_HEIGHT = 32;
constexpr uint32_t TERRAIN_SPRITE_WIDTH = 32;

constexpr uint32_t HERO_SPRITE_WIDTH = 95;
constexpr uint32_t HERO_SPRITE_HEIGHT = 64;

constexpr uint32_t HEXAGON_SPRITE_WIDTH = 48;
constexpr uint32_t HEXAGON_SPRITE_HEIGHT = 56;

constexpr uint32_t BATTLE_MAP_SPRITE_X_DELTA = 48;
constexpr uint32_t BATTLE_MAP_SPRITE_Y_DELTA = 86;

constexpr uint32_t BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD = 24;
constexpr uint32_t BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD = 24;
constexpr uint32_t BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD_UNIT = 64;

constexpr uint32_t BATTLE_MAP_SPRITE_ADJUST_EVEN_X = 24;
constexpr uint32_t BATTLE_MAP_SPRITE_ADJUST_EVEN_Y = 43;

constexpr double HEXAGON_SPRITE_MAX_RADIUS = HEXAGON_SPRITE_WIDTH / 2.0;

const std::string WORLD_MAP_INPUT_PATH = "in/world_map_in_2.txt";

const std::string WINDOW_NAME = "Heroes3App";

}  // namespace SpriteNumericLib