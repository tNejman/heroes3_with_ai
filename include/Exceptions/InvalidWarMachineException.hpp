#pragma once

#include <exception>
#include <string>

class InvalidWarMachineException : public std::exception {
 private:
  std::string message;

 public:
  InvalidWarMachineException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};