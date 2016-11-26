
#pragma once

#include "PlayerStrategy.h"
#include "../entity/Character.h"

class UserPlayerStrategy : public PlayerStrategy {
    public:
        void move(GamePlayer* player, Map* map);
        void attack(GamePlayer* player, GamePlayer* victim);
        void freeAction(GamePlayer* player);
        bool turn(GamePlayer* player, Map* map);
        void modifyGameLogSettings();
    private:
        void backpackOption(Character* character);
        bool postAttack(Character* character, Map* map);
        void endGameLevelUp(Character* character);

};
