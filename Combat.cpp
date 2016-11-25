#include "Combat.h"

using namespace d20Logic;
using namespace std;
#include <iostream>

Combat::Combat()
{
}


Combat::~Combat()
{
}

bool Combat::Collide(Character player, Character enemy)
{
	Dice dice1;
	int playerRoll;
	int enemyRoll;

	while (player.getHitPoints() >= 0 && enemy.getHitPoints() >= 0)
	{
		playerRoll = dice1.roll_d20();
		logInfo("Combat", "Collide", " Player rolled a d20 dice for initiative  ");

		int InitiativePlayer;
		InitiativePlayer = playerRoll + player.getModDexterity();
		enemyRoll = dice1.roll_d20();

		logInfo("Combat", "Collide", " Enemy rolled a d20 dice for initiative  ");
		int initiativeEnemy;
		initiativeEnemy = enemyRoll + enemy.getModDexterity();

		if (InitiativePlayer > initiativeEnemy)
		{
			logInfo("Combat", "Collide", " Player won the initiative and will attack ");
			player.attack(&enemy);//player will attack because he has a higher initative

			logInfo("Combat", "Collide", " Player just attacked the enemy  ");
			if (enemy.getHitPoints() > 0)
			{
				enemy.attack(&player);
				logInfo("Combat", "Collide", " Enemy executed an attack after player attack  ");
			}
			else
			{
				cout << "The Enemy has no more hit points , he is dead" << endl;
				return true;

			}
		}

		else if (initiativeEnemy > InitiativePlayer)
		{
			logInfo("Combat", "Collide", " Enemy won the iniative and will execute the attack  ");
			enemy.attack(&player);

			logInfo("Combat", "Collide", "Enemy executed attack after wining initiative   ");

			if (player.getHitPoints() > 0)
			{
				player.attack(&enemy);
				logInfo("Combat", "Collide", "Player executed attack after enemy attacked ");
			}
			else
			{
				cout << "Player is not able to attack because he is dead !!" << endl;
				return false;
			}
		}
	}
}


