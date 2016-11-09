#pragma once

#include "../entity/Map.h"

class GamePlayController {
    public:
        GamePlayController();
        void newGame();


    private:
        Map* map;
        int level;
        void selectMap();
        void startGame();

};
