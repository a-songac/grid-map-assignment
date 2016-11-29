#include "CombatService.h"
#include "ShortestPath.h"
#include "Settings.h"
#include "../entity/Dice.h"
#include "../entity/Cell.h"
#include "../utils/LogUtils.h"
#include "../utils/IOUtils.h"

#include <sstream>

using namespace std;

bool CombatService::isAdjacent(Coordinate origin, Coordinate destination) {

	return (destination.row == origin.row + 1 && destination.column == origin.column)
		|| (destination.row == origin.row - 1 && destination.column == origin.column)
		|| (destination.row == origin.row && destination.column == origin.column + 1)
		|| (destination.row == origin.row && destination.column == origin.column - 1);

}


bool CombatService::canRangeAttack(Coordinate origin, Coordinate destination, int range, Map* gameMap) {
	ShortestPath shortestPath(gameMap);
	vector<Coordinate> pathToUser;
	pathToUser = shortestPath.computeShortestPath(origin, destination, false);

	return pathToUser.size() > 1 && (pathToUser.size() - 1) <= range;

}

bool CombatService::attack(Character* attacker, Character* victim, bool melee) {

    Dice dice1;

    bool range = !melee;
    stringstream sstream;
    string attackTypeName = range? "Range" : "Melee";
    if(SETTINGS::LOG_CHAR)
        logInfo("Character", "attack", attackTypeName + " attack start: " + attacker->getName() + " on " + victim->getName());

    if(SETTINGS::LOG_CHAR)
        logInfo("Character", "attack", "Compute attack attempt score...");


    int attackRoll = dice1.roll_d20();

    sstream << "d20 dice roll result: " << attackRoll;
    if(SETTINGS::LOG_CHAR)
        logInfo("Character", "attack",  sstream.str());
    sstream.str("");

	int attackModifier = attacker->getAttackBonus();

    sstream << "Attack modifier value: " << attackModifier;
    if(SETTINGS::LOG_CHAR)
        logInfo("Character", "attack",  sstream.str());
    sstream.str("");

    int weaponModifier;
    if (range) {
        weaponModifier = attacker->getModDexterity();
        sstream << "Weapon dexterity modifier value for range attack: " << weaponModifier;
    } else {
        weaponModifier = attacker->getModStrength();
        sstream << "Weapon strength modifier value for melee attack: " << weaponModifier;
    }

    if(SETTINGS::LOG_CHAR)
        logInfo("Character", "attack",  sstream.str());
    sstream.str("");

    // How is the attackB

    int rollAndBonus = attackRoll + weaponModifier + attackModifier;
    sstream << "Attacker attack attempt total value: " << rollAndBonus << " VS victim's armor class value: " << victim->getArmorClass();
    if(SETTINGS::LOG_CHAR)
        logInfo("Character", "attack", sstream.str());
    sstream.str("");

    if (rollAndBonus > victim->getArmorClass())
    {
        int damageRollValue = dice1.roll_d8();
        sstream << "d8 dice damage roll result: " << damageRollValue;
        if(SETTINGS::LOG_CHAR)
            logInfo("Character", "attack",  sstream.str());
        sstream.str("");

        sstream << "Damage modifier value: " << weaponModifier;
        if(SETTINGS::LOG_CHAR)
            logInfo("Character", "attack",  sstream.str());
        sstream.str("");

        int damageinCombat;

        //TODO How do i compute the damage modifier?
        damageinCombat = damageRollValue + weaponModifier;


        sstream << "Damage inflicted on victim's current HP: " << damageinCombat << "/" << victim->getHitPoints();
        if(SETTINGS::LOG_CHAR)
            logInfo("Character", "attack",  sstream.str());
        sstream.str("");

        victim->setHitPoints(victim->getHitPoints() - damageinCombat);
    }
    else
    {
        if(SETTINGS::LOG_CHAR)
            logInfo("Character", "attack", "Attack missed");
    }
    return true;
}


void CombatService::eliminateDeadBodies(Map* map) {

    GamePlayer* playerAt;
    for (size_t i = 0; i < map->getGamePlayers()->size(); i++) {
        playerAt = map->getGamePlayers()->at(i);
        if (playerAt->getInGameCharacter()->getHitPoints() <= 0)
        {
            map->getGamePlayers()->erase(map->getGamePlayers()->begin()+i);
            map->fillCell(
                    playerAt->getLocation()->row,
                    playerAt->getLocation()->column,
                     Cell::OCCUPANT_EMPTY);
            cout << "Character died: ";

            playerAt->display();
            readStringInput("Press any key to continue", "");
        }
    }
}
