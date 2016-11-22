#pragma once

class GamePlayer; // Forward declare to resolve cyclic dependency issue between strategy and GamePlaeyer

#include "../entity/GamePlayer.h"


class PlayerStrategy
{
    public:
        PlayerStrategy();
        virtual ~PlayerStrategy();

        virtual void move(const GamePlayer* player) = 0;
        virtual void attack(const GamePlayer* player, GamePlayer* victim) = 0;
        virtual void freeAction(const GamePlayer* player) = 0;
        virtual void getType() = 0;

    protected:

    private:
};


