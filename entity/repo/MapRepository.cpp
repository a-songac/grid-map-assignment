#include "MapRepository.h"
#include "../../utils/FileUtils.h"
#include"../../utils/LogUtils.h"
#include "../../entity_generator/MapGenerator.h"


using namespace std;

MapRepository* MapRepository::_instance;

MapRepository::MapRepository(): Repository<Map>("_map_references"){
    loadEntity = &Repository<Map>::loadMap;
    persistEntity = &Repository<Map>::persistMap;
}

MapRepository* MapRepository::instance() {
    if (!_instance) {
        _instance = new MapRepository();
//        if (_instance->listAll()->size() == 0) {
//            #ifdef DEBUG
//                logWarning("MapRepository", "instance", "No maps loaded, start the creation and saving of pregenerated ones...");
//            #endif // DEBUG
//            Map* map1 = MapGenerator::map1();
//            _instance->save(map1->getName(), map1);
//            #ifdef DEBUG
//                logWarning("MapRepository", "instance", "Pregenerated maps successfully loaded and saved");
//            #endif // DEBUG
//        }
    }
    return _instance;
}



