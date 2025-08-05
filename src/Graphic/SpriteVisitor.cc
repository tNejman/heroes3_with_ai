#include "Graphic/SpriteVisitor.h"

// Nazwa przedmiotu jako path do Sprita
//
//====================================

sf::Texture& SpriteVisitor::visit( const Artifact& e ) {
  std::string path_to_sprite = SpriteNameLib::SPRITE_ARTIFACTS_DIR_PREFIX;
  path_to_sprite += SpriteNameLib::ARTIFACT_TYPE_TO_STRING.find( e.getType() )->second;
  path_to_sprite += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  return FindTexture( path_to_sprite );
}

sf::Texture& SpriteVisitor::visit( const BattleObstacle& e ) {
  std::string path_to_sprite = SpriteNameLib::SPRITE_OBSTACLES_DIR_PREFIX;
  path_to_sprite += SpriteNameLib::BATTLE_OBSTACLE_TYPE_TO_STRING.find( e.getType() )->second;
  path_to_sprite += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  return FindTexture( path_to_sprite );
}

sf::Texture& SpriteVisitor::visit( const Character& e ) {
  std::string path_to_sprite = SpriteNameLib::SPRITE_HEROES_DIR_PREFIX;
  path_to_sprite += SpriteNameLib::CHARACTER_TYPE_TO_STRING.find( e.getCharacterType() )->second;
  path_to_sprite += SpriteNameLib::CHARACTER_ORIENTATION_TO_STRING.find( e.getOrientation() )->second;
  path_to_sprite += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  sf::Texture& tex_temp = FindTexture( path_to_sprite );
  assert( tex_temp.getSize().x == SpriteNumericLib::HERO_SPRITE_WIDTH );
  assert( tex_temp.getSize().y == SpriteNumericLib::HERO_SPRITE_HEIGHT );
  return tex_temp;
}

sf::Texture& SpriteVisitor::visit( const SecondarySkill& e ) {
  std::string path_to_sprite = SpriteNameLib::SPRITE_SECONDARY_SKILLS_DIR_PREFIX;
  path_to_sprite += SpriteNameLib::SECONDARY_SKILL_TYPE_TO_STRING.find( e.getType() )->second;
  path_to_sprite += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  return FindTexture( path_to_sprite );
}

sf::Texture& SpriteVisitor::visit( const Spell& e ) {
  std::string path_to_sprite = SpriteNameLib::SPRITE_SPELLS_DIR_PREFIX;
  path_to_sprite += SpriteNameLib::SPELL_TYPE_TO_STRING.find( e.getType() )->second;
  path_to_sprite += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  return FindTexture( path_to_sprite );
}

// sf::Texture& SpriteVisitor::visit(const SpellBook& e) {
//     std::string path = "Sprites/spellbooks/Spellbook.png";
//     return FindTexture(path);
// }

sf::Texture& SpriteVisitor::visit( const Unit& e ) {
  std::string path_to_sprite = SpriteNameLib::SPRITE_UNITS_DIR_PREFIX;
  UnitLib::UnitType unit_type = e.getUnitType();
  // try {
  //   auto machine_type = std::get<UnitLib::WarMachineUnitType>( unit_type );
  //   path_to_sprite += SpriteNameLib::WAR_MACHINE_TYPE_TO_STRING.at( machine_type );
  // } catch ( const std::bad_variant_access& ) {
  //   try
  // }
  std::visit( UnitLib::UnitTypeForwardLambdaCombiner{
                  [&path_to_sprite]( UnitLib::WarMachineUnitType machine_type ) { path_to_sprite += SpriteNameLib::WAR_MACHINE_TYPE_TO_STRING.at( machine_type ); },
                  [&path_to_sprite]( UnitLib::CastleUnitType castle_type ) { path_to_sprite += SpriteNameLib::CASTLE_UNIT_TYPE_TO_STRING.at( castle_type ); },
                  [&path_to_sprite]( UnitLib::ConfluxUnitType conflux_type ) { path_to_sprite += SpriteNameLib::CONFLUX_UNIT_TYPE_TO_STRING.at( conflux_type ); } },
              unit_type );

  path_to_sprite += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  return FindTexture( path_to_sprite );
}

sf::Texture& SpriteVisitor::visit( const Resource& e ) {
  std::string path_to_file = SpriteNameLib::SPRITE_RESOURCE_DIR_PREFIX;
  path_to_file += SpriteNameLib::RESOURCE_TYPE_TO_STRING.at( e.getType() );
  path_to_file += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  return FindTexture( path_to_file );
}

sf::Texture& SpriteVisitor::visit( const Building& e ) {
  std::string path_to_file = SpriteNameLib::SPRITE_BUILDINGS_DIR_PREFIX;
  path_to_file += SpriteNameLib::BUILDING_TYPE_TO_STRING.at( e.getType() );
  path_to_file += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  return FindTexture( path_to_file );
}

sf::Texture& SpriteVisitor::visit( const ProjectLib::Terrain& e ) {
  std::string path_to_file = SpriteNameLib::SPRITE_TERRAIN_TILES_DIR_PREFIX;
  path_to_file += SpriteNameLib::TERRAIN_TYPE_TO_STRING.at( e );
  path_to_file += SpriteNameLib::SPRITE_FILE_TYPE_SUFFIX;
  sf::Texture& tex_temp = FindTexture( path_to_file );
  assert( tex_temp.getSize().x == SpriteNumericLib::TERRAIN_SPRITE_WIDTH );
  assert( tex_temp.getSize().y == SpriteNumericLib::TERRAIN_SPRITE_HEIGHT );
  return tex_temp;
}

sf::Texture& SpriteVisitor::visit( const OverworldObstacle& e ) {
  std::string path = "Sprites/terrain/Overworld_obstacles/" + e.getName() + ".png";
  sf::Texture& tex_temp = FindTexture( path );
  assert( tex_temp.getSize().x == 32 );
  assert( tex_temp.getSize().y == 32 );
  return FindTexture( path );
  // @TODO fix by making an enum with types and not use plain "name"
}

// sf::Texture& SpriteVisitor::visit(const WorldMap& e) @warning done in Renderer
// sf::Texture& SpriteVisitor::visit(const Player& e) @warning done in Renderer
// sf::Texture& SpriteVisitor::visit(const Castle& e) @TODO

sf::Texture& SpriteVisitor::visit( const Battle& e ) {
  // CmBkDrTr.png
  sf::Image combined_image;
  std::string path = "Sprites/Battle_Backgrounds/CmBkDrTr.png";
  if ( !combined_image.loadFromFile( path ) ) {
    throw InvalidImageException( "SpriteVisitor::visit(Battle) -> Failed to load battle background image: " + path );
  }
  const auto units_sorted = e.getUnitsInBattleSortedToPrint();
  const auto units_defender = e.getDefendingArmy();

  std::pair<sf::Texture, std::string> pair_image = getBattleHexagons( e.getPossibleMoves() );
  sf::Image image_hex = pair_image.first.copyToImage();
  path += pair_image.second;
  (void)combined_image.copy( image_hex, sf::Vector2u( 0, 0 ), sf::IntRect(), true );

  for ( const auto& unit : units_sorted ) {
    CoordPair unit_coords = unit->getCoordsInBattle();
    uint32_t offset_x, offset_y;
    offset_x = SpriteNumericLib::BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD + unit_coords.x_ * SpriteNumericLib::BATTLE_MAP_SPRITE_X_DELTA;
    offset_y = SpriteNumericLib::BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD_UNIT + ( 4 - unit_coords.y_ / 2 ) * SpriteNumericLib::BATTLE_MAP_SPRITE_Y_DELTA;
    if ( unit_coords.y_ % 2 == 0 ) {
      offset_x += SpriteNumericLib::BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
      offset_y += SpriteNumericLib::BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
    }
    sf::Image image_tmp;
    std::string unit_path = "Sprites/units/" + unit->getUnit()->getName() + ".png";
    if ( !image_tmp.loadFromFile( unit_path ) ) {
      throw InvalidImageException( "SpriteVisitor::visit(Battle) -> Failed to load image: " + unit_path );
    }
    if ( std::find( units_defender.begin(), units_defender.end(), unit ) != units_defender.end() ) {
      image_tmp.flipHorizontally();
    }
    (void)combined_image.copy( image_tmp, sf::Vector2u( offset_x, offset_y ), sf::IntRect(), true );
    path = path + "unit" + unit->getUnit()->getName() + std::to_string( unit->getCoordsInBattle().x_ ) + std::to_string( unit->getCoordsInBattle().y_ );
  }

  sf::Texture combined_texture;
  if ( !combined_texture.loadFromImage( combined_image ) ) {
    throw InvalidTextureException( "SpriteVisitor::visit(Battle) -> Failed to load texture from image" );
  }
  if ( textures_.find( path ) == textures_.end() ) {
    textures_.emplace( path, combined_texture );
  }

  return textures_[path];
}

sf::Texture& SpriteVisitor::FindTexture( const std::string& path ) {
  if ( textures_.find( path ) == textures_.end() ) {
    sf::Texture texture;
    if ( !texture.loadFromFile( path ) )
      throw InvalidTextureException( "SpriteVisitor::FindTexture -> Failed to load texture from: " + path );
    textures_.emplace( path, texture );
  }
  return textures_[path];
}

sf::Image SpriteVisitor::mirrorImageHorizontally( const sf::Image& original ) const {
  sf::Vector2u size = original.getSize();
  sf::Image flipped( { size.x, size.y }, sf::Color::Transparent );

  for ( unsigned int y = 0; y < size.y; ++y ) {
    for ( unsigned int x = 0; x < size.x; ++x ) {
      flipped.setPixel( { size.x - 1 - x, y }, original.getPixel( { x, y } ) );
    }
  }

  return flipped;
}

std::pair<sf::Texture&, std::string> SpriteVisitor::getBattleHexagons( std::vector<std::shared_ptr<Move>> moves ) {
  sf::Image combined_image;
  std::string path1 = "Sprites/Battle_Backgrounds/CmBkDrTr.png";
  if ( !combined_image.loadFromFile( path1 ) ) {
    throw InvalidImageException( "SpriteVisitor::getBattleHexagons -> Failed to load battle background image: " + path1 );
  }
  std::string path = "";
  for ( uint32_t x = 0; x < ProjectLib::MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < ProjectLib::MAP_HEIGHT_BF; ++y ) {
      CoordPair map_tile_coord( x, y );
      uint32_t offset_x_temp, offset_y_temp;
      // set offset for even rows
      offset_x_temp = SpriteNumericLib::BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD + x * SpriteNumericLib::BATTLE_MAP_SPRITE_X_DELTA;
      offset_y_temp = SpriteNumericLib::BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD + ( 5 - y / 2 ) * SpriteNumericLib::BATTLE_MAP_SPRITE_Y_DELTA;

      // adjust if even
      if ( ( y % 2 == 0 ) ) {
        offset_x_temp += SpriteNumericLib::BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
        offset_y_temp += SpriteNumericLib::BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
      }

      sf::Image image_hexagon;
      std::shared_ptr<Move> move_to_print;
      if ( moves.end() != std::find_if( moves.begin(), moves.end(), [&]( const std::shared_ptr<Move> move ) {move_to_print = move ; return move->destinationCoords() == map_tile_coord; } ) ) {
        if ( !image_hexagon.loadFromFile( move_to_print->getPath() ) ) {
          throw InvalidImageException( "SpriteVisitor::getBattleHexagons -> Failed to load image: " + move_to_print->getPath() );
        }
        path += move_to_print->getPath();
      } else {
        if ( !image_hexagon.loadFromFile( SpriteNameLib::HEXAGON_SPRITE_DEFAULT_PATH ) ) {
          throw InvalidImageException( "SpriteVisitor::getBattleHexagons -> Failed to load image: " + SpriteNameLib::HEXAGON_SPRITE_DEFAULT_PATH );
        }
        path += "n";
      }
      try {
        if ( !combined_image.copy( image_hexagon, sf::Vector2u( offset_x_temp, offset_y_temp ), sf::IntRect(), true ) ) {
          throw BadCopyException( "SpriteVisitor::getBattleHexagons -> Copying hexagon onto combined image failed" );
        }
      } catch ( const std::exception& e ) {
        throw BadCopyException( "SpriteVisitor::getBattleHexagons -> Copying hexagon onto combined image failed" );
      }
    }
  }
  sf::Texture combined_texture;
  if ( !combined_texture.loadFromImage( combined_image ) ) {
    throw InvalidTextureException( "SpriteVisitor::getBattleHexagons -> Failed to load texture from image" );
  }
  textures_.emplace( path, combined_texture );

  return std::pair<sf::Texture&, std::string>( textures_[path], path );
}