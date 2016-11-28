/// @file
/// @brief Header file for implementation of GameRepository
/// @details  1. Game Rules: NONE \n\n
/// 2. inherits from Repository template, see Repopsitory.h file for more info
/// 3. Libraries: NONE


#pragma once

#include "../Map.h"
#include "../../core/Repository.h"
#include <vector>



class GameRepository : public Repository<Game> {
    public:
        static GameRepository* instance();

    private:
        GameRepository();
        void loadGeneratedEntities();
        static GameRepository* _instance;

};
