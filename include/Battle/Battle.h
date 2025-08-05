#pragma once

/**
 * @file Battle.h
 * @brief Defines the Battle class responsible for managing battles between two armies.
 *
 * @author Tomasz Naszkowski
 */

/**
 * @class Battle
 * @brief Manages the battle logic, including unit actions, round management, and battle state.
 *
 * The Battle class is responsible for managing the state and flow of a battle between two armies,
 * handling unit actions such as movement and attacks, managing the round queue, and providing access
 * to the battlefield, armies, and units. It also supports AI and minimax logic for automated moves.
 *
 * @author Tomasz Naszkowski
 */

#include <stdint.h>

#include <array>
#include <cassert>
#include <memory>
#include <queue>
#include <set>
#include <vector>

#include "Battle/BattleField.h"
#include "Battle/BattleObstacle.h"
#include "Battle/Tile.h"
#include "Battle/TileObject.h"
#include "Characters/Character.h"
#include "Graphic/Printable.h"
#include "WorldMap/GridTile.h"

class MoveFactory;
class Move;

/**
 * @class Battle
 * @brief Represents a battle between two characters and their armies.
 *
 * This class manages the battle state, battlefield, and unit actions.
 * It handles the logic for moving units, attacking, and managing rounds.
 */
class Battle : public Printable, std::enable_shared_from_this<Battle> {
 private:
  /**
   * @enum BattleState
   * @brief Represents the current state of the battle.
   */
  ProjectLib::BattleState state_ = ProjectLib::BattleState::PREPPING;

  /**
   * @brief The battlefield where the battle takes place.
   */
  std::shared_ptr<BattleField> battlefield_;

  /**
   * @brief The obstacles present on the battlefield.
   */
  std::shared_ptr<Character> attacker_;

  /**
   * @brief The defending character in the battle.
   */
  std::shared_ptr<Character> defender_;

  size_t round_counter_ = 0;
  bool attacker_threw_spell_;
  bool defender_threw_spell_;
  std::vector<std::shared_ptr<UnitStack>> round_queue_;
  void setAttackingArmy();
  void setDefendingArmy();
  uint32_t setUnitInQueue( std::shared_ptr<UnitStack> unit );
  void createObstacles();
  void nextRound();
  std::shared_ptr<UnitStack> unit_in_action_;
  std::vector<std::shared_ptr<Move>> possible_moves_;

  bool is_minimax_ = false;

