#include "MapProxy.h"
#include "repo/MapRepository.h"
#include "../utils/LogUtils.h"

MapProxy::~MapProxy() {
    if (this->map != nullptr)
        delete this->map;
}

MapProxy::MapProxy() {
    this->map = nullptr;
    this->fileName = "";
}

MapProxy::MapProxy(Map* map) {
    this->map = map;
    this->fileName = map->getName();
}

MapProxy::MapProxy(string fileName) {
    this->map = nullptr;
    this->fileName = fileName;
}


Map* MapProxy::getMap() {
    if (nullptr == this->map) {
        this->map = MapRepository::instance()->loadMap(this->fileName);
        #ifdef DEBUG
            logInfo("MapProxy", "getMap", "Map not yet loaded, load into memory");
        #endif // DEBUG
    }
    return this->map;
}


