#pragma once

#include <exception>
#include <string>

class InvalidImageException : public std::exception {
 private:
  std::string message;

 public:
  InvalidImageException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};