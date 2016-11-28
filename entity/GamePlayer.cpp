#include "GamePlayer.h"
#include "../service/FriendlyPlayerStrategy.h"
#include "../service/AggressivePlayerStrategy.h"
#include "../service/UserPlayerStrategy.h"
#include "../service/Settings.h"
#include "../utils/LogUtils.h"
#include "../controller/MapInteractionHelper.h"

#include "Cell.h"

GamePlayer::GamePlayer(std::string elementReference, Coordinate* location, char type)
	: GameElement(elementReference, location), type(type), inGameCharacter(nullptr)
{
	if (type == Cell::OCCUPANT_FRIEND) {
		actionStrategy = new FriendlyPlayerStrategy();
	}
	else if (type == Cell::OCCUPANT_OPPONENT) {
		actionStrategy = new AggressivePlayerStrategy();
	}
	else {
		actionStrategy = new UserPlayerStrategy();
	}
}

GamePlayer::GamePlayer(GamePlayer* gamePlayer)
	: GameElement(gamePlayer), type(gamePlayer->getType()), inGameCharacter(nullptr) {
	if (type == Cell::OCCUPANT_FRIEND) {
		actionStrategy = new FriendlyPlayerStrategy();
	}
	else if (type == Cell::OCCUPANT_OPPONENT) {
		actionStrategy = new AggressivePlayerStrategy();
	}
	else {
		actionStrategy = new UserPlayerStrategy();
	}
}

GamePlayer::GamePlayer() : type(Cell::OCCUPANT_EMPTY) {}


bool GamePlayer::turn(Map* map) {
	if (SETTINGS::LOG_GAME) logInfo("GamePlayer", "turn", "Turn switching: " + getElementReference() + " - " + MapInteractionHelper::coordinateToString(getLocation()));
	return this->actionStrategy->turn(this, map);

}


std::string GamePlayer::getTypeName() {
	if (type == Cell::OCCUPANT_FRIEND) {
		return "Friendly";
	}
	return "Hostile";
}

void GamePlayer::makeHostile() {
    if (this->type == Cell::OCCUPANT_FRIEND) {
        this->type = Cell::OCCUPANT_OPPONENT;
        this->actionStrategy = new AggressivePlayerStrategy();
    }
}

void GamePlayer::display() {
    std::string locationString = MapInteractionHelper::coordinateToString(this->location);
    cout << inGameCharacter->getName() << " - " << getTypeName()
            << " - " << locationString << " - HP: " <<  inGameCharacter->getHitPoints() << endl;
}
