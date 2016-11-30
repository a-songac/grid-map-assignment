#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include "Map.h"
#include "../service/MapValidator.h"
#include "../utils/ArrayUtils.h"
#include "../view/MapView.h"
#include "../entity/repo/CharacterRepository.h"

using namespace std;
Map::Map() {
    height = 7;
    width = 7;
    playerPosition = {-1, -1};


    std::vector<std::vector<Cell> > g(height, std::vector<Cell>(width));
    this->grid = g;

    Coordinate entryDoor = {0,0};
    Coordinate exitDoor = {height-1, width-1};

    grid.at(entryDoor.row).at(entryDoor.column).setType(Cell::TYPE_DOOR_ENTRY);
    grid.at(exitDoor.row).at(exitDoor.column).setType(Cell::TYPE_DOOR_EXIT);

    this->gameItems = new vector<GameItem*>();
    this->gamePlayers = new vector<GamePlayer*>();

}


Map::Map(int height, int width) {
    this->height = height;
    this->width = width;
    playerPosition = {-1, -1};

    std::vector<std::vector<Cell> > g(height, std::vector<Cell>(width));
    this->grid = g;

    this->gameItems = new vector<GameItem*>();
    this->gamePlayers = new vector<GamePlayer*>();
}

Map::Map(int height, int width, Coordinate entryDoor, Coordinate exitDoor) {
    this->height = height;
    this->width = width;
    playerPosition = {-1, -1};

    //grid = new Cell* [height];
    std::vector<std::vector<Cell> > g(height, std::vector<Cell>(width));
    this->grid = g;

    //initialize2DArray(grid, height, width);

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid.at(entryDoor.row).at(entryDoor.column).setType(Cell::TYPE_DOOR_ENTRY);
    grid.at(exitDoor.row).at(exitDoor.column).setType(Cell::TYPE_DOOR_EXIT);

    this->gameItems = new vector<GameItem*>();
    this->gamePlayers = new vector<GamePlayer*>();

}

Map::Map(Map* toCopy) {

    this->height = toCopy->getHeight();
    this->width = toCopy->getWidth();
    this->name = toCopy->getName();
    this->gameItems = new vector<GameItem*>();
    this->gamePlayers = new vector<GamePlayer*>();
    GameItem* gameItem;
    GamePlayer* gamePlayer;

    playerPosition = {-1, -1};

    std::vector<std::vector<Cell> > g(this->height, std::vector<Cell>(this->width));
    this->grid = g;

    Coordinate entryDoor = toCopy->getEntryDoorCoordinate();
    Coordinate exitDoor = toCopy->getExitDoorCoordinate();

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    this->grid.at(entryDoor.row).at(entryDoor.column).setType(Cell::TYPE_DOOR_ENTRY);
    this->grid.at(exitDoor.row).at(exitDoor.column).setType(Cell::TYPE_DOOR_EXIT);

    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++){
            this->grid.at(i).at(j).setType(toCopy->getCellType(i, j));
            this->grid.at(i).at(j).setOccupant(toCopy->getOccupant(i, j));
            this->grid.at(i).at(j).setOriginalOccupant(toCopy->getOriginalOccupant(Coordinate(i,j)));
        }
    }


    for (size_t i = 0; i < toCopy->getGameItems()->size(); i++) {
        gameItem = static_cast<GameItem*>(toCopy->getGameItems()->at(i));
        this->gameItems->push_back(new GameItem(gameItem));
    }

    for (size_t i = 0; i < toCopy->getGamePlayers()->size(); i++) {
        gamePlayer = static_cast<GamePlayer*>(toCopy->getGamePlayers()->at(i));
        this->gamePlayers->push_back(new GamePlayer(gamePlayer));
    }

}


Map::~Map() {

    delete this->gameItems;
    delete this->gamePlayers;

}


void Map::initDoors(Coordinate entryDoor, Coordinate exitDoor) {

    this->entryDoor.column = entryDoor.column;
    this->entryDoor.row = entryDoor.row;

    this->exitDoor.column = exitDoor.column;
    this->exitDoor.row = exitDoor.row;

    grid.at(entryDoor.row).at(entryDoor.column).setType(Cell::TYPE_DOOR_ENTRY);
    grid.at(exitDoor.row).at(exitDoor.column).setType(Cell::TYPE_DOOR_EXIT);
}



char Map::getOccupant(int row, int column) {
    if (isWall(row, column)) {
        return ' ';
    }
    return grid.at(row).at(column).getOccupant();
}


