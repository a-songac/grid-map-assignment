#include "GamePlayer.h"
#include "../service/FriendlyPlayerStrategy.h"
#include "../service/AggressivePlayerStrategy.h"
#include "../service/UserPlayerStrategy.h"

#include "Cell.h"

GamePlayer::GamePlayer(std::string elementReference, Coordinate* location, char type)
: GameElement(elementReference, location), type(type)
{
    if (type == Cell::OCCUPANT_FRIEND) {
        actionStrategy = new FriendlyPlayerStrategy();
    } else if (type == Cell::OCCUPANT_OPPONENT) {
        actionStrategy = new AggressivePlayerStrategy();
    } else {
        actionStrategy = new UserPlayerStrategy();
    }
}

GamePlayer::GamePlayer(GamePlayer* gamePlayer)
: GameElement(gamePlayer), type(gamePlayer->getType()) {
    if (type == Cell::OCCUPANT_FRIEND) {
        actionStrategy = new FriendlyPlayerStrategy();
    } else if (type == Cell::OCCUPANT_OPPONENT) {
        actionStrategy = new AggressivePlayerStrategy();
    } else {
        actionStrategy = new UserPlayerStrategy();
    }
}

GamePlayer::GamePlayer() : type(Cell::OCCUPANT_EMPTY) {}


bool GamePlayer::turn(Map* map) {

    this->actionStrategy->turn(this, map);

}
