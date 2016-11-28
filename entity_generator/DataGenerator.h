/// @file
/// @brief
/// Header file for MapGenerator.class.  Generates data for testing
///
/// @details
/// 1. Game Rules:  None.   \n\n
/// 2. Design: None \n\n
/// 3. Libraries: \n
///     - Standard Libraries

#pragma once

#include "../entity/Map.h"
#include "../entity/Character.h"
#include "../entity/Item.h"

class DataGenerator {
    public:
        static void generateForDemoGame();
    private:
        static Map* genMap(Character* friendToAdd);
        static Character* genCharacter();

};
