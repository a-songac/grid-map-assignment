#pragma once

#include "Character.h"


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>

class Game {

    public:
        Game(std::string gameName, Character* character);

        save(std::string saveName);
        load(std::string saveName);

    private:
        Character* userCharacter;
        std::string gameSaveName; // give this name to the save file of the character too

        // add more info with regard to the game progress in the campaing

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & gameSaveName;
        }

}

