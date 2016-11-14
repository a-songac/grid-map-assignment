//
//  Character.cpp
//  Character
//
//  Created by Hyjaz Loudin on 2016-10-15.
//  Copyright © 2016 Hyjaz Loudin. All rights reserved.
//

#include <iostream>
#include "Character.h"
#include "../core/Subject.h"
#include "../entity/Dice.h"
#include "../view/CharacterView.h"
#include <random>
#include <ctime>
#include <algorithm>
//#include <windows.h>
#include <fstream>

using namespace std;
using namespace d20Logic;

//! implementation of Character method that initializes strength, dexterity, intelligence, charisma, wisdom, constitution, whether it is generated randomly or not
//!  it is of type Character
Character::Character(int strength, int dexterity, int intelligence, int charisma, int wisdom, int constitution)
{

	//modifiers
	modifiers[0] = modifier(strength);
	modifiers[1] = modifier(dexterity);
	modifiers[2] = modifier(intelligence);
	modifiers[3] = modifier(charisma);
	modifiers[4] = modifier(wisdom);
	modifiers[5] = modifier(constitution);

	//ability scores
	abilityScores[0] = strength;
	abilityScores[1] = dexterity;
	abilityScores[2] = intelligence;
	abilityScores[3] = charisma;
	abilityScores[4] = wisdom;
	abilityScores[5] = constitution;

	currentHitPoints = 10;


}
void Character::updateStatsAtEquip(Item equipment) {

	vector<Enhancement> eVec = equipment.getInfluences();
		for (size_t i = 0; i < eVec.size(); i++) {

			if (eVec[i].getType() == "Strength")
			{
				this->setStrength(this->getStrength() + eVec[i].getBonus());
				this->setModStrength(modifier(this->getStrength()));
			}
			if (eVec[i].getType() == "Dexterity") 
			{
				this->setDexterity(this->getDexterity() + eVec[i].getBonus());
				this->setModDexterity(modifier(this->getDexterity()));
			}
			if (eVec[i].getType() == "Intelligence") 
			{
				this->setIntelligence(this->getIntelligence() + eVec[i].getBonus());
				this->setModIntelligence(modifier(this->getIntelligence()));
			}
			if (eVec[i].getType() == "Charisma") 
			{
				this->setCharisma(this->getCharisma() + eVec[i].getBonus());
				this->setModCharisma(modifier(this->getCharisma()));
			}
			if (eVec[i].getType() == "Wisdom")
			{
				this->setWisdom(this->getWisdom() + eVec[i].getBonus());
				this->setModWisdom(modifier(this->getWisdom()));
			}
			if (eVec[i].getType() == "Constitution")
			{
				this->setConstitution(this->getConstitution() + eVec[i].getBonus());
				this->setModConstitution(modifier(this->getConstitution()));
			}
			if (eVec[i].getType() == "Armor")
				this->armorPoints += eVec[i].getBonus();
			if (eVec[i].getType() == "AtkBonus")
				this->attackB += eVec[i].getBonus();
			if (eVec[i].getType() == "AtkDamage")
				this->damageB += eVec[i].getBonus();
		}
		this->hitPoints();

}
void Character::updateStatsAtUnequip(Item equipment) {

	vector<Enhancement> eVec = equipment.getInfluences();
	for (size_t i = 0; i < eVec.size(); i++) {
		if (eVec[i].getType() == "Strength") 
		{
			this->setStrength(this->getStrength() - eVec[i].getBonus());
			this->setModStrength(modifier(this->getStrength()));
		}
		if (eVec[i].getType() == "Dexterity")
		{
			this->setDexterity(this->getStrength() - eVec[i].getBonus());
			this->setModDexterity(modifier(this->getDexterity()));
		}
		if (eVec[i].getType() == "Intelligence")
		{
			this->setIntelligence(this->getIntelligence() - eVec[i].getBonus());
			this->setModIntelligence(modifier(this->getIntelligence()));
		}
		if (eVec[i].getType() == "Charisma")
		{
			this->setCharisma(this->getCharisma() - eVec[i].getBonus());
			this->setModCharisma(modifier(this->getCharisma()));
		}
		if (eVec[i].getType() == "Wisdom")
		{
			this->setWisdom(this->getWisdom() - eVec[i].getBonus());
			this->setModWisdom(modifier(this->getWisdom()));
		}
		if (eVec[i].getType() == "Constitution")
		{
			this->setConstitution(this->getConstitution() - eVec[i].getBonus());
			this->setModConstitution(modifier(this->getConstitution()));
		}
		if (eVec[i].getType() == "Armor")
			this->armorPoints -= eVec[i].getBonus();
		if (eVec[i].getType() == "AtkBonus")
			this->attackB -= eVec[i].getBonus();
		if (eVec[i].getType() == "AtkDamage")
			this->damageB -= eVec[i].getBonus();
	}
	this->resetHitPoints();

}
//! Implementation of a modifier method, that calculates the modifier of each ability
//! @return int:: value of modifier
int Character::modifier(int abilityScore)
{
	int mod = (int)floor((abilityScore - 10) / 2);
	if (mod < 0) {
		return 0;
	}
	return mod;
}
//! Implementation of a levelUp method, at the same time updates everything else depending on the level
void Character::levelUp()
{
	this->lvl++;
	this->attackB++;
	Notify();


}
//! implementation of setLevel that initializes the level at the beginning of the game depending on what the user provides.
void Character::setLevel(int level)
{
	this->lvl = level;

}
//! Implementation of a getter method for level
//! @return int: value of lvl
int Character::getLevel()
{
	return this->lvl;
}
//! Implementation of generate randomly the ability scores
//! @return int:: value of the ability Score
int Character::genAbilityScores()
{

	int i = 0, j = 0, indexFound = 0, max = 0;
	int results[4] = { 0, 0, 0, 0 }, sortedResults[4] = { 0, 0, 0, 0 };

	//Roll each die+1
	for (i = 0; i<4; ++i) {
		results[i] = (rand() % 6) + 1;
	}

	//Sort the results
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; ++j)
		{
			if (results[j] > max) {
				max = results[j];
				indexFound = j;
			}
		}

		results[indexFound] = 0;
		sortedResults[i] = max;
		max = 0;
	}

	//Add first 3 elements
	int sumOfDice = sortedResults[0] + sortedResults[1] + sortedResults[2];

	return sumOfDice;
}
//! Implementation of pre-generated ability scores
void Character::preGenAbilityScores()
{
	//pre generated numbers
	abilityScores[0] = 15;
	abilityScores[1] = 14;
	abilityScores[2] = 13;
	abilityScores[3] = 12;
	abilityScores[4] = 10;
	abilityScores[5] = 8;
	//modifiers
	modifiers[0] = modifier(abilityScores[0]);
	modifiers[1] = modifier(abilityScores[1]);
	modifiers[2] = modifier(abilityScores[2]);
	modifiers[3] = modifier(abilityScores[3]);
	modifiers[4] = modifier(abilityScores[4]);
	modifiers[5] = modifier(abilityScores[5]);

	currentHitPoints = 10;

}

