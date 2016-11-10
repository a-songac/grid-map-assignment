#include "CharacterRepository.h"
#include "../../utils/FileUtils.h"
#include"../../utils/LogUtils.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <sstream>

using namespace std;

const string PERSISTENCE_CHARACTER_REFERENCES = "_character_references";

CharacterRepository* CharacterRepository::_instance;

CharacterRepository* CharacterRepository::instance() {
    if (!_instance) {
        _instance = new CharacterRepository;
    }
    return _instance;
}

CharacterRepository::~CharacterRepository() {
    delete _proxies;
}

///  Load proxies of persisted characaters in the memory from _character_references
/// _character_references holds a list of all names of persisted character
CharacterRepository::CharacterRepository() {

    stringstream sStream;

    #ifdef DEBUG
        logInfo("CharacterRepository",
                "Constructor",
                "Initialization of CharacterRepository; loading persisted character references...");
    #endif // DEBUG

    this->_proxies = new vector<CharacterProxy*>;
    string characterName;
    CharacterProxy* proxy;

    ifstream in(PERSISTENCE_CHARACTER_REFERENCES);
    if (!in) {
        ofstream out;
        out.open(PERSISTENCE_CHARACTER_REFERENCES, ios::trunc);
        out.close();
        in.open(PERSISTENCE_CHARACTER_REFERENCES);

        #ifdef DEBUG
            logInfo("CharacterRepository",
                    "Constructor",
                    "character references file does not exist, file created");
                if (!in)
                    logInfo("CharacterRepository",
                    "Constructor",
                    "Could not create reference file.");
        #endif // DEBUG
    }

    while (in >> characterName) {
        #ifdef DEBUG
            logInfo("CharacterRepository",
                "Constructor",
                "Load " + characterName);
        #endif // DEBUG
        proxy = new CharacterProxy(characterName);
        this->_proxies->push_back(proxy);
    }
    in.close();
    #ifdef DEBUG
        sStream << "Total of " << this->_proxies->size() << " character references loaded.";
        logInfo("CharacterRepository",
                "Constructor",
                sStream.str());
    #endif // DEBUG
}



/// Return the list of proxies
vector<CharacterProxy*>* CharacterRepository::listAll() {
    return this->_proxies;
}

/// Save changes in the _character_references file
/// Essential when deleting or adding
void CharacterRepository::updateRepoReference() {
    ofstream out = loadOutputFileStream(PERSISTENCE_CHARACTER_REFERENCES);

    for (int i = 0; i < this->_proxies->size(); i++) {
        out << _proxies->at(i)->getFileName() << endl;
    }
    out.close();
}

/// persist character
/// create new character file and update _character_references if creating a new character
bool CharacterRepository::save(Character* character) {

    string characterName = character->getName();
    CharacterProxy* proxy = this->find(characterName);
    if (nullptr == proxy) {

        CharacterProxy* proxy = new CharacterProxy(characterName);
        this->_proxies->push_back(proxy);
        this->updateRepoReference();
    }

    return character->saveCharacter(characterName);
}

/// Work with proxy since finding a character does not mean we will need it.  To be discussed
CharacterProxy* CharacterRepository::find(string name) {

    for (int i = 0; i < this->_proxies->size(); i++) {
        if (name == _proxies->at(i)->getFileName()) {
            return _proxies->at(i);
        }
    }
    return nullptr;
}

// USE LOAD IN THE CHARACTER CLASS INSTEAD
//Character* CharacterRepository::loadCharacter(string fileName) {
//
//    boost::filesystem::path myfile(fileName);
//
//    if( !boost::filesystem::exists(myfile))
//    {
//        return nullptr;
//    }
//    Character* loadedCharacter = new Character();
//
//    loadedCharacter->loadCharacter(fileName);
//    loadedCharacter->setName(fileName);
//
//    return loadedCharacter;
//}


bool CharacterRepository::remove(string name) {

    int index = -1;
    for (int i = 0; i < this->_proxies->size(); i++) {
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
            cout << "CharacterRepository::remove::error deleting file: " << name << endl;
            return false;
        }

    }
    return false;
}


