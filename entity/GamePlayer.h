/// @file
/// @brief
/// Header file for GamePlayer.class.  Wrapper for the characters a map may contain \n\n
///
/// @details
/// 1. Game Rules: A map may contain characters that are either friendly or hostile. These items have a precise location on the map.  \n\n
/// 2. Design: The GamePlayer is a child of the GameElement class.  It also uses Strategy Pattern (class member actionStrategy) to determine the action it takes on the map (see PlayerStrategy class) \n\n
/// 3. Libraries: \n
///     - Boost Library used for serialization: eases the process of serialization and minimizes the work needed if the schema of the class changes \n
///     - Standard Libraries: string

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

        PlayerStrategy* getActionStrategy();


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

inline PlayerStrategy* GamePlayer::getActionStrategy() {
    return this->actionStrategy;
}

