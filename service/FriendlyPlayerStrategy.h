/// @file
/// @brief
/// Header file for FriendlyPlayerStrategy.class.  Concrete strategy of the PlayerStrategy (derived from NonUserStrategy) used for a friendly non user character.
/// Implements attack method.
///
/// @details
/// 1. Game Rules: While in a game, when it is the turn of a friendly player to take action, either it moves towards the user character, or does nothing when next to him. \n\n
/// 2. Design: Concreteimplementation of a strategy for the PlayerStrategy. Derived from NonUserStrategy class \n\n
/// 3. Libraries: standard libraries: none

#pragma once

#include "NonUserStrategy.h"

class FriendlyPlayerStrategy : public NonUserStrategy {
    public:
        void attack(GamePlayer* player, GamePlayer* victim, bool melee);
        void freeAction(GamePlayer* player);

};
