#pragma once

#include "Map.h"

class MapProxy {
    public:
        ~MapProxy();
        MapProxy();
        MapProxy(Map* map);
        MapProxy(string fileName);

        string getFileName();
        void setFileName(string fileName);
        Map* getMap();
        void setMap(Map* map);

    private:
        Map* map;
        string fileName;

};



inline void MapProxy::setFileName(string fileName) {
    this->fileName = fileName;
}

inline void MapProxy::setMap(Map* map) {
    this->map = map;
}

inline string MapProxy::getFileName() {
    return this->fileName;
}
