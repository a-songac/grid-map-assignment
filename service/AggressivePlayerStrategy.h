
#pragma once

#include "PlayerStrategy.h"

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        void move(const GamePlayer* player);
        void attack(const GamePlayer* player, GamePlayer* victim);
        void freeAction(const GamePlayer* player);
};
