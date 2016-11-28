/// @file
/// @brief
/// Header file for AggressivePlayerStrategy.class.  Concrete strategy of the PlayerStrategy (derived from NonUserStrategy) used for a hostile non user character.
/// Implements attack method.
///
/// @details
/// 1. Game Rules: While in a game, when it is the turn of a hostile player to take action, either it moves towards the user character, or attacks him when next to him. \n\n
/// 2. Design: Concreteimplementation of a strategy for the PlayerStrategy. Derived from NonUserStrategy class \n\n
/// 3. Libraries: standard libraries: none


#pragma once

#include "NonUserStrategy.h"


class AggressivePlayerStrategy : public NonUserStrategy {
    public:
        void attack(GamePlayer* player, GamePlayer* victim, bool melee);
        void freeAction(GamePlayer* player);

};
