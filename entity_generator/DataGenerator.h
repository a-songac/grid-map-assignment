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
