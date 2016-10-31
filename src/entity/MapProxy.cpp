#include "MapProxy.h"

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
    this->fileName = "";
}

MapProxy::MapProxy(string fileName) {
    this->map = nullptr;
    this->fileName = fileName;
}


Map* MapProxy::getMap() {
    if (nullptr == this->map) {
        // TODO load map from persistence and set the map pointer
    }

    return this->map;
}


