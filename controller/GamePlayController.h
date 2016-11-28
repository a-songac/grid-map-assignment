#pragma once

#include "../entity/Map.h"
#include "../entity/Character.h"
#include "../entity/Game.h"
#include "../entity/Campaign.h"


class GamePlayController {
    public:
        GamePlayController();
        void newGame();
        void loadGame();


    private:
        Campaign* campaign;
        Map* map;
        int level;
        void startGame(Game*);

};
