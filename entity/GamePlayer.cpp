#include "GamePlayer.h"

#include "Cell.h"

GamePlayer::GamePlayer(std::string elementReference, Coordinate* location, char type)
: GameElement(elementReference, location), type(type)
{
}

GamePlayer::GamePlayer(GamePlayer* gamePlayer)
: GameElement(gamePlayer), type(gamePlayer->getType()) {
}

GamePlayer::GamePlayer() : type(Cell::OCCUPANT_EMPTY) {}
