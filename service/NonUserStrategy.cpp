#include "NonUserStrategy.h"

#include "ShortestPath.h"
#include "../service/Settings.h"
#include "../service/CombatService.h"
#include "../utils/LogUtils.h"
#include "../controller/MapInteractionHelper.h"


void NonUserStrategy::move(GamePlayer* player, Map* gameMap) {
    if (SETTINGS::LOG_GAME) logInfo("NonUserStrategy", "move", "Moving attempt from: " + player->getElementReference() + " - " + MapInteractionHelper::coordinateToString(player->getLocation()));
    this->distanceFromUser = -1;

    Coordinate* currentLocation = player->getLocation();
    Coordinate playerPosition = gameMap->getPlayerPosition();
    Coordinate nextLocation;
    ShortestPath shortestPath(gameMap);
    vector<Coordinate> pathToUser;


    pathToUser = shortestPath.computeShortestPath((*currentLocation), playerPosition, false);
    nextLocation = pathToUser.at(1);

    if (gameMap->isOccupiedByCharacter(nextLocation.row, nextLocation.column)) {

        // Check for a path that avoids game characters.  If any, use this one instead, otherwise stay
        pathToUser =  shortestPath.computeShortestPath((*currentLocation), playerPosition, true);
        if (pathToUser.size() == 0) {
            if (SETTINGS::LOG_GAME) logInfo("NonUserStrategy", "move", "Cannot move: " + player->getElementReference() + " - " + MapInteractionHelper::coordinateToString(player->getLocation()));
            return;
        }

        nextLocation = pathToUser.at(1);
    }

    this->distanceFromUser = pathToUser.size() - 1;

    // put back what was initially on this cell if it was an item
    // could be a chest that a monster stepped on
    char toPutBack = gameMap->getOriginalOccupant(*currentLocation) == Cell::OCCUPANT_CHEST?
            Cell::OCCUPANT_CHEST:
            Cell::OCCUPANT_EMPTY;

    gameMap->fillCell(
        currentLocation->row,
        currentLocation->column,
        toPutBack);

    currentLocation->row = nextLocation.row;
    currentLocation->column = nextLocation.column;

    gameMap->fillCell(nextLocation.row, nextLocation.column, player->getType());
    if (SETTINGS::LOG_GAME) logInfo("NonUserStrategy", "move", "Moved to new location: " + player->getElementReference() + " - " + MapInteractionHelper::coordinateToString(player->getLocation()));

}

bool NonUserStrategy::turn(GamePlayer* player, Map* gameMap) {

    bool distanceAttack = false;
    bool nextToPlayer = false;
    bool gameOver = false;

    Coordinate* currentLocation = player->getLocation();
    Coordinate playerPosition = gameMap->getPlayerPosition();

    nextToPlayer =
            gameMap->isPlayerAdjacent(currentLocation->row, currentLocation->column);

    if( !nextToPlayer) {
        this->move(player, gameMap);
    }

    // attack if next or at 1 cell from user
    else  {
        this->distanceFromUser = 1;
        this->attack(player, gameMap->getUserGamePlayer(), this->distanceFromUser == 1);

        if (gameMap->getUserGamePlayer()->getInGameCharacter()->getHitPoints() <= 0) {
            gameOver = true;
        } else {
            CombatService::eliminateDeadBodies(gameMap);
        }

    }

    return gameOver;
}
