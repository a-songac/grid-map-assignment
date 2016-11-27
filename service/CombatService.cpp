#include "CombatService.h"
#include "ShortestPath.h"
#include "Settings.h"
#include "../entity/Dice.h"
#include "../utils/LogUtils.h"

#include <sstream>

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

bool CombatService::attack(Character* attacker, Character* victim) {

    Dice dice1;
	int attackerRoll, attackerInitiative, victimRoll, victimInitiative;
    stringstream sStream;

	while (attacker->getHitPoints() >= 0 && victim->getHitPoints() >= 0)
	{
		attackerRoll = dice1.roll_d20();
		sStream << "Attacker rolled a d20 dice for initiative resulting: [" << attackerRoll << "]";
		if(SETTINGS::LOG_CHAR)logInfo("CombatService", "attack", sStream.str());
		sStream.str("");

		attackerInitiative = attackerRoll + attacker->getModDexterity();

		victimRoll = dice1.roll_d20();

		logInfo("CombatService", "attack", " Enemy rolled a d20 dice for initiative  ");
		victimInitiative = victimRoll + victim->getModDexterity();

		if (attackerInitiative > victimInitiative)
		{
			logInfo("CombatService", "attack", " Attacker won the initiative and will attack");
			attacker->attack(victim);//player will attack because he has a higher initative

			logInfo("CombatService", "attack", "Attacker just attacked the victim");
			if (victim->getHitPoints() > 0)
			{
				victim->attack(attacker);
				logInfo("CombatService", "attack", "Vicim executed a counter-attack");
			}
			else
			{
				cout << "The Enemy has no more hit points , he is dead" << endl;
				return true;

			}
		}

		else if (victimInitiative > attackerInitiative)
		{
			logInfo("CombatService", "attack", "Victim won the iniative and will execute the attack");
			victim->attack(attacker);

			logInfo("CombatService", "attack", "Vicim executed attack after wining initiative");

			if (attacker->getHitPoints() > 0)
			{
				attacker->attack(victim);
				logInfo("CombatService", "attack", "Player executed counter-attack");
			}
			else
			{
				cout << "Player is not able to attack because he is dead !!" << endl;
				return false;
			}
		}
	}
    return true;

}
