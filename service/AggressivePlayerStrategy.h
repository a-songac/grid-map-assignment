
#pragma once

#include "NonUserStrategy.h"


class AggressivePlayerStrategy : public NonUserStrategy {
    public:
        void attack(GamePlayer* player, GamePlayer* victim);
        void freeAction(GamePlayer* player);

};
