#include "DataGenerator.h"
#include "../entity/Cell.h"
#include "../entity/repo/MapRepository.h"
#include "../entity/repo/ItemRepository.h"
#include "../entity/repo/CharacterRepository.h"

using namespace std;

void DataGenerator::generateForDemoGame() {


    string mapName = "mapa3";
    string userName= "usera3";
    string oppName= "creaturea3";
    string weaponName = "sworda3";
    string shieldName = "shielda3";


    // CHARACTERS
    Character* user;
    Character* creature;
    user = DataGenerator::genCharacter();
    user->setName(userName);
    creature = DataGenerator::genCharacter();
    creature->setName(oppName);
    // todo: add worn items
    // todo: save


    // MAP
    Map* map = DataGenerator::genMap(creature);
    map->setName(mapName);
    MapRepository::instance()->save(mapName, map);





}


Map* DataGenerator::genMap(Character* friendToAdd) {
    Coordinate entryDoor = {3,0};
    Coordinate exitDoor = {3,6};
    Map* map = new Map(7, 7,entryDoor, exitDoor);
    map->setName("mapa3");
    map->setCellType(2, 3, Cell::TYPE_WALL);
    map->setCellType(2, 4, Cell::TYPE_WALL);
    map->setCellType(2, 5, Cell::TYPE_WALL);
    map->setCellType(2, 6, Cell::TYPE_WALL);
    map->fillCell(5, 5, Cell::OCCUPANT_FRIEND);

    Coordinate* creatureLocation = new Coordinate(5,5);
    GamePlayer* creaturePlayer = new GamePlayer(friendToAdd->getName(), creatureLocation, Cell::OCCUPANT_FRIEND);
    map->getGamePlayers()->push_back(creaturePlayer);

    return map;
}


Character* DataGenerator::genCharacter() {

    Character* character = new Character();
	CharacterView* cView = new CharacterView(character);
	character->preGenAbilityScores();
	character->setLevel(2);
    character->armorClass();
    character->attackBonus();
    character->damageBonus();
    character->display();

}



