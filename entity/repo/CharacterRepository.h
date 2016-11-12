#pragma once

#include "../CharacterProxy.h"
#include <vector>


class CharacterRepository {
    public:
        static CharacterRepository* instance();
        ~CharacterRepository();

        vector<CharacterProxy*>* listAll();
        bool save(Character* character);
        void save(std::string characterName);
        bool exists(std::string characterName);
        Character* getCharacter(std::string characterName);
        bool remove(std::string name);
        CharacterProxy* find(std::string name);
        Character* loadCharacter(std::string name);


    private:
        vector<CharacterProxy*>* _proxies;
        static CharacterRepository* _instance;
        CharacterRepository();
        void updateRepoReference();
        void loadGeneratedCharacters();

};
