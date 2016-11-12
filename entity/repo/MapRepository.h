/// @file
/// @brief Header file for implementation of MapRepository
///        and struct declaration for Coordinate.struct
/// @details  1. Game Rules: NONE \n\n
/// 2. inherits from Repository template, see Repopsitory.h file for more info
/// 3. Libraries: NONE


#pragma once

#include "../Map.h"
#include "../../core/Repository.h"
#include <vector>



class MapRepository : public Repository<Map> {
    public:
        static MapRepository* instance();
        MapRepository();

    private:
        void loadGeneratedEntities();
        static MapRepository* _instance;

};
