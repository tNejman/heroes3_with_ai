#include "LoadAndSaveTools/MapSaver.h"

#include <fstream>

void MapSaver::doSave( std::ofstream& out ) const {
  out << "hello" << std::endl;  // placeholder, zeby kompilator sie nie czepial
  throw NotImplementedException( "MapSaver::doSave" );
}

MapSaver::MapSaver( const std::string& path, const std::shared_ptr<const WorldMap> map )
    : ISaver( path ), map_( map ) {
  assert( map != nullptr && "MapSaver: map is null" );
};