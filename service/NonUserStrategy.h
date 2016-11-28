/// @file
/// @brief
/// Header file for NonUserStrategy.class.  Partially concrete strategy of the PlayerStrategy used for a non user character.
/// Implements the move and turn methods, since they are common to all non user players. Uses shortest path algorithm to establish
/// the direction where it needs to go (see  ShortestPath class)\n\n
///
/// @details
/// 1. Game Rules: While in a game, when it is the turn of a player to take action, it can move, attack or exectue a free action.
///    A non user player will move towards the user character. \n\n
/// 2. Design: Paritially concrete implementation of a strategy for the PlayerStrategy. \n\n
/// 3. Libraries: standard libraries: sstream, string.

#pragma once

#include "PlayerStrategy.h"
#include "ShortestPath.h"


class NonUserStrategy : public PlayerStrategy {
    public:
        NonUserStrategy() {
            distanceFromUser = -1;
        }

        // A non user automatically moves towards the user
        void move(GamePlayer* player, Map* map);
        bool turn(GamePlayer* player, Map* map);

    protected:
        int distanceFromUser;

};