void Character::randomlyGenAbilityScores() {

	//ability scores
	abilityScores[0] = genAbilityScores();
	abilityScores[1] = genAbilityScores();
	abilityScores[2] = genAbilityScores();
	abilityScores[3] = genAbilityScores();
	abilityScores[4] = genAbilityScores();
	abilityScores[5] = genAbilityScores();
	//modifiers
	modifiers[0] = modifier(abilityScores[0]);
	modifiers[1] = modifier(abilityScores[1]);
	modifiers[2] = modifier(abilityScores[2]);
	modifiers[3] = modifier(abilityScores[3]);
	modifiers[4] = modifier(abilityScores[4]);
	modifiers[5] = modifier(abilityScores[5]);

	currentHitPoints = 10;

}
//implementation of a setter method for hit points
void Character::resetHitPoints() {
	this->currentHitPoints = this->currentHitPoints - this->getModConstitution();
}
void Character::hitPoints()
{
	Dice d;
	int d10 = d.roll_d10();
	//roll a d10 dice
	this->currentHitPoints = this->currentHitPoints + this->getModConstitution() + d10;
}
//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return this->currentHitPoints;
}
//implementation of a setter method for armor
void Character::armor()
{
	this->armorPoints = this->getModDexterity();
}
//! Implementation of a getter method for armor
//! @return int: value of armorPoints
int Character::getArmor()
{
	return this->armorPoints;
}
//implementation of a setter method for attack bonus
void Character::attackBonus()
{
	//depends on the weapon of choice
	this->attackB = this->lvl + modifiers[0] + modifiers[1];

}
//! Implementation of a getter method for attack bonus
//! @return int: value of attackB
int Character::getAttackBonus()
{
	return this->attackB;
}
//! implementation of a setter method for attack damage
void Character::damageBonus()
{
	this->damageB = this->modifiers[0];

}
//! Implementation of a getter method for attack damage
//! @return int: value of attackD
int Character::getDamageBonus()
{
	return this->damageB;
}
//! Implementation of the verification of a newly created Character
//! @return bool value, true of the character is valid (stats should be in the 3-18 range for a new character), false if invalid.
bool Character::validateNewCharacter()
{
	for (int i = 0; i <= 5; i++)
		if (abilityScores[i]<3 || abilityScores[i]>18)
			return false;
	return true;
}
//! Implementation of the verification of the current hit points
//! @return bool value, true if the current hit points = constituion modifier + lvl
bool Character::validateHitPoints()
{
	if (currentHitPoints != (modifiers[4] + lvl))
		return false;
	return true;
}

