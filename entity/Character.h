//!  Character.hpp\n
//!  Character\n
//
//!  Created by Hyjaz Loudin on 2016-10-15.\n
//!  Copyright © 2016 Hyjaz Loudin. All rights reserved.\n
//! //! @file \n
//! @brief Header file for the Character class  \n
//!
//! (1) The Game rules are as followed:\n
//!     \t A user is of class Fighter\n
//!     \t A user chooses its level at the beninning\n
//!     \t Depending on the level the user chooses to start the game as, this will reflect how much hitpoints, attack bonus and attack damage he will have\n
//!     \t The ability scores are generated randomly, by roling 4 dices and summing them.\n
//!     \t Once we have the ability score we calculate the modifiers. The modifiers are calculated as follow: modifiers = (ability score - 10)/2.\n
//!     \t It is going to be the the (ability score - 10)/2.\n
//!     \t We then add the modifier to the ability score and let the user know how much of the ability comes from the modifier\n
//!     \t Every we level the ability changes depending on the level and the modifier \n
//! (2) Design Description \n
//!     We have a fighter class that inherents from the Character class. \n
//!		The character class has two special static private variables that are being used in the different public methods in order to set or update.\n
//!	(3) Libraries used in this c++ program are the following:\n
//!		<vector>, <string>, <iostream>, <random>, <ctime>, <algorithm>, <windows.h>\ns


#pragma once
#ifndef Character_h
#define Character_h
#include <vector>
#include <string>
#include "../core/Subject.h"
#include "ItemContainer.h"
#include "Item.h"
//! Class that implements a character
class Character: public Subject
{
public:
	Character();
	Character(int, int, int, int, int, int);
	//hit points
	void hit(int);
	void setHitPoints();
	int getHitPoints();
	void resetHitPoints();
	//set modifier based on ability scores
	int modifier(int);
	//generate ability scores
	int genAbilityScores();
	void preGenAbilityScores();
	//leveling up
	void levelUp();
	int getLevel();
	void setLevel(int);
	//armor class
	void armor();
	int getArmor();
	//attack bonus
	void attackBonus();
	int getAttackBonus();
	void setAttackBonus(int);
	//attack damage
	void attackDamage();
	int getAttackDamage();
	void setAttackDamage(int);
	//load
	bool saveCharacter(std::string name);
	bool loadCharacter(std::string name);
	//update
	void update();
	//Item update
	void updateStatsAtEquip(Item);
	void updateStatsAtUnequip(Item);
	//print ability score
	void printAbilityScores();
	//unit testing validation
	bool validateNewCharacter();
	bool validateHitPoints();
	bool validateAttackBonus();
	//getter for ability score
	int getStrenght();
	int getDexterity();
	int getIntelligence();
	int getCharisma();
	int getWisdom();
	int getConstitution();
	//setter for ability scores
	void static setStrenght(int);
	void static setDexterity(int);
	void static setIntelligence(int);
	void static setCharisma(int);
	void static setWisdom(int);
	void static setConstitution(int);
	//getter for modifiers
	int getModStrenght();
	int getModDexterity();
	int getModIntelligence();
	int getModCharisma();
	int getModWisdom();
	int getModConstitution();
	//setter for modifiers
	//void setModStrength(int);
	//void setModDexterity(int);
	//void setModIntelligence(int);
	//void setModCharisma(int);
	//void setModWisdom(int);
	//void setModConstitution(int);

	void setName(std::string name);
	std::string getName();

private:
	static int abilityScores[6];
	static int modifiers[6];
	int currentHitPoints = 0;
	int equip[6];
	int lvl = 1;
    int armorPoints;
	int attackB;
	int attackD;
	Character *_subject;
	std::string name;


};

class Fighter : public Character
{
public:
	Fighter();
	Fighter(int, int, int, int, int, int);

};

inline void Character::setName(std::string name) {
    this->name = name;
}

inline std::string Character::getName() {
    return this->name;
}

#endif
