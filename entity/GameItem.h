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