 public:
  friend MoveFactory;
  /**
   * @brief Constructs a Battle object with the given attacker, defender, and battlefield background.
   * @param attacker Shared pointer to the attacking Character.
   * @param defender Shared pointer to the defending Character.
   * @param background Shared pointer to the GridTile representing the battlefield background.
   */
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, std::shared_ptr<GridTile> background );

  /**
   * @brief Constructs a Battle object with the given attacker, defender, battlefield background, and minimax flag.
   * @param attacker Shared pointer to the attacking Character.
   * @param defender Shared pointer to the defending Character.
   * @param background Shared pointer to the GridTile representing the battlefield background.
   * @param is_minimax Boolean flag indicating if the battle is for minimax/AI simulation.
   */
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, std::shared_ptr<GridTile> background, bool is_minimax );

  /**
   * @brief Destructor for the Battle class.
   */
  ~Battle() noexcept override = default;

  /**
   * @brief Accepts a Visitor for rendering or processing.
   * @param v Reference to the Visitor.
   * @return Reference to an sf::Texture.
   */
  [[nodiscard]] sf::Texture& accept( Visitor& v ) const override;

  /**
   * @brief Gets the current state of the battle.
   * @return The current BattleState.
   */
  [[nodiscard]] ProjectLib::BattleState getState() const;

  /**
   * @brief Sets the position of a unit stack on the battlefield.
   * @param unit_stack Shared pointer to the UnitStack to be placed.
   * @param new_coords Coordinates where the unit stack should be placed.
   * @return True if the unit was successfully placed, false otherwise.
   */
  bool setUnit( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );

  /**
   * @brief Removes (kills) a unit from the battlefield.
   * @param dead_unit_to_kill Shared pointer to the UnitStack to be removed.
   * @return True if the unit was successfully removed, false otherwise.
   */
  bool killUnit( std::shared_ptr<UnitStack> dead_unit_to_kill );

  /**
   * @brief Sets the current state of the battle.
   * @param state The new BattleState.
   */
  void setBattleState( ProjectLib::BattleState state );

  /**
   * @brief Moves a unit stack to new coordinates on the battlefield.
   * @param unit_stack Shared pointer to the UnitStack to move.
   * @param new_coords The target coordinates.
   * @return True if the move was successful, false otherwise.
   */
  bool move( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );

  /**
   * @brief Executes an attack from one unit stack to another.
   * @param attacker Shared pointer to the attacking UnitStack.
   * @param defender Shared pointer to the defending UnitStack.
   * @return True if the attack was successful, false otherwise.
   */
  bool attack( std::shared_ptr<UnitStack> attacker, std::shared_ptr<UnitStack> defender );

  /**
   * @brief Gets the battlefield associated with this battle.
   * @return Shared pointer to the BattleField.
   */
  std::shared_ptr<BattleField> getBattlefield();

  /**
   * @brief Gets the attacking character.
   * @return Shared pointer to the attacker Character.
   */
  std::shared_ptr<Character> getAttacker() const;

  /**
   * @brief Gets the defending character.
   * @return Shared pointer to the defender Character.
   */
  std::shared_ptr<Character> getDefender() const;

  /**
   * @brief Gets the current round counter.
   * @return The current round number.
   */
  size_t getRoundCounter() const;

  /**
   * @brief Gets the unit stack located at the specified coordinates.
   * @param coords The coordinates to check.
   * @return Shared pointer to the UnitStack at the given coordinates, or nullptr if none exists.
   */
  std::shared_ptr<UnitStack> getUnitFromCoords( CoordPair coords ) const;

  /**
   * @brief Checks if the attacker has already cast a spell in this battle.
   * @return True if the attacker has cast a spell, false otherwise.
   */
  bool hasAttackerThrownSpell() const;

  /**
   * @brief Checks if the defender has already cast a spell in this battle.
   * @return True if the defender has cast a spell, false otherwise.
   */
  bool hasDefenderThrownSpell() const;

  /**
   * @brief Advances to the next unit's turn in the round queue.
   */
  void nextUnit();

  /**
   * @brief Gets the attacking army's unit stacks.
   * @return Vector of shared pointers to the attacking army's UnitStacks.
   */
  std::vector<std::shared_ptr<UnitStack>> getAttackingArmy() const;

  /**
   * @brief Gets the defending army's unit stacks.
   * @return Vector of shared pointers to the defending army's UnitStacks.
   */
  std::vector<std::shared_ptr<UnitStack>> getDefendingArmy() const;

  /**
   * @brief Gets all unit stacks currently in the battle.
   * @return Vector of shared pointers to all UnitStacks in the battle.
   */
  std::vector<std::shared_ptr<UnitStack>> getUnitsInBattle() const;

  /**
   * @brief Gets all unit stacks in the battle, sorted for printing.
   * @return Vector of shared pointers to UnitStacks, sorted for display.
   */
  std::vector<std::shared_ptr<UnitStack>> getUnitsInBattleSortedToPrint() const;

  /**
   * @brief Gets the current round queue of unit stacks.
   * @return Vector of shared pointers to UnitStacks in the round queue.
   */
  std::vector<std::shared_ptr<UnitStack>> getRoundQueue() const;

  /**
   * @brief Gets the unit stack currently taking action.
   * @return Shared pointer to the UnitStack in action.
   */
  std::shared_ptr<UnitStack> getUnitInAction() const;

  /**
   * @brief Gets the possible moves for the current unit in action.
   * @return Vector of shared pointers to possible Move objects.
   */
  std::vector<std::shared_ptr<Move>> getPossibleMoves() const;

  /**
   * @brief Gets the current battle state.
   * @return The current BattleState.
   */
  ProjectLib::BattleState getBattleState() const;

  /**
   * @brief Checks if two unit stacks belong to the same army.
   * @param unit1 Shared pointer to the first UnitStack.
   * @param unit2 Shared pointer to the second UnitStack.
   * @return True if both units are from the same army, false otherwise.
   */
  bool isSameArmy( const std::shared_ptr<UnitStack> unit1, const std::shared_ptr<UnitStack> unit2 ) const;

  /**
   * @brief Checks if the current move is an AI move (minimax).
   * @return True if the move is for AI/minimax, false otherwise.
   */
  bool isAIMove() const;

  /**
   * @brief Forces all unit stacks to be unplaced from the battlefield.
   */
  void forceUnplaceUnitStacks();

  /**
   * @brief Forces a unit stack to be placed at the specified coordinates.
   * @param unit_stack Shared pointer to the UnitStack to place.
   * @param new_coords The coordinates where the unit stack should be placed.
   */
  void forcePlaceUnitStack( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );

  /** * @brief Creates a deep copy of the current Battle object.
   * @return Shared pointer to the copied Battle.
   */
  std::shared_ptr<Battle> copy();
};