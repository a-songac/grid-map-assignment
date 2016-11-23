#pragma once

#include "PlayerStrategy.h"

class FriendlyPlayerStrategy : public PlayerStrategy {
    public:
        void move(const GamePlayer* player);
        void attack(const GamePlayer* player, GamePlayer* victim);
        void freeAction(const GamePlayer* player);
        bool turn(const GamePlayer* player, const Map* map);


};
