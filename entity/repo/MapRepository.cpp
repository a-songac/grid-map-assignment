#include "MapRepository.h"
#include "../../utils/FileUtils.h"
#include"../../utils/LogUtils.h"
#include "../../entity_generator/MapGenerator.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <sstream>

using namespace std;

const string PERSISTENCE_MAPS_REFERENCES = "_map_references";
const string PERSISTENCE_CHARACTER_LOCATION = "persistence/character/";
const string PERSISTENCE_CHARACTER_REFERENCES = "_character_references";

MapRepository* MapRepository::_instance;

MapRepository* MapRepository::instance() {
    if (!_instance) {
        _instance = new MapRepository;
    }
    return _instance;
}

MapRepository::~MapRepository() {
    // TODO Delete map proxies held in the list, how is that done?
    delete _proxies;
}

///  Load proxies of persisted map in the memory from _map_references
/// _map_references holds a list of all names of persisted map
MapRepository::MapRepository() {

    stringstream sStream;

    #ifdef DEBUG
        logInfo("MapRepository",
                "Constructor",
                "Initialization of MapRepository; loading persisted map references...");
    #endif // DEBUG

    this->_proxies = new vector<MapProxy*>;
    string mapName;
    MapProxy* proxy;

    ifstream in(PERSISTENCE_MAPS_REFERENCES);
    if (!in) {
        ofstream out;
        out.open(PERSISTENCE_MAPS_REFERENCES, ios::trunc);
        out.close();
        in.open(PERSISTENCE_MAPS_REFERENCES);

        #ifdef DEBUG
            logInfo("MapRepository",
                    "Constructor",
                    "map references file does not exist, file created");
                if (!in)
                    logInfo("MapRepository",
                    "Constructor",
                    "Could not create reference file.");
        #endif // DEBUG
    }

    while (in >> mapName) {
        #ifdef DEBUG
            logInfo("MapRepository",
                "Constructor",
                "Load " + mapName);
        #endif // DEBUG
        proxy = new MapProxy(mapName);
        this->_proxies->push_back(proxy);
    }
    in.close();
    #ifdef DEBUG
        sStream << "Total of " << this->_proxies->size() << " map references loaded.";
        logInfo("MapRepository",
                "Constructor",
                sStream.str());
    #endif // DEBUG

    if (0 == this->_proxies->size()) {
        loadGeneratedMaps();

        #ifdef DEBUG
            logInfo("MapRepository",
                    "Constructor",
                    "No existing maps, load and save the pregenerated maps");
        #endif // DEBUG
    }
}


void MapRepository::loadGeneratedMaps() {

    this->save(MapGenerator::map1());

}



/// Return the list of proxies
vector<MapProxy*>* MapRepository::listAll() {
    return this->_proxies;
}

/// Save changes in the _map_references file
/// Essential when deleting or adding
void MapRepository::updateRepoReference() {
    ofstream out = loadOutputFileStream(PERSISTENCE_MAPS_REFERENCES);

    for (size_t i = 0; i < this->_proxies->size(); i++) {
        out << _proxies->at(i)->getFileName() << endl;
    }
    out.close();
}

/// persist map
/// create new map file and update _map_references if creating a new map
void MapRepository::save(Map* map) {

    string mapName = map->getName();
    MapProxy* proxy = this->find(mapName);
    if (nullptr == proxy) {

        MapProxy* proxy = new MapProxy(mapName);
        this->_proxies->push_back(proxy);
        this->updateRepoReference();
    }

    std::ofstream ofs(mapName);
    boost::archive::text_oarchive oa(ofs);
    oa << map;
    ofs.close();
}

/// Work with proxy since finding a map does not mean we will need it.  To be discussed
MapProxy* MapRepository::find(string name) {

    for (size_t i = 0; i < this->_proxies->size(); i++) {
        if (name == _proxies->at(i)->getFileName()) {
            return _proxies->at(i);
        }
    }
    return nullptr;
}


Map* MapRepository::loadMap(string fileName) {

    boost::filesystem::path myfile(fileName);

    if( !boost::filesystem::exists(myfile))
    {
        return nullptr;
    }

    Map* lMap;
    std::ifstream ifs(fileName, std::ios::binary);
    boost::archive::text_iarchive ia(ifs);
    ia >> lMap;
    ifs.close();
    Map* loadedMap = new Map(lMap); // TODO need copy constructor
    return loadedMap;
}


bool MapRepository::remove(string name) {

    int index = -1;
    for (size_t i = 0; i < this->_proxies->size(); i++) {
        if (name == _proxies->at(i)->getFileName()) {
            index = i;
            break;
        }
    }


    if (-1 != index) {

        this->_proxies->erase(_proxies->begin()+index);
        this->updateRepoReference();
        string fileName = name;
        if( std::remove(fileName.c_str()) != 0 ) {
            cout << "MapRepository::remove::error deleting file: " << name << endl;
            return false;
        }

    }
    return false;
}