//! Implementation of the verification of the attack bonus
//! @return bool value, true if the attack bonus = lvl + strenghtModifier + dexterityModifier
bool Character::validateAttackBonus()
{
	if (attackB != (lvl + modifiers[0] + modifiers[1]))
		return false;
	return true;

}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param damage: damage sustained by the charactere
void Character::hit(int damage)
{
	currentHitPoints = currentHitPoints - damage;
}
Character::Character()
{

}
void Character::printAbilityScores() {

	Notify();
}
bool Character::saveCharacter(string name)
{
	std::ofstream f(name, std::ios::out);

	if (f.is_open())
	{


			f << lvl << endl
			<< abilityScores[0] << endl
			<< abilityScores[1] << endl
			<< abilityScores[2] << endl
			<< abilityScores[3] << endl
			<< abilityScores[4] << endl
			<< abilityScores[5] << endl
			<< modifiers[0] << endl
			<< modifiers[1] << endl
			<< modifiers[2] << endl
			<< modifiers[3] << endl
			<< modifiers[4] << endl
			<< modifiers[5] << endl
			<< armorPoints << endl
			<< damageB << endl
			<< attackB << endl
			<< currentHitPoints << endl;


		f.close();
		return true;
	}
	else
	{
		return false;
	}
}

// Load a Character from file
bool Character::loadCharacter(string name1)
{
	std::ifstream f(name1, std::ios::in);

	if (f.is_open())
	{
		f >> lvl;
		f >> abilityScores[0];
		f >> abilityScores[1];
		f >> abilityScores[2];
		f >> abilityScores[3];
		f >> abilityScores[4];
		f >> abilityScores[5];
		f >> modifiers[0];
		f >> modifiers[1];
		f >> modifiers[2];
		f >> modifiers[3];
		f >> modifiers[4];
		f >> modifiers[5];
		f >> armorPoints;
		f >> damageB;
		f >> attackB;
		f >> currentHitPoints;

		f.close();
		Notify();
		return true;
	}
	else
	{
		return false;
	}
}
void Character::update() {

}
void Character::equipItem(string itemName)
{
	vector<Item> iVec = this->backpack->getItems();

	for (size_t i = 0; i < iVec.size(); i++) {
		string name = iVec[i].getName();
		if (checkIfItemExists(itemName, name))
		{
			if (ItemContainer::validateContainer()) 
			{
				this->items.push_back(iVec[i]);
				this->wornItems->addItemToWornItems(iVec[i]);
				this->updateStatsAtEquip(iVec[i]);
				cout << "you are now equipped with: " << iVec[i].getName() << endl;
				cout << "your worn Items are: " << endl;
				this->backpack->removeItemFromBackpack(iVec[i]);
				break;
			}
		}
		else 
		{
			cout << "You cannot equip Item: " << iVec[i].getName() << endl;
		}

	}
}
void Character::unEquipItem(string name) {
	vector<Item> iVec = this->wornItems->getItems();
	for (size_t i = 0; i < iVec.size(); ++i)
	{
		if (checkIfItemExists(iVec[i].getName(), name))
		{
			this->items.erase(items.begin() + i);
			cout << "Item: " << iVec[i].getName() << " has been successfully unequipped" << endl;
			this->backpack->addItemToBackpack(iVec[i]);
			this->updateStatsAtUnequip(iVec[i]);
		}
		else {
			if (i + 1 == items.size()) {
				cout << "Item: " << iVec[i].getName() << " is not available" << endl;
			}
		}
	}
}
bool Character::checkIfItemExists(string wearItem, string name) {

	if (wearItem == name) 
	{
		return true;
	}
	return false;

}
void Character::backpackContainer(string backpackItem) {
	this->backpack = this->item->loadFile(backpackItem);
}

