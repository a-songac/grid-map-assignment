/// @file
/// @brief
/// Header file for PlayerStrategy.class.  Interface for implementation of strategy pattern for a player action in the game. \n\n
///
/// @details
/// 1. Game Rules: While in a game, when it is the turn of a player to take action, it can move, attack or exectue a free action  \n\n
/// 2. Design: Interface of the Strategy Pattern for player action \n\n
/// 3. Libraries: none

#pragma once

class GamePlayer; // Forward declare to resolve cyclic dependency issue between strategy and GamePlaeyer
class Map; // Forward declare to resolve cyclic dependency issue between strategy and GamePlaeyer

#include "../entity/GamePlayer.h"
#include "../entity/Map.h"



class PlayerStrategy
{
    public:
        PlayerStrategy();

        virtual void move(GamePlayer* player, Map* map) = 0;
        virtual void attack(GamePlayer* player, GamePlayer* victim, bool melee) = 0;
        virtual void freeAction(GamePlayer* player) = 0;
        virtual bool turn(GamePlayer* player, Map* map) = 0;

    protected:

    private:
};


