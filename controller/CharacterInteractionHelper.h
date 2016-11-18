#pragma once

#include "../entity/Character.h"


class CharacterInteractionHelper {
    public:
        static Character* selectCharacter();
        static std::string getStrategyName(char type);

};
