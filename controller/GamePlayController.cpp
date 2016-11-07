#include "GamePlayController.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../utils/IOUtils.h"
#include "MapInteractionHelper.h"


GamePlayController::GamePlayController(): level(0), map(nullptr) {}
GamePlayController::GamePlayController(Map* map, int level): level(level), map(map) {}

void GamePlayController::startGame() {

    bool gameOver = false;
    Coordinate entryDoor = this->map->getEntryDoorCoordinate();
    Coordinate nextPosition;

    this->map->movePlayer(entryDoor.row, entryDoor.column);

    do {

        nextPosition = MapInteractionHelper::readMapLocation(this->map, "Go to: ", "");
        this->map->movePlayer(nextPosition.row, nextPosition.column);


    } while (!gameOver);

}


