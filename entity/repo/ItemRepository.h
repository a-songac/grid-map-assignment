/// @file
/// @brief Header file for implementation of ItemRepository
///
/// @details  1. Game Rules: NONE \n\n
/// 2. inherits from Repository template, see Repopsitory.h file for more info
/// 3. Libraries: NONE


#pragma once

#include "../Item.h"
#include "../../core/Repository.h"
#include <vector>



class ItemRepository : public Repository<Item> {
    public:
        static ItemRepository* instance();

    private:
        ItemRepository();
        static ItemRepository* _instance;
};
