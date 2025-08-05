#include "Battle/TileObject.h"

TileObject::TileObject() noexcept
    : traversable_( false ), name_( "" ) {};

TileObject::TileObject( const std::string& name ) noexcept
    : traversable_( false ), name_( name ) {};

TileObject::TileObject( bool traversable ) noexcept
    : traversable_( traversable ), name_( "" ) {};

TileObject::TileObject( bool traversable, const std::string& name ) noexcept
    : traversable_( traversable ), name_( name ) {}

[[nodiscard]] bool TileObject::isTraversable() const noexcept {
  return traversable_;
}

[[nodiscard]] const std::string& TileObject::getName() const noexcept {
  return name_;
}
