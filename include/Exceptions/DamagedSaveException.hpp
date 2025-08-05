#pragma once

#include <exception>
#include <string>

class DamagedSaveException : public std::exception {
 private:
  std::string message;

 public:
  DamagedSaveException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};