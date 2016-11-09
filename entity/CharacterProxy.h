#pragma once

#include "Character.h"

class CharacterProxy {
    public:
        ~CharacterProxy();
        CharacterProxy();
        CharacterProxy(Character* character);
        CharacterProxy(string fileName);

        string getFileName();
        void setFileName(string fileName);
        Character* getCharacter();
        void setCharacter(Character* character);

    private:
        Character* character;
        string fileName;

};



inline void CharacterProxy::setFileName(string fileName) {
    this->fileName = fileName;
}

inline void CharacterProxy::setCharacter(Character* character) {
    this->character = character;
}

inline string CharacterProxy::getFileName() {
    return this->fileName;
}
