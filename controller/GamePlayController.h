#pragma once

#include "../entity/Map.h"
#include "../entity/Character.h"
#include "../entity/Game.h"


class GamePlayController {
    public:
        GamePlayController();
        void newGame();
        void loadGame();


    private:
        Map* map;
        int level;
        void startGame(Game*);

};
