/// @file
/// @brief Header file containing template declaration and implementatino for Repository.class
///        and struct declaration for Coordinate.struct
/// @details  1. Game Rules: NONE \n\n
/// 2. Use as a generic Repository for the implementation for entity repositories \n
///    Initially wanted to work for polymorphism (virtual) and template but since they
///    don mix well together, found a workaround by using function pointers to change
///    certain behaviors based on the type of entity we are working with. \n
///    See: http://stackoverflow.com/questions/2354210/can-a-c-class-member-function-template-be-virtual \n
///    See: http://stackoverflow.com/questions/2354210/can-a-c-class-member-function-template-be-virtual \n
/// 3. Libraries: Uses Boost library for the implementation of the persisting of a map



#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <sstream>
#include <stdexcept>

#include "Repository.h"
#include "../entity/Map.h"
#include "../view/MapView.h"
#include "../view/CharacterView.h"
#include "../entity/Character.h"
#include "../utils/FileUtils.h"
#include"../utils/LogUtils.h"
#include "../entity_generator/MapGenerator.h"




/// Do not use directly, extend it and provide create persit and save functions for your specific entity
/// Those functions will be connected by function pointers instantiated in the constructor of the derived class
///  see MapRepository class for example
template <class T> class Repository {
    public:

        const static int REPO_CAPACITY = 100;
        ~Repository();

        std::vector<std::string>* listAll();
        bool save(std::string name, T* entity);
        bool exists(std::string name);
        T* getEntity(std::string name);
        T* getEntity(int index);
        bool remove(std::string name);
        T* find(std::string name);



        // Definition of entity specific methods for persistence
        // they will be used as values of the persistEntity and saveEntity function pointers
        // See function pointers for more information
        Map* loadMap(std::string name);
        bool persistMap(Map* entity, std::string name);
        Character* loadCharacter(std::string name);
        bool persistCharacter(Character* entity, std::string name);
        Item* loadItem(std::string name);
        bool persistItem(Item* entity, std::string name);

    protected:
        std::string referenceFile;
        Repository(std::string fileReference);

        // Function pointers that are defined in the constructor of the subtype
        // For instance the MapRepository will instantiate it with its persistMap and loadMap
        T* (Repository::*loadEntity)(std::string);
        bool (Repository::*persistEntity)(T* entity, std::string name);

    private:
        void updateRepoReference();
        int getIndex(std::string name);
        std::vector<std::string>* _references;
        T *_entities[REPO_CAPACITY];
        void construct();

};



// ////////////////////////////////////////////////////////////////////
// IMPLEMENTATION
// Implementaion kept in the same file due to templating particularies
// ////////////////////////////////////////////////////////////////////

template <class T>
Repository<T>::Repository(std::string fileReference): referenceFile(fileReference){
//    this->_entities = new T[20]();
    this->construct();
}


template <class T>
inline std::vector<std::string>* Repository<T>::listAll() {
    return this->_references;
}

template <class T>
Repository<T>::~Repository() {
    delete _references;
}


///  Load references of persisted entitiesin the memory from the reference file
/// reference files hold a list of all names of persisted entities for each type
template <class T>
void Repository<T>::construct() {

    stringstream sStream;

    #ifdef DEBUG
        logInfo("Repository",
                "Constructor",
                "FOR " + referenceFile + ": Initialization of Repository; loading persisted entity references...");
    #endif // DEBUG

    this->_references = new vector<string>;
    string entityName;

    T* entity;

    ifstream in(this->referenceFile);
    if (!in) {
        ofstream out;
        out.open(referenceFile, ios::trunc);
        out.close();
        in.open(referenceFile);

        #ifdef DEBUG
            logInfo("Repository",
                    "Constructor",
                    "FOR " + referenceFile + ":  references file does not exist, file created");
                if (!in)
                    logInfo("Repository",
                    "Constructor",
                    "FOR " + referenceFile + ": Could not create reference file.");
        #endif // DEBUG
    }
    int i = 0;
    while (in >> entityName) {
        #ifdef DEBUG
            logInfo("Repository",
                "Constructor",
                "Load " + entityName);
        #endif // DEBUG
        this->_references->push_back(entityName);
        this->_entities[i] = nullptr;
        i++;
    }
    in.close();
    #ifdef DEBUG
        sStream << "FOR " << referenceFile << ": Total of " << this->_references->size() << " references loaded.";
        logInfo("Repository",
                "Constructor",
                sStream.str());
    #endif // DEBUG
    if (0 == this->_references->size()) {

        #ifdef DEBUG
            logInfo("Repository",
                    "Constructor",
                    "FOR " + referenceFile + ": No existing entities");
        #endif // DEBUG
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
    ofstream out = loadOutputFileStream(this->referenceFile);

    for (size_t i = 0; i < this->_references->size(); i++) {
        out << this->_references->at(i) << endl;
    }
    out.close();
}



template <class T>
bool Repository<T>::save(string name, T* entity) {

    int currentSize = this->_references->size();
    #ifdef DEBUG
        logInfo("Repository", "save", "FOR " + referenceFile + ": Start saving entity " + name);
    #endif // DEBUG

    if (!this->exists(name)) {
        if (REPO_CAPACITY <= currentSize) {
            #ifdef DEBUG
                logInfo("Repository",
                        "save",
                        "FOR " + referenceFile + ": Cannot save new entity, reached max capacity of the repository");
            #endif // DEBUG
            return false;
        }
        #ifdef DEBUG
            logInfo("Repository", "save", "FOR " + referenceFile + ": " + name + "is new, updating reference file");
        #endif // DEBUG

        this->_references->push_back(name);
        this->_entities[currentSize] = entity;
        this->updateRepoReference();
    }
    return (this->*persistEntity)(entity, name);
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
    if (nullptr == entity || !entity) {
        #ifdef DEBUG
            logInfo("Repository", "getEntity", "FOR " + referenceFile + ":Entity not yet loaded, load into memory");
        #endif // DEBUG

        this->_entities[index] = entity = (this->*loadEntity)(fileName);

    }
    return entity;
}



// //////////////////////////////////////////
// LOAD AND PERSIST METHODS FOR THE ENTITIES
// //////////////////////////////////////////

 //////////// MAP //////////////

template <class T>
Map* Repository<T>::loadMap(string fileName) {
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
    Map* loadedMap = new Map(lMap);
    #ifdef DEBUG
        logInfo("Repository", "loadMap", "Attaching view to loaded map");
    #endif // DEBUG
    MapView* mapView = new MapView(loadedMap);
    return loadedMap;
}

template <class T>
bool Repository<T>::persistMap(Map* map, std::string name) {

    std::ofstream ofs(name);
    boost::archive::text_oarchive oa(ofs);
    oa << map;
    ofs.close();
    return true;
}



//////////// CHARACTER //////////////

template <class T>
Character* Repository<T>::loadCharacter(string fileName) {
    Character* character = new Character();
    character->loadCharacter(fileName);
    character->setName(fileName);
	CharacterView* charView = new CharacterView(character);
    return character;
}


template <class T>
bool Repository<T>::persistCharacter(Character* character, std::string name) {
    character->saveCharacter(name);
    return true;
}




//////////// ITEM//////////////

template <class T>
Item* Repository<T>::loadItem(string fileName) {

    string itemType, itemName, enhancementType;

    vector <Enhancement> Enhancements;
	std::ifstream f(fileName, std::ios::in);

	if (f.is_open())
	{
		int bonus;
		string getBonus;
		int i = 0;

		getline(f, itemType);

        getline(f, itemName);

//			while (enhancementType != "Armor" && enhancementType != "Ring"  && enhancementType != "Helmet" && enhancementType != "Boots" && enhancementType!="Belt" && enhancementType!="Weapon" && enhancementType!="Shield" && enhancementType !="")
        while (!f.eof())
        {
            getline(f, enhancementType);
            getline(f, getBonus);
            bonus = std::stoi(getBonus);
            Enhancements.push_back(Enhancement(enhancementType, bonus));
        }
        f.close();
        Item* item = new Item(itemType, Enhancements, itemName);

		return item;


	} else {

       throw std::invalid_argument( "Could not load item from given file name" );
	}
    return nullptr;
}

template <class T>
bool Repository<T>::persistItem(Item* item, std::string name) {

    ofstream saveFile(name, std::ios::trunc);
	vector<Enhancement> eVec;

    if (saveFile.is_open()) {

        saveFile << item->getType() << endl;
        saveFile << item->getName() << endl;
        eVec = item->getInfluences();

        for (size_t i = 0; i < eVec.size(); i++)
        {
            saveFile << eVec[i].getType() << endl;
            saveFile << eVec[i].getBonus() << endl;

        }
        saveFile.close();
	} else {
        throw std::invalid_argument( "Could not save item to file" );
        return false;
	}
    return true;
}
