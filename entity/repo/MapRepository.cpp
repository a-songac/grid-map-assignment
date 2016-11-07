#include "MapRepository.h"
#include "../../utils/FileUtils.h"

#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

const string PERSISTENCE_MAPS_LOCATION = "persistence/map/";
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

#ifdef DEBUG
    cout << "Initialization of MapRepository; loading persisted map references..." << endl;
#endif // DEBUG

    this->_proxies = new list<MapProxy*>;
    string mapName;
    MapProxy* proxy;

    ifstream in(PERSISTENCE_MAPS_LOCATION + PERSISTENCE_MAPS_REFERENCES);
    if (!in) {
        ofstream out;
        out.open(PERSISTENCE_MAPS_LOCATION + PERSISTENCE_MAPS_REFERENCES, ios::trunc);
        out.close();
        in.open(PERSISTENCE_MAPS_LOCATION + PERSISTENCE_MAPS_REFERENCES);
#ifdef DEBUG
        cout << "map references file does not exist, file created" << endl;
#endif // DEBUG
    }

    while (in >> mapName) {
#ifdef DEBUG
        cout << "Load " << mapName <<  endl;
#endif // DEBUG
        proxy = new MapProxy(mapName);
        this->_proxies->push_back(proxy);
    }
    in.close();
#ifdef DEBUG
    cout << "Total of " << this->_proxies->size() << " map references loaded." <<  endl;
#endif // DEBUG
}

/// Return the list of proxies
list<MapProxy*>* MapRepository::listAll() {
    return this->_proxies;
}

/// Save changes in the _map_references file
/// Essential when deleting or adding
void MapRepository::updateRepoReference() {
    ofstream out = loadOutputFileStream(PERSISTENCE_MAPS_LOCATION + PERSISTENCE_MAPS_REFERENCES);

    list<MapProxy*>::iterator i = this->_proxies->begin();
    for (; i!= this->_proxies->end(); i++) {
        out << (*i)->getFileName() << endl;
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


    ofstream in = loadOutputFileStream(PERSISTENCE_MAPS_LOCATION + mapName);
    // TODO Persist map in the file
    in.close();
}

/// Work with proxy since finding a map does not mean we will need it.  To be discussed
MapProxy* MapRepository::find(string name) {

    list<MapProxy*>::iterator i = this->_proxies->begin();
    for (; i != this->_proxies->end(); i++) {
        if (name == (*i)->getFileName()) {
            return (*i);
        }
    }
    return nullptr;
}

Map* MapRepository::loadMap(string name) {
    Map* loadedMap;
    // TODO load map from textfile
    return loadedMap;
}


bool MapRepository::remove(string name) {

    MapProxy* proxy = this->find(name);
    if (nullptr != proxy) {

        this->_proxies->remove(proxy);
        delete proxy;
        this->updateRepoReference();
        string fileName = PERSISTENCE_MAPS_LOCATION + name;
        if( std::remove(fileName.c_str()) != 0 ) {
            cout << "MapRepository::remove::error deleting file: " << PERSISTENCE_MAPS_LOCATION << name << endl;
            return false;
        }

    }
    return false;
}


