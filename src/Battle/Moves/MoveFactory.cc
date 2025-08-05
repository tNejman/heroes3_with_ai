#include "Battle/Moves/MoveFactory.h"

std::vector<std::shared_ptr<Move>> MoveFactory::createMoveMove( std::shared_ptr<Battle> battle ) {
  std::vector<std::shared_ptr<Move>> valid_moves;
  if ( !battle->getUnitInAction() ) return valid_moves;

  CoordPair start = battle->getUnitInAction()->getCoordsInBattle();
  uint32_t max_steps = battle->getUnitInAction()->getSpeed();

  std::queue<std::pair<std::shared_ptr<Tile>, uint32_t>> queue;
  std::set<CoordPair> visited;

  std::shared_ptr<Tile> start_tile = battle->getBattlefield()->getTileByProxy( start );
  if ( !start_tile ) return valid_moves;

  queue.push( { start_tile, 0u } );
  visited.insert( start );
  valid_moves.push_back( std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() ) );
  while ( !queue.empty() ) {
    auto [current_tile, cost] = queue.front();
    queue.pop();

    const CoordPair current_coords = current_tile->getCoords();
    if ( cost > 0 ) {
      valid_moves.push_back(
          std::make_shared<MoveMove>( battle->getUnitInAction()->getCoordsInBattle(), current_coords ) );
    }

    if ( cost >= max_steps ) continue;

    for ( const auto& neighbor_tile : battle->battlefield_->getTileNeighbours( current_tile ) ) {
      if ( !neighbor_tile ) continue;

      CoordPair neighbour_coords = neighbor_tile->getCoords();
      // if (visited.count(neighbour_coords)) continue;
      if ( auto it = visited.find( neighbour_coords ); it != visited.end() ) continue;
      if ( neighbor_tile->getObject() ) continue;

      queue.push( { neighbor_tile, cost + 1 } );
      visited.insert( neighbour_coords );
    }
  }
  battle->possible_moves_ = valid_moves;
  return valid_moves;
}

std::vector<std::shared_ptr<Move>> MoveFactory::createAttackMove( std::shared_ptr<Battle> battle ) {
  std::vector<std::shared_ptr<Move>> valid_moves;
  if ( !battle->unit_in_action_ ) return valid_moves;

  CoordPair start = battle->unit_in_action_->getCoordsInBattle();
  uint32_t distance = battle->unit_in_action_->getRange();

  std::queue<std::pair<std::shared_ptr<Tile>, uint32_t>> queue;
  std::set<CoordPair> visited;

  std::shared_ptr<Tile> start_tile = battle->battlefield_->getTileByProxy( start );
  if ( !start_tile ) return valid_moves;

  queue.push( { start_tile, 0u } );
  visited.insert( start );
  std::vector<std::shared_ptr<UnitStack>> target_units = battle->getUnitsInBattle();
  std::shared_ptr<UnitStack> unit;
  valid_moves.push_back( std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() ) );
  while ( !queue.empty() ) {
    auto [current_tile, cost] = queue.front();
    queue.pop();

    const CoordPair current_coords = current_tile->getCoords();
    if ( cost > 0u && cost <= distance && current_tile->getObject() != nullptr ) {
      // some magic to get defending unit
      std::for_each( target_units.begin(), target_units.end(),
                     [&unit, &current_coords, &battle]( std::shared_ptr<UnitStack> unit_tmp ) {if(current_coords == unit_tmp->getCoordsInBattle() &&
                       !battle->isSameArmy(battle->getUnitInAction(),unit_tmp))unit=unit_tmp; } );
      if ( unit )
        valid_moves.push_back(
            std::make_shared<AttackMove>( battle->unit_in_action_->getCoordsInBattle(), unit->getCoordsInBattle() ) );
    }

    if ( cost >= distance ) continue;

    for ( const auto& neighbor_tile : battle->battlefield_->getTileNeighbours( current_tile ) ) {
      if ( !neighbor_tile ) continue;

      CoordPair neighbour_coords = neighbor_tile->getCoords();
      // if (visited.count(neighbour_coords)) continue;
      if ( auto it = visited.find( neighbour_coords ); it != visited.end() ) continue;
      // if (neighbor_tile->getObject()) continue;

      queue.push( { neighbor_tile, cost + 1 } );
      visited.insert( neighbour_coords );
    }
  }
  battle->possible_moves_ = valid_moves;
  return valid_moves;
}

std::vector<std::shared_ptr<Move>> MoveFactory::generateMoves( std::shared_ptr<Battle> battle ) {
  std::vector<std::shared_ptr<Move>> moves;
  switch ( battle->getBattleState() ) {
    case ProjectLib::BattleState::MOVING: {
      moves = createMoveMove( battle );
      break;
    }
    case ProjectLib::BattleState::ATTACKING: {
      moves = createAttackMove( battle );
      break;
    }
    case ProjectLib::BattleState::WIN_ATTACKER:
    case ProjectLib::BattleState::WIN_DEFENDER: {
      throw NotImplementedException( "MoveFactory::generateMoves -> End of battle not implemented" );
      break;
    }
    default: {
      throw UnknownStateException( "MoveFactory::generateMoves encountered an invalid Battle state" );
      break;
    }
  }
  moves.push_back( std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() ) );
  return moves;
}