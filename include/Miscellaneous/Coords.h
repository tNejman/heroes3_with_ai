#pragma once

#include <stdint.h>

#include <cmath>
#include <concepts>
#include <initializer_list>
#include <iostream>

#include "Exceptions/CoordinateOutOfBoutdsException.hpp"

// works, just not used
// template <typename T>
// concept UnsignedInt = std::unsigned_integral<T>;

/**
 * @brief
 * ShiftPair represents a shift whether positive or negative
 * in cartesian coordinate system
 *
 * @param dx_
 * Shift either left or right
 * @param dy_
 * Shift either up or down
 */
class ShiftPair {
 public:
  int dx_;
  int dy_;

  ShiftPair( std::integral auto dx, std::integral auto dy ) noexcept
      : dx_( dx ), dy_( dy ) {}

  // Constructor below must be defined here, because ProjectLib.h uses it before Coords.cc is compiled, hence "constexpr"
  inline explicit constexpr ShiftPair( int dx, int dy ) noexcept
      : dx_( dx ), dy_( dy ) {}

  ~ShiftPair() noexcept = default;

  ShiftPair& operator=( const ShiftPair& other ) noexcept;
  ShiftPair operator+( const ShiftPair& other ) noexcept;
  ShiftPair operator-( const ShiftPair& other ) noexcept;
  bool operator==( const ShiftPair& other ) const noexcept;
  bool operator!=( const ShiftPair& other ) const noexcept;

  std::string toString() const noexcept;
  std::string toStringExtended() const noexcept;
};

/**
 * @brief
 * CoordPair represents a pair of strictly positive
 * coordinates in cartesian coordinate system
 *
 * @param x_
 * x coordinate
 * @param y_
 * y coordinate
 */
class CoordPair {
 public:
  uint32_t x_;
  uint32_t y_;

  CoordPair( std::unsigned_integral auto x, std::unsigned_integral auto y )
      : x_( x ), y_( y ) {}

  // Constructor below must be defined here, because ProjectLib.h uses it before Coords.cc is compiled, hence constexpr
  inline explicit constexpr CoordPair( uint32_t x, uint32_t y ) noexcept
      : x_( x ), y_( y ) {}

  CoordPair( const CoordPair& other ) noexcept;

  CoordPair( CoordPair&& other ) noexcept;  // R-value of course cannot be const as it is moved

  ~CoordPair() noexcept = default;

  CoordPair& operator=( const CoordPair& other ) noexcept;
  CoordPair operator+( const CoordPair& other ) noexcept;
  CoordPair operator+( const ShiftPair& shift );
  CoordPair operator-( const CoordPair& other );
  CoordPair& operator+=( const CoordPair& other ) noexcept;
  CoordPair& operator+=( const ShiftPair& shift );
  friend std::ostream& operator<<( std::ostream& os, const CoordPair& coord );
  bool operator==( const CoordPair& other ) const noexcept;
  bool operator!=( const CoordPair& other ) const noexcept;

  // @Warning lexicographical order, please do not use without a thought
  bool operator<( const CoordPair& other ) const noexcept;
  bool operator<=( const CoordPair& other ) const noexcept;
  bool operator>( const CoordPair& other ) const noexcept;
  bool operator>=( const CoordPair& other ) const noexcept;

  double distanceFrom( const CoordPair& other ) const noexcept;

  std::string toString() const noexcept;
  std::string toStringExtended() const noexcept;
};