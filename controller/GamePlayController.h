#pragma once

#include "../entity/Map.h"

class GamePlayController {
    public:
        GamePlayController();
        GamePlayController(Map* map, int level);

        void startGame();


    private:
        Map* map;
        int level;

};