bool Map::fillCell(int row, int column, char occupant) {
    if (isWall(row, column)) {
        return false;
    }
    grid.at(row).at(column).setOccupant(occupant);
    Notify();
    return true;
}

bool Map::isOccupied(int row, int column) {
    return getOccupant(row, column) != Cell::OCCUPANT_EMPTY;
}

bool Map::isOccupiedByChest(int row, int column) {
    return getOccupant(row, column) != Cell::OCCUPANT_CHEST;
}

bool Map::isOccupiedByCharacter(int row, int column) {

    char occupant = getOccupant(row, column);
    return occupant == Cell::OCCUPANT_OPPONENT
        || occupant == Cell::OCCUPANT_FRIEND;
}

bool Map::validate() {
    MapValidator validator(this);
    return validator.validateMap();
}

void Map::render() {
    Notify();
}


bool Map::removeGameItem(Coordinate location) {
    Coordinate* elementLocation;
    for (size_t i = 0; i < this->gameItems->size(); i++) {
        elementLocation = this->gameItems->at(i)->getLocation();
        if (*elementLocation == location) {
            this->gameItems->erase(this->gameItems->begin() + i);
            return true;
        }
    }
    return false;
}
bool Map::removeGamePlayer(Coordinate location) {
    Coordinate* elementLocation;
    for (size_t i = 0; i < this->gamePlayers->size(); i++) {
        elementLocation = this->gamePlayers->at(i)->getLocation();
        if (*elementLocation == location) {
            this->gamePlayers->erase(this->gamePlayers->begin() + i);
            return true;
        }
    }
    return false;
}

void Map::setOriginalOccupant(Coordinate location, char occupant) {
    grid.at(location.row).at(location.column).setOriginalOccupant(occupant);
}

char Map::getOriginalOccupant(Coordinate location) {
    return grid.at(location.row).at(location.column).getOriginalOccupant();
}

void Map::setInGamePlayers(Character* character) {
    Character* realCharacter;
    Character* inGameCharacterCopy;
    GamePlayer* gamePlayer;
	
    for (size_t i = 0; i < this->gamePlayers->size(); i++) {
		gamePlayer = this->gamePlayers->at(i);
		realCharacter = CharacterRepository::instance()->getEntity(gamePlayer->getElementReference());
		inGameCharacterCopy = new Character(realCharacter);
		srand(time(NULL));
		int result = (rand() % 3);
		

		switch (2) {
		case 0:
			gamePlayer->setInGameCharacter(inGameCharacterCopy);
			break;
		case 1:
			gamePlayer->setInGameCharacter(factorBy(character, inGameCharacterCopy, 1));
			break;
		case 2:
			gamePlayer->setInGameCharacter(factorBy(character, inGameCharacterCopy, 0.5));
			break;
		case 3: 
			gamePlayer->setInGameCharacter(factorBy(character, inGameCharacterCopy, 2));
			break;
			
		}

    }
}
void Map::unsetInGamePlayers() {

    GamePlayer* gamePlayer;
    Character* character;
    for (size_t i = 0; i < this->gamePlayers->size(); i++) {
        gamePlayer = this->gamePlayers->at(i);
        character = gamePlayer->getInGameCharacter();
        delete character;
        gamePlayer->setInGameCharacter(nullptr);
    }
}

Character* Map::factorBy(Character* character, Character* characterCopy,double factor){
	
	characterCopy->setLevel(character->getLevel());
	characterCopy->setStrength(floor(character->getStrength()*factor));
	characterCopy->setCharisma(floor(character->getCharisma()*factor));
	characterCopy->setConstitution(floor(character->getConstitution()*factor));
	characterCopy->setDexterity(floor(character->getDexterity()*factor));
	characterCopy->setWisdom(floor(character->getWisdom()*factor));
	characterCopy->setIntelligence(floor(character->getIntelligence()*factor));
	characterCopy->setModStrength(characterCopy->modifier(characterCopy->getStrength()));
	characterCopy->setModCharisma(characterCopy->modifier(characterCopy->getCharisma()));
	characterCopy->setModConstitution(characterCopy->modifier(characterCopy->getConstitution()));
	characterCopy->setModDexterity(characterCopy->modifier(characterCopy->getDexterity()));
	characterCopy->setModWisdom(characterCopy->modifier(characterCopy->getWisdom()));
	characterCopy->setModIntelligence(characterCopy->modifier(characterCopy->getIntelligence()));
	characterCopy->armorClass();
	characterCopy->attackBonus();
	characterCopy->damageBonus();
	characterCopy->numberOfAttack();
	return characterCopy;



}