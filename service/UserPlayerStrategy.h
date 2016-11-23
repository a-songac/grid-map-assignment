
#pragma once

#include "PlayerStrategy.h"

class UserPlayerStrategy : public PlayerStrategy {
    public:
        void move(GamePlayer* player, Map* map);
        void attack(GamePlayer* player, GamePlayer* victim);
        void freeAction(GamePlayer* player);
        bool turn(GamePlayer* player, Map* map);


};
