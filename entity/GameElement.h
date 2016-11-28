/// @file
/// @brief
/// Header file for GameElement.class.  Wrapper for the elements that a map may contain: items (in chest) and map characters.  Adds the notion of positin on the map of these items. \n\n
///
/// @details
/// 1. Game Rules: A map may contain items in a chest and other game characters. These elements have a precise location on the map  \n\n
/// 2. Design: The GameElement class is a base class for the specific elements a map may contain, namely items and characters \n\n
/// 3. Libraries: \n
///     - Boost Library used for serialization: eases the process of serialization and minimizes the work needed if the schema of the class changes \n
///     - Standard Libraries: string


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

