#pragma once

#include "Coordinate.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>


class GameElement
{
    public:
        GameElement(std::string elementReference, Coordinate* location);
        GameElement();
        GameElement(GameElement* toCopy);

        // GETTER & SETTER
        std::string getElementReference() { return elementReference; }
        void setElementReference(std::string val) { elementReference = val; }
        Coordinate* getLocation() { return location; }
        void setLocation(Coordinate* val) { location = val; }

    protected:
        std::string elementReference;
        Coordinate* location;

    private:
        // Serializer
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & location;
            ar & elementReference;
        }

};

