#pragma once

#include "Character.h"


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>

class Game {

    public:
        Game(std::string gameName, Character* character, std::string campaignName, int currentMapIndex);
        Game(Game* toCopy);
        Game();

        void save(std::string saveName);
        Game* load(std::string saveName);

        void setGameSaveName(std::string name);
        std::string getGameSaveName();

        void setUserCharacter(Character* charac);
        Character* getUserCharacter();

        void setCharacterName(std::string);
        std::string getCharacterName();
    
        void setCampaignName(std::string c);
        std::string getCampaignName();
    
        void setMapIndex(int i);
        int getMapIndex();

    private:
        Character* userCharacter;
        std::string gameSaveName; // give this name to the save file of the character too
        std::string characterName;
        std::string campaignName;
        int currentMapIndex;
        // add more info with regard to the game progress in the campaing

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & gameSaveName;
            ar & characterName;
            ar & campaignName;
            ar & currentMapIndex;
        }

};


inline void Game::setGameSaveName(std::string name) {
    this->gameSaveName = name;
}
inline std::string Game::getGameSaveName() {
    return this->gameSaveName;
}

inline void Game::setUserCharacter(Character* charac) {
    this->userCharacter = charac;
}
inline Character* Game::getUserCharacter() {
    return this->userCharacter;
}

inline void Game::setCharacterName(std::string name){
    this->characterName = name;
}
inline std::string Game::getCharacterName() {
    return this->characterName;
}

inline void Game::setCampaignName(std::string c){
    this->campaignName = c;
}

inline std::string Game::getCampaignName(){
    return this->campaignName;
}

inline void Game::setMapIndex(int i){
    this->currentMapIndex = i;
}

inline int Game::getMapIndex(){
    return this->currentMapIndex;
}

