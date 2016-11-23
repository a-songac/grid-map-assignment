#pragma once

class GamePlayer; // Forward declare to resolve cyclic dependency issue between strategy and GamePlaeyer
class Map; // Forward declare to resolve cyclic dependency issue between strategy and GamePlaeyer

#include "../entity/GamePlayer.h"
#include "../entity/Map.h"



class PlayerStrategy
{
    public:
        PlayerStrategy();

        virtual void move(GamePlayer* player) = 0;
        virtual void attack(GamePlayer* player, GamePlayer* victim) = 0;
        virtual void freeAction(GamePlayer* player) = 0;
        virtual bool turn(GamePlayer* player, Map* map) = 0;

    protected:

    private:
};


