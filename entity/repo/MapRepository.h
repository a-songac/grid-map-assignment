#pragma once

#include "../MapProxy.h"
#include <list>

using namespace std;

class MapRepository {
    public:
        static MapRepository* instance();
        ~MapRepository();

        list<MapProxy*>* listAll();
        void save(Map* map);
        void save(string mapName);
        bool exists(string mapName);
        Map* getMap(string mapName);
        bool remove(string name);
        MapProxy* find(string name);
        Map* loadMap(string name);


    private:
        list<MapProxy*>* _proxies;
        static MapRepository* _instance;
        MapRepository();
        void updateRepoReference();

};
