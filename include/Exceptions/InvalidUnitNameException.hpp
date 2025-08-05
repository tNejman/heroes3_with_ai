#pragma once

#include <exception>
#include <string>

class InvalidUnitNameException : public std::exception {
 private:
  std::string message;

 public:
  InvalidUnitNameException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};