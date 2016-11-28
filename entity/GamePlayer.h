#pragma once

class PlayerStrategy; // forward reference

#include "GameElement.h"
#include "Coordinate.h"
#include "Character.h"
#include "../service/PlayerStrategy.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>


class GamePlayer : public GameElement
{
    public:
        GamePlayer(std::string elementReference, Coordinate* location, char type);
        GamePlayer();
        GamePlayer(GamePlayer* gamePlayer);
        char getType();

        bool turn(Map* map);
        std::string getTypeName();

        void setInGameCharacter(Character* charac);
        Character* getInGameCharacter();

        void makeHostile();
        void display();


    protected:

    private:
        PlayerStrategy* actionStrategy;
        char type;
        Character* inGameCharacter;

        // Serializer
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & type;
            ar & elementReference;
            ar & location;
        }

};


inline char GamePlayer::getType() {
    return this->type;
}


inline void GamePlayer::setInGameCharacter(Character* charac) {
    this->inGameCharacter = charac;
}
inline Character* GamePlayer::getInGameCharacter() {
    return this->inGameCharacter;
}


