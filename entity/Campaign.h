/// @file
/// @brief Header file containing class declaration for Campaign.class
/// @details  1. Game Rules: The Map enforces that a cell of type wall cannot be occupied \n\n
/// 2. Model class from the MVC pattern. The Campaign keeps a vector of maps. \n\n
/// 3. Libraries: The campaign uses the boost archive and vector serialization libraries in order for its state to be saved/loaded.

#pragma once
#include "Map.h"
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>


class Campaign {
    public:
        Campaign();
        Campaign(vector<Map> m);
    
        bool validate();
        vector<Map> getMaps();
    
    
    private:
    
        std::vector<Map> maps;
    
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & maps;
        }

    
};

inline vector<Map> Campaign::getMaps(){
    return maps;
}