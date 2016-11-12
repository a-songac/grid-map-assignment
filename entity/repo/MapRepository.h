#pragma once

#include "../MapProxy.h"
#include <vector>

using namespace std;

class MapRepository {
    public:
        static MapRepository* instance();
        ~MapRepository();

        vector<MapProxy*>* listAll();
        void save(Map* map);
        void save(string mapName);
        bool exists(string mapName);
        Map* getMap(string mapName);
        bool remove(string name);
        MapProxy* find(string name);
        Map* loadMap(string name);


    private:
        vector<MapProxy*>* _proxies;
        static MapRepository* _instance;
        MapRepository();
        void updateRepoReference();
        void loadGeneratedMaps();

};
