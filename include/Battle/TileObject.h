#pragma once
// Autor: Tomasz Naszkowski
/* Zawarość klasy TileObject:
  - klasa TileObject jest interfajsem dla obiektów, które mogą być umieszczane na kafelkach w grze.
*/
#include <array>
#include <memory>
#include <string>
#include <vector>

class TileObject {
 private:
  const bool traversable_;
  const std::string name_;

 public:
  TileObject() noexcept;
  TileObject( const std::string& name ) noexcept;
  TileObject( bool traversable ) noexcept;
  TileObject( bool traversable, const std::string& name ) noexcept;

  [[nodiscard]] bool isTraversable() const noexcept;
  [[nodiscard]] const std::string& getName() const noexcept;
};