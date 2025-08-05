#pragma once

#include <exception>
#include <string>

class InvalidTerrainException : public std::exception {
 private:
  std::string message;

 public:
  InvalidTerrainException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};