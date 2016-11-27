
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
