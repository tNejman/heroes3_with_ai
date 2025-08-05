#pragma once

#include "LoadAndSaveTools/ISaver.h"
#include "WorldMap/WorldMap.h"

class MapSaver : public ISaver {
 private:
  const std::shared_ptr<const WorldMap> map_;
  void doSave( std::ofstream& out ) const override;

 public:
  MapSaver( const std::string& path, const std::shared_ptr<const WorldMap> map );
};