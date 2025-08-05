#include "Artifacts/Artifact.h"

Artifact::Artifact( const std::shared_ptr<const ArtifactLib::ArtifactData> data )
    : artifact_data_( data ) {}

std::unique_ptr<Artifact> Artifact::create( const ArtifactLib::ArtifactType type ) {
  return std::make_unique<Artifact>( ArtifactLib::ARTIFACTS_PRESET.at( type ) );
}

sf::Texture& Artifact::accept( Visitor& v ) const {
  return v.visit( *this );
}

ArtifactLib::ArtifactType Artifact::getType() const {
  return this->artifact_data_->type_;
}

ProjectLib::EquipmentSlots Artifact::getSlot() const {
  return this->artifact_data_->slot_;
}

int Artifact::getAttack() const {
  return this->artifact_data_->attack_;
}

int Artifact::getDefense() const {
  return this->artifact_data_->defense_;
}

int Artifact::getPower() const {
  return this->artifact_data_->power_;
}

int Artifact::getKnowledge() const {
  return this->artifact_data_->knowledge_;
}

int Artifact::getSpeed() const {
  return this->artifact_data_->speed_;
}

size_t Artifact::getCost() const {
  return this->artifact_data_->cost_;
}

std::unique_ptr<Artifact> Artifact::copy() const {
  return std::make_unique<Artifact>( this->artifact_data_ );
}