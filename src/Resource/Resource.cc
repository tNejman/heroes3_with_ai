#include "Resource/Resource.h"

Resource::Resource( ProjectLib::ResourceType type, uint32_t amount )
    : type_( type ), amount_( amount ) {};

sf::Texture& Resource::accept( Visitor& v ) const {
  return v.visit( *this );
}

ProjectLib::ResourceType Resource::getType() const noexcept {
  return this->type_;
}

uint32_t Resource::getAmount() const noexcept {
  return this->amount_;
}
