#include "AggressivePlayerStrategy.h"

#include "ShortestPath.h"


void AggressivePlayerStrategy::move(GamePlayer* player) {
}
void AggressivePlayerStrategy::attack(GamePlayer* player, GamePlayer* victim) {
}
void AggressivePlayerStrategy::freeAction(GamePlayer* player) {
}
bool AggressivePlayerStrategy::turn(GamePlayer* player, Map* gameMap){

    Coordinate* currentLocation = player->getLocation();
    Coordinate playerPosition = gameMap->getPlayerPosition();
    Coordinate nextLocation;

    bool nextToPlayer =
            gameMap->isPlayerAdjacent(currentLocation->row, currentLocation->column);

    if( !nextToPlayer) {
        ShortestPath shortP(gameMap);
        nextLocation = shortP.computeShortestPath(*currentLocation, playerPosition).at(1);
        gameMap->fillCell(currentLocation->row, currentLocation->column, Cell::OCCUPANT_EMPTY);
        currentLocation->row = nextLocation.row;
        currentLocation->column = nextLocation.column;
        gameMap->fillCell(nextLocation.row, nextLocation.column, player->getType());

    }


    return true;
}
