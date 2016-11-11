#include "Repository.h"
#include "../utils/FileUtils.h"
#include"../utils/LogUtils.h"
#include "../entity_generator/MapGenerator.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <sstream>

using namespace std;

template <class T>
const int Repository<T>::REPO_CAPACITY = 20;

//Repository<T*>* Repository::Repository;
template <class T>
Repository<T>* Repository<T>::instance() {
    if (!_instance) {
        _instance = new Repository;
    }
    return _instance;
}


template <class T>
Repository<T>::~Repository() {
    delete _references;
}


///  Load proxies of persisted map in the memory from _map_references
/// _map_references holds a list of all names of persisted map
template <class T>
Repository<T>::Repository() {

    stringstream sStream;

    #ifdef DEBUG
        logInfo("Repository",
                "Constructor",
                "FOR " + getReferenceFileName() + ": Initialization of Repository; loading persisted map references...");
    #endif // DEBUG

    this->_proxies = new vector<string>;
    string entityName;
    T* entity;

    ifstream in(this->getReferenceFileName());
    if (!in) {
        ofstream out;
        out.open(getReferenceFileName(), ios::trunc);
        out.close();
        in.open(getReferenceFileName());

        #ifdef DEBUG
            logInfo("Repository",
                    "Constructor",
                    "FOR " + getReferenceFileName() + ":  references file does not exist, file created");
                if (!in)
                    logInfo("Repository",
                    "Constructor",
                    "FOR " + getReferenceFileName() + ": Could not create reference file.");
        #endif // DEBUG


        _entities = new T[REPO_CAPACITY];

    }
    size_t i = 0;
    while (in >> entityName) {
        #ifdef DEBUG
            logInfo("Repository",
                "Constructor",
                "Load " + entityName);
        #endif // DEBUG
        this->_references->push_back(entityName);
        this->_entities[i++] = nullptr;
    }
    in.close();
    #ifdef DEBUG
        sStream << "FOR " << getReferenceFileName() << ": Total of " << this->_proxies->size() << " references loaded.";
        logInfo("Repository",
                "Constructor",
                sStream.str());
    #endif // DEBUG

    if (0 == this->_proxies->size()) {

        #ifdef DEBUG
            logInfo("Repository",
                    "Constructor",
                    "FOR " + getReferenceFileName() + ": No existing entities, attempt to load the pregenerated entities if any...");
        #endif // DEBUG
        this->loadGeneratedEntities();

    }
}

template <class T>
int Repository<T>::getIndex(string name) {
    for (size_t i = 0; i < this->_references->size(); i++) {
        if (name == _references->at(i)) {
            return i;
        }
    }
    return -1;
}

template <class T>
bool Repository<T>::exists(string name) {

    return this->getIndex(name) >= 0;
}

template <class T>
void Repository<T>::updateRepoReference() {
    ofstream out = loadOutputFileStream(this->getReferenceFileName());

    for (size_t i = 0; i < this->_references->size(); i++) {
        out << this->_references->at(i) << endl;
    }
    out.close();
}


template <class T>
bool Repository<T>::save(string name, T* entity) {

    int currentSize = this->_references->size();

    if (!this-exists(name)) {
        if (REPO_CAPACITY <= currentSize) {
            #ifdef DEBUG
                logInfo("Repository",
                        "save",
                        "FOR " + getReferenceFileName() + ": Cannot save new entity, reached max capacity of the repository");
            #endif // DEBUG
            return false;
        }

        this->_references->push_back(name);
        this->_entities[currentSize] = entity;
        this->updateRepoReference();
    }
    return this->persist(entity);
}

template <class T>
T* Repository<T>::getEntity(std::string name) {
    for (size_t i = 0; i < this->_references->size(); i++) {
        if (name == this->_references->at(i)) {
            return this->getEntity(i);
        }
    }
    return nullptr;
}

template <class T>
T* Repository<T>::getEntity(int index) {

    T* entity;
    string fileName = this->_references->at(index);

    if (index < 0 || index > this->_references->size()) {
        return nullptr;
    }

    entity = this->_entities[index];
    if (nullptr == entity) {
        #ifdef DEBUG
            logInfo("Repository", "getEntity", "FOR " + getReferenceFileName() + ":Entity not yet loaded, load into memory");
        #endif // DEBUG

        this->_entities[index] = entity = this->loadEntity(fileName);

    }
    return entity;
}

