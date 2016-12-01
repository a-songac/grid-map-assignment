/// @file
/// @brief
/// Header file for GameItem.class.  Wrapper for the items in chests a map may contain \n\n
///
/// @details
/// 1. Game Rules: A map may contain items in a chest that are collectable by the user. These items have a precise location on the map.  \n\n
/// 2. Design: The GameItem is a child of the GameElement class \n\n
/// 3. Libraries: \n
///     - Boost Library used for serialization: eases the process of serialization and minimizes the work needed if the schema of the class changes \n
///     - Standard Libraries: string

#pragma once

#include "GameElement.h"
#include "Coordinate.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>


class GameItem : public GameElement
{
    public:
        GameItem(std::string elementReference, Coordinate* location);
        GameItem();
        GameItem(GameItem* gameItem);


        // GETTER & SETTER
        bool getCollected() { return collected; }
        void setCollected(bool val) { collected = val; }

        void display();

    protected:

    private:
        bool collected;

        // Serializer
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & collected;
            ar & elementReference;
            ar & location;
        }
};


