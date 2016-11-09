#include "GamePlayController.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <list>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../utils/IOUtils.h"
#include "MapInteractionHelper.h"
#include "../entity/MapProxy.h"
#include "../entity/repo/MapRepository.h"
#include "../utils/LogUtils.h"


GamePlayController::GamePlayController(): level(1), map(nullptr) {}


void GamePlayController::newGame() {

    bool gameLoop = false;

    cout << "\n************* New Game *************" << endl << endl;

    do {

        this->selectMap();
        this->startGame();


    } while (gameLoop);

}

void GamePlayController::selectMap() {

    bool confirm = false;
    string filename;
    vector<MapProxy*> mapProxies = *(MapRepository::instance()->listAll());

    if(mapProxies.size() > 0){

        do {
            cout << "Please select a map: " << endl;
            for (int i = 0; i < mapProxies.size(); i++) {
                cout << i+1 << ":" << mapProxies.at(i)->getFileName() << endl;
            }
            int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, mapProxies.size());
            this->map = mapProxies.at(index-1)->getMap();
            this->map->render();
            confirm = readYesNoInput("You confirm the selection of this map displayed above?[Y/n]: ", true);

        } while (!confirm);
    } else {
        cout << "Error could not load maps" << endl;
    }

}


void GamePlayController::startGame() {

    bool startGame = readYesNoInput("Ready to start the game?[Y/n]", 1);
    if (!startGame) {
        return;
    }

    if (nullptr != this->map) {

        bool gameOver = false;

        cout << "\n************* Start Game *************" << endl << endl;
        Coordinate entryDoor = this->map->getEntryDoorCoordinate();
        Coordinate nextPosition;

        this->map->movePlayer(entryDoor.row, entryDoor.column);

        do {

            nextPosition = MapInteractionHelper::readMapLocation(this->map, "Go to: ", "");
            this->map->movePlayer(nextPosition.row, nextPosition.column);


        } while (!gameOver);
    } else {
        logError("GamePlayController", "startGame", "No map was loaded for this game");
    }

}
