#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Resource pozwala na zarządzanie zasobami

// #include <SFML/Graphics.hpp>

#include "Exceptions/UnknownStateException.hpp"
#include "Graphic/Printable.h"
#include "Miscellaneous/ProjectLib.h"

class Resource : public Printable {
 private:
  ProjectLib::ResourceType type_;
  uint32_t amount_;

 public:
  Resource( ProjectLib::ResourceType type, uint32_t amount );
  sf::Texture& accept( Visitor& v ) const override;

  [[nodiscard]] ProjectLib::ResourceType getType() const noexcept;
  [[nodiscard]] uint32_t getAmount() const noexcept;
};