#pragma once

#include <exception>
#include <string>

class InvalidSecondarySkillException : public std::exception {
 private:
  std::string message;

 public:
  InvalidSecondarySkillException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};