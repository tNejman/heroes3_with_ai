#pragma once

#include <array>
// chorno is required for this to work: stringstream::operator>>(const std::string& str)
#include <chrono>
#include <fstream>
#include <string>

#include "Exceptions/DamagedSaveException.hpp"
#include "Exceptions/InvalidInputFileException.hpp"
#include "Miscellaneous/ProjectLib.h"

template <typename TypeLoaded, typename TypeContainer>
class ILoader {
 protected:
  TypeContainer container_;

  virtual void resetCounters() = 0;
  virtual void moveWordToContainer( const int word ) = 0;
  virtual std::shared_ptr<TypeLoaded> getObjectFromContainer() = 0;

  bool isNumber( const std::string& s ) const {
    return !s.empty() &&
           std::find_if( s.begin(), s.end(), []( unsigned char c ) { return !std::isdigit( c ); } ) == s.end();
  }

 public:
  ILoader() {}
  virtual ~ILoader() = default;

  std::shared_ptr<TypeLoaded> load( const std::string& path ) {
    resetCounters();
    std::ifstream file( path );
    if ( !file.is_open() ) {
      throw InvalidInputFileException( "ILoader descendant could not open file with data; path:" + path );
    }

    std::string line;
    while ( std::getline( file, line ) ) {
      std::stringstream ss( line );
      std::string word;

      while ( ss >> word ) {
        // while ( word = ss.str() ) {
        if ( !isNumber( word ) ) {
          throw InvalidInputFileException( "Invalid character in input file is not a number: " + word );
        }
        const int word_int = std::stoi( word );
        moveWordToContainer( word_int );
      }
      //
    }
    file.close();
    return getObjectFromContainer();
  }
};