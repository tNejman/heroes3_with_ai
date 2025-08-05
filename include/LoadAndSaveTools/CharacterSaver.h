#pragma once

#include "Characters/Character.h"
#include "LoadAndSaveTools/ISaver.h"

class CharacterSaver : public ISaver {
 private:
  const std::shared_ptr<const Character> c_;

  void saveStats( std::ofstream& out ) const;
  void saveSecondarySkills( std::ofstream& out ) const;
  void saveEquipment( std::ofstream& out ) const;
  void saveWarMachines( std::ofstream& out ) const;
  void saveSpellBook( std::ofstream& out ) const;
  void saveBackpack( std::ostream& out ) const;
  void saveParty( std::ofstream& out ) const;

  void doSave( std::ofstream& out ) const override;

  std::vector<int> convertStringToInVec( const std::string& str ) const;

 public:
  CharacterSaver( std::string&& path, std::shared_ptr<const Character> character );
};