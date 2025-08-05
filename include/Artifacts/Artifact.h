#pragma once
/**
 * @file Artifact.h
 * @author Tomasz Nejman
 * @brief Class Artifact implements Artifact (stat buffing item) equippable by Characters
 *
 * Detailed desccreption
 * Instances are created exclusively through the static factory
 * Artifact::create(ArtifactType). Direct construction is disabled.
 */

#include <stdint.h>

#include <array>
#include <memory>
#include <string>

#include "Exceptions/InvalidArtifactTypeException.hpp"
#include "Graphic/Printable.h"
#include "Miscellaneous/ArtifactLib.h"
#include "WorldMap/MapObject.h"

// public Printable
/**
 * @class Artifact
 * @brief Immutable representation of an equippable artifact.
 *
 * An Artifact provides passive attribute bonuses while occupying a single
 * equipment slot. Instances are created via the staic factory
 * Artifact::create(ArtifactType) that validates the requested ::ArtifactTyp against
 * the central ArtifactLib database.
 *
 * @note ALL getters are noexcept and thread-safe because the underlying
 *       data is immutable after construction.
 *
 * Artifact inherits from:
 *  MapObject - meaning it can be placed on a WorldMapclass
 */
class Artifact : public MapObject {
 private:
  //* Shared metedata describing the artifact (type, name, stats, cost, slot, etc.). */
  const std::shared_ptr<const ArtifactLib::ArtifactData> artifact_data_;

 public:
  /**
   * @brief Artifact is always of a specific type, therefore a default construtor
   * would leave Artifact in an incomplete state.
   */
  Artifact() = delete;

  /**
   * @brief Construct a new Artifact object
   * @warning Must not be called explicitly. GOTO Artifact::create
   * @param data Identifier of the artifact to instantiate.
   */
  Artifact( const std::shared_ptr<const ArtifactLib::ArtifactData> data );

  // ------------------------------------------------------------------
  // Factory
  // ------------------------------------------------------------------
  /**
   * @brief Factory method creating a fully initalised Artifact.
   *
   * @param type Identifier of the artifact to instantiate.
   * @return std::unique_ptr<Artifact> Owning pointer to the new object.'
   * @throws InvalidArtifactTypeException
   */
  static std::unique_ptr<Artifact> create( const ArtifactLib::ArtifactType type );

  // ------------------------------------------------------------------
  // Visitor
  // ------------------------------------------------------------------
  /**
   * @brief Accepts a rendering visitor (double dispatch).
   *
   * @param v Concrete visitor, e.g. SpriteVisitor
   * @return sf::Texture& Texture owned by the visitor representing
   *         this artifact.
   */
  sf::Texture& accept( Visitor& v ) const override;

  // ------------------------------------------------------------------
  // Accessors
  // ------------------------------------------------------------------
  [[nodiscard]] ArtifactLib::ArtifactType getType() const;
  [[nodiscard]] ProjectLib::EquipmentSlots getSlot() const;
  [[nodiscard]] int getAttack() const;
  [[nodiscard]] int getDefense() const;
  [[nodiscard]] int getPower() const;
  [[nodiscard]] int getKnowledge() const;
  [[nodiscard]] int getSpeed() const;
  [[nodiscard]] size_t getCost() const;

  /**
   * @brief Produces a deep copy of the artifact.
   * @return std::unique_ptr<Artifact> Independent duplicate.
   */
  std::unique_ptr<Artifact> copy() const;
};