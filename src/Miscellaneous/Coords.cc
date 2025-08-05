#include "Miscellaneous/Coords.h"
/*
========== ShiftPair ==========
*/

ShiftPair& ShiftPair::operator=( const ShiftPair& other ) noexcept {
  dx_ = other.dx_;
  dy_ = other.dy_;
  return *this;
}

ShiftPair ShiftPair::operator+( const ShiftPair& other ) noexcept {
  return ShiftPair( dx_ + other.dx_, dy_ + other.dy_ );
}

ShiftPair ShiftPair::operator-( const ShiftPair& other ) noexcept {
  return ShiftPair( dx_ - other.dx_, dy_ - other.dy_ );
}

bool ShiftPair::operator==( const ShiftPair& other ) const noexcept {
  return ( dx_ == other.dx_ && dy_ == other.dy_ );
}

bool ShiftPair::operator!=( const ShiftPair& other ) const noexcept {
  return ( dx_ != other.dx_ || dy_ != other.dy_ );
}

std::string ShiftPair::toString() const noexcept {
  return "(dx=" + std::to_string( dx_ ) + ", dy=" + std::to_string( dy_ ) + ")";
}

std::string ShiftPair::toStringExtended() const noexcept {
  return "ShiftPair: (dx=" + std::to_string( dx_ ) + ", dy=" + std::to_string( dy_ ) + ")";
}

/*
========== CoordPair ==========
*/

// template <typename T>
// CoordPair::CoordPair(std::initializer_list<T> init)
// requires std::unsigned_integral<T> {
//   static_assert(init.size() == 2);
//   x_ = init[0];
//   y_ = init[1];
// }

CoordPair::CoordPair( const CoordPair& other ) noexcept
    : x_( other.x_ ), y_( other.y_ ) {};

CoordPair::CoordPair( CoordPair&& other ) noexcept
    : x_( other.x_ ), y_( other.y_ ) {}

CoordPair& CoordPair::operator=( const CoordPair& other ) noexcept {
  if ( this != &other ) {
    x_ = other.x_;
    y_ = other.y_;
  }
  return *this;
}

CoordPair CoordPair::operator+( const CoordPair& other ) noexcept {
  return CoordPair( x_ + other.x_, y_ + other.y_ );
}

CoordPair CoordPair::operator+( const ShiftPair& shift ) {
  int x_tmp = short( x_ ) + shift.dx_;
  int y_tmp = short( y_ ) + shift.dy_;
  if ( x_tmp < 0 || y_tmp < 0 ) {
    throw CoordinateOutOfBoundsException( "CoordPair::operator+ -> Tried to shift coordinates:" + toString() +
                                          " with shift: " + shift.toString() + " resulting in negative coordinates" );
  } else {
    return CoordPair( uint32_t( x_tmp ), uint32_t( y_tmp ) );
  }
}

CoordPair CoordPair::operator-( const CoordPair& other ) {
  int x_tmp = int( x_ ) - int( other.x_ );
  int y_tmp = int( y_ ) - int( other.y_ );
  if ( x_tmp < 0 || y_tmp < 0 ) {
    throw CoordinateOutOfBoundsException( "CoordPair::operator- -> Tried to subtract coordinates:" + other.toString() +
                                          " from : " + toString() + " resulting in negative coordinates" );
  } else {
    return CoordPair( uint32_t( x_tmp ), uint32_t( y_tmp ) );
  }
}

CoordPair& CoordPair::operator+=( const CoordPair& other ) noexcept {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

CoordPair& CoordPair::operator+=( const ShiftPair& shift ) {
  int x_tmp = int( x_ ) + shift.dx_;
  int y_tmp = int( y_ ) + shift.dy_;
  if ( x_tmp < 0 || y_tmp < 0 ) {
    throw CoordinateOutOfBoundsException( "CoordPair::operator+= -> Tried to shift coordinates:" + toString() +
                                          " with shift: " + shift.toString() + " resulting in negative coordinates" );
  } else {
    x_ = uint32_t( x_tmp );
    y_ = uint32_t( y_tmp );
    return *this;
  }
}

std::ostream& operator<<( std::ostream& os, const CoordPair& coord ) {
  os << "(x=" << coord.x_ << ", y=" << coord.y_ << ")";
  return os;
}

bool CoordPair::operator==( const CoordPair& other ) const noexcept {
  return ( x_ == other.x_ && y_ == other.y_ );
}

bool CoordPair::operator!=( const CoordPair& other ) const noexcept {
  return ( x_ != other.x_ || y_ != other.y_ );
}

bool CoordPair::operator<( const CoordPair& other ) const noexcept {
  return ( x_ < other.x_ ) || ( x_ == other.x_ && y_ < other.y_ );
}

bool CoordPair::operator<=( const CoordPair& other ) const noexcept {
  return ( *this == other ) || ( x_ < other.x_ ) || ( x_ == other.x_ && y_ < other.y_ );
}

bool CoordPair::operator>( const CoordPair& other ) const noexcept {
  return ( x_ > other.x_ ) || ( x_ == other.x_ && y_ > other.y_ );
}

bool CoordPair::operator>=( const CoordPair& other ) const noexcept {
  return ( *this == other ) || ( x_ > other.x_ ) || ( x_ == other.x_ && y_ > other.y_ );
}

double CoordPair::distanceFrom( const CoordPair& other ) const noexcept {
  auto x_diff = int( x_ ) - int( other.x_ );
  auto y_diff = int( y_ ) - int( other.y_ );
  return std::hypot( x_diff, y_diff );
}

std::string CoordPair::toString() const noexcept {
  return "(x=" + std::to_string( x_ ) + ", y=" + std::to_string( y_ ) + ")";
}

std::string CoordPair::toStringExtended() const noexcept {
  return "CoordPair: (x=" + std::to_string( x_ ) + ", y=" + std::to_string( y_ ) + ")";
}