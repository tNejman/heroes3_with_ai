#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy BattleField:
  - Klasa BattleField odpowiada za zarządzanie polem bitwy, w tym za przesuwanie jednostek,
  - dodawanie przeszkód i sprawdzanie, czy jednostka może dojść gdzieś.
  - Pole bitwy jest reprezentowane jako graf gdzie można poruszać się w 6 kierunkach.
*/
// #include <SFML/Graphics.hpp>

#include <algorithm>
#include <array>
#include <memory>
#include <queue>
#include <vector>

#include "Battle/Tile.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/GridTile.h"

class BattleField {
 private:
  std::array<std::array<std::shared_ptr<Tile>, ProjectLib::MAP_HEIGHT_BF>, ProjectLib::MAP_WIDTH_BF> battle_grid_;
  // battle_grid[width][height]
  std::shared_ptr<GridTile> background_;

  [[nodiscard]] bool getIfCoordsInBounds( const CoordPair& coords ) const noexcept;

 public:
  BattleField( std::shared_ptr<GridTile> background );
  ~BattleField();

  std::vector<std::shared_ptr<Tile>> getTileNeighbours( const CoordPair coords );
  std::vector<std::shared_ptr<Tile>> getTileNeighbours( const std::shared_ptr<Tile> tile );
  std::shared_ptr<Tile> getTileByProxy( CoordPair coords );
  // int createRandomObstacles( int amount );         // TODO
  std::vector<CoordPair> getCoordPairs( CoordPair coords );

  std::shared_ptr<GridTile> getBackground();
  // @Warning do not use method getBattleGrid(); the only safe access to tiles i via getTileByProxy()
  // std::array<std::array<std::shared_ptr<Tile>, MAP_HEIGHT_BF>, MAP_WIDTH_BF>& getBattleGrid() = delete;
  void eraseEmptyTiles();
};