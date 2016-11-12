#include "CharacterProxy.h"
#include "repo/CharacterRepository.h"
#include "../utils/LogUtils.h"

CharacterProxy::~CharacterProxy() {
    if (this->character != nullptr)
        delete this->character;
}

CharacterProxy::CharacterProxy() {
    this->character = nullptr;
    this->fileName = "";
}

CharacterProxy::CharacterProxy(Character* character) {
    this->character = character;
    this->fileName = character->getName();
}

CharacterProxy::CharacterProxy(string fileName) {
    this->character = nullptr;
    this->fileName = fileName;
}


Character* CharacterProxy::getCharacter() {
    if (nullptr == this->character) {
        this->character = new Character();
        this->character->loadCharacter(this->fileName);
        this->character->setName(fileName);
        #ifdef DEBUG
            logInfo("CharacterProxy", "getcharacter", "character not yet loaded, load into memory");
        #endif // DEBUG
    }
    return this->character;
}


