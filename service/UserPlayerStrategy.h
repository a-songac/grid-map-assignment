/// @file
/// @brief
/// Header file for UserPlayerStrategy.class.  Concrete strategy of the PlayerStrategy used for the user's character. In the case of the user,
/// those action a take by the user through command line interface interaction \n\n
///
/// @details
/// 1. Game Rules: While in a game, when it is the turn of the user player to take action, he can move, attack or exectue a free action  \n\n
/// 2. Design: Concrete implementation of a strategy for the PlayerStrategy \n\n
/// 3. Libraries: standard libraries: sstream, string.



#pragma once

#include "PlayerStrategy.h"
#include "../entity/Character.h"

class UserPlayerStrategy : public PlayerStrategy {
    public:
        void move(GamePlayer* player, Map* map);
        void attack(GamePlayer* player, GamePlayer* victim, bool melee);
        void freeAction(GamePlayer* player);
        bool turn(GamePlayer* player, Map* map);
        void modifyGameSettings();
    private:
        void backpackOption(Character* character);
        bool postAttack(Character* character, Map* map);
        void endGameLevelUp(Character* character);

};
