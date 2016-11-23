#pragma once

class PlayerStrategy; // forward reference

#include "GameElement.h"
#include "Coordinate.h"
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


    protected:

    private:
        PlayerStrategy* actionStrategy;
        char type;

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
