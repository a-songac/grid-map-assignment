#pragma once

#include "NonUserStrategy.h"

class FriendlyPlayerStrategy : public NonUserStrategy {
    public:
        void attack(GamePlayer* player, GamePlayer* victim, bool melee);
        void freeAction(GamePlayer* player);

};
