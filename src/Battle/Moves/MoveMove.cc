#include "Battle/Moves/MoveMove.h"

MoveMove::MoveMove( CoordPair old_coords, CoordPair new_coords )
    : Move(), old_coords_( old_coords ), new_coords_( new_coords ) {};

MoveMove::~MoveMove() {}

void MoveMove::execute(std::shared_ptr<Battle> battle) {
  if(battle->getUnitFromCoords(old_coords_) != nullptr){
    battle->move( battle->getUnitFromCoords(old_coords_), new_coords_ );
    battle->setBattleState(ProjectLib::BattleState::ATTACKING);
  }
}

CoordPair MoveMove::destinationCoords() const {
  return new_coords_;
}

std::string MoveMove::getPath() const {
  return "Sprites/Battle/Auxiliary/Hexagon_Movement.png";
}

std::string MoveMove::getInfo(std::shared_ptr<Battle> battle) const {
  if(battle->getUnitFromCoords(old_coords_) == nullptr){
    std::string path = "move from: [";
    path += std::to_string(old_coords_.x_);
    path += ", ";
    path +=  std::to_string(old_coords_.y_);
    path += "] to [" ;
    path += std::to_string(old_coords_.x_);
    path += ", ";
    path += std::to_string(old_coords_.y_);
    path += "]\n";
    return path;
  }
  else{
  std::string info = "Unit: ";
  info += battle->getUnitFromCoords(old_coords_)->getUnit()->getName();

  auto x = battle->getUnitFromCoords(old_coords_)->getCoordsInBattle().x_;
  auto y = battle->getUnitFromCoords(old_coords_)->getCoordsInBattle().y_;
  info += ", old coords: (x=" + std::to_string( x ) + ",y=" + std::to_string( y ) + "), ";

  auto xn = new_coords_.x_;
  auto yn = new_coords_.y_;
  info += ", new coords: (x=" + std::to_string( xn ) + ",y=" + std::to_string( yn ) + "), ";

  return info;
  }
}

std::shared_ptr<Move> MoveMove::copy() const {
  return std::make_shared<MoveMove>( old_coords_, new_coords_ );
}
