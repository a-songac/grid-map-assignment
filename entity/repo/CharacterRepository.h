/// @file
/// @brief Header file for implementation of CharacterRepository
///        and struct declaration for Coordinate.struct
/// @details  1. Game Rules: NONE \n\n
/// 2. inherits from Repository template, see Repopsitory.h file for more info
/// 3. Libraries: NONE


#pragma once

#include "../../core/Repository.h"
#include <vector>


class CharacterRepository : public Repository<Character> {
    public:
        static CharacterRepository* instance();

    private:
        CharacterRepository();
        static CharacterRepository* _instance;

};