//ability scores
void Character::setStrength(int stre) {
	this->abilityScores[0] = stre;
}
int Character::getStrength() {
	return this->abilityScores[0];
}
void Character::setDexterity(int dex){
	this->abilityScores[1] = dex;
}
int Character::getDexterity() {
	return this->abilityScores[1];
} 
void Character::setIntelligence(int intel) {
	this->abilityScores[2] = intel;
}
int Character::getIntelligence() {
	return this->abilityScores[2];
}
void Character::setWisdom(int wis) {
	this->abilityScores[3] = wis;
}
int Character::getWisdom() {
	return this->abilityScores[3];
}
void Character::setCharisma(int cha) {
	this->abilityScores[4] = cha;
}
int Character::getCharisma() {
	return this->abilityScores[4];
}
void Character::setConstitution(int cons) {
	this->abilityScores[5] = cons;
}
int Character::getConstitution() {
	return this->abilityScores[5];
}
//modifier
void Character::setModStrength(int modStr) {
	this->modifiers[0] = modStr;
}
int Character::getModStrength() {
	return this->modifiers[0];
}
void Character::setModDexterity(int modDex) {
	this->modifiers[1] = modDex;
}
int Character::getModDexterity() {
	return this->modifiers[1];
}
void Character::setModIntelligence(int modIntel) {
	this->modifiers[2] = modIntel;
}
int Character::getModIntelligence() {
	return this->modifiers[2];
}
void Character::setModCharisma(int modCha) {
	this->modifiers[3] = modCha;
}
int Character::getModCharisma() {
	return this->modifiers[3];
}
void Character::setModWisdom(int modWis) {
	this->modifiers[4] = modWis;
}
int Character::getModWisdom() {
	return this->modifiers[4];
}
void Character::setModConstitution(int modCons) {
	this->modifiers[5] = modCons;
}
int Character::getModConstitution() {
	return this->modifiers[5];
}

//! Implementation of Fighter Class. Inherites from the super class Character
Fighter::Fighter(int strength, int dexterity, int intelligence, int charisma, int wisdom, int constitution) :Character(strength * 2, dexterity * 2, intelligence, charisma, wisdom, constitution) {

}
Fighter::Fighter()
{

}
Character::~Character() {

}
