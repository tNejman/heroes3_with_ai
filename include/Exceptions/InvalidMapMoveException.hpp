#pragma once

#include <exception>
#include <string>

class InvalidMapMoveException : public std::exception {
 private:
  std::string message;

 public:
  InvalidMapMoveException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};