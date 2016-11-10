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
#include <random>
#include <ctime>
#include <algorithm>
//#include <windows.h>
#include <fstream>

using namespace std;

int modifiers[6];
int abilityScores[6];
int attackD;
int attackB;
int armorPoints;
int currentHitPoints = 0;
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

	setHitPoints();


}
void Character::updateStatsAtEquip(Item equipment) {

	vector<Enhancement> eVec = equipment.getInfluences();
		for (size_t i = 0; i < eVec.size(); i++) {

			if (eVec[i].getType() == "Strength")
				abilityScores[0] += eVec[i].getBonus();
			if (eVec[i].getType() == "Dexterity")
				abilityScores[1] += eVec[i].getBonus();
			if (eVec[i].getType() == "Intelligence")
				abilityScores[2] += eVec[i].getBonus();
			if (eVec[i].getType() == "Charisma")
				abilityScores[3] += eVec[i].getBonus();
			if (eVec[i].getType() == "Wisdom")
				abilityScores[4] += eVec[i].getBonus();
			if (eVec[i].getType() == "Constitution")
				abilityScores[5] += eVec[i].getBonus();
			if (eVec[i].getType() == "Armor")
				armorPoints += eVec[i].getBonus();
			if (eVec[i].getType() == "AtkBonus")
				attackB += eVec[i].getBonus();
			if (eVec[i].getType() == "AtkDamage")
				attackD += eVec[i].getBonus();

		}

		setHitPoints();
		this->notify();
}
void Character::updateStatsAtUnequip(Item equipment) {

	vector<Enhancement> eVec = equipment.getInfluences();
	for (size_t i = 0; i < eVec.size(); i++) {

		resetHitPoints();
		if (eVec[i].getType() == "Strength")
			abilityScores[0] -= eVec[i].getBonus();
		if (eVec[i].getType() == "Dexterity")
			abilityScores[1] -= eVec[i].getBonus();
		if (eVec[i].getType() == "Intelligence")
			abilityScores[2] -= eVec[i].getBonus();
		if (eVec[i].getType() == "Charisma")
			abilityScores[3] -= eVec[i].getBonus();
		if (eVec[i].getType() == "Wisdom")
			abilityScores[4] -= eVec[i].getBonus();
		if (eVec[i].getType() == "Constitution")
			abilityScores[5] -= eVec[i].getBonus();
		if (eVec[i].getType() == "Armor")
			armorPoints -= eVec[i].getBonus();
		if (eVec[i].getType() == "AtkBonus")
			attackB -= eVec[i].getBonus();
		if (eVec[i].getType() == "AtkDamage")
			attackD -= eVec[i].getBonus();

	}
	this->notify();


}
//! Implementation of Fighter Class. Inherites from the super class Character
Fighter::Fighter(int strength, int dexterity, int intelligence, int charisma, int wisdom, int constitution) :Character(strength * 2, dexterity * 2, intelligence, charisma, wisdom, constitution) {

}
Fighter::Fighter()
{

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

	for (int i = 0; i < 6; i++)
	{
		modifiers[i] = modifier(abilityScores[i] * lvl);
		abilityScores[i] = abilityScores[i] * lvl + modifiers[i];
	}

	setHitPoints();
	attackDamage();
	attackBonus();
	armor();
	notify();
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
	return lvl;
}
//! Implementation of generate randomly the ability scores
//! @return int:: value of the ability Score
int Character::genAbilityScores()
{

	int i = 0, j = 0, indexFound = 0, max = 0;
	int results[4] = { 0, 0, 0, 0 }, sortedResults[4] = { 0, 0, 0, 0 };

	//Roll each die
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
	Character(15, 14, 13, 12, 10, 8);
}
//implementation of a setter method for hit points
void Character::resetHitPoints() {
	currentHitPoints = currentHitPoints - modifiers[5] + lvl;
}
void Character::setHitPoints()
{
	//roll a d10 dice
	currentHitPoints = currentHitPoints + modifiers[5] + lvl;
	if (currentHitPoints < 10)
	{
		currentHitPoints = 10;
	}

}
//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}
//implementation of a setter method for armor
void Character::armor()
{
	armorPoints = modifiers[1];
}
//! Implementation of a getter method for armor
//! @return int: value of armorPoints
int Character::getArmor()
{
	return armorPoints;
}
//implementation of a setter method for attack bonus
void Character::attackBonus()
{
	attackB = lvl + modifiers[0] + modifiers[1];

}
//! Implementation of a getter method for attack bonus
//! @return int: value of attackB
int Character::getAttackBonus()
{
	return attackB;
}
//implementation of a setter method for attack damage
void Character::attackDamage()
{
	attackD = modifiers[0];

}
//! Implementation of a getter method for attack damage
//! @return int: value of attackD
int Character::getAttackDamage()
{
	return attackD;
}
//! Implementation of an equipment method, that enables the user to add equipment per category


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

	this->notify();
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
			<< attackD << endl
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
		f >> attackD;
		f >> attackB;
		f >> currentHitPoints;

		f.close();
		return true;
	}
	else
	{
		return false;
	}
}
void Character::update() {

}
//definition of getter for ability scores
int Character::getStrenght() {
	return abilityScores[0];
}
int Character::getDexterity() {
	return abilityScores[1];
}
int Character::getIntelligence() {
	return abilityScores[2];
}
int Character::getCharisma() {
	return abilityScores[3];
}
int Character::getWisdom() {
	return abilityScores[4];
}
int Character::getConstitution() {
	return abilityScores[5];
}
void  Character::setStrenght(int strenght) {
	abilityScores[0] = abilityScores[0] + strenght;
}
void  Character::setDexterity(int dexterity) {
	abilityScores[1] = abilityScores[1] + dexterity;
}
void  Character::setIntelligence(int intelligence) {
	abilityScores[0] = abilityScores[2] + intelligence;
}
void  Character::setCharisma(int charisma) {
	abilityScores[0] = abilityScores[3] + charisma;
}
void  Character::setWisdom(int wisdom) {
	abilityScores[0] = abilityScores[0] + wisdom;
}
void  Character::setConstitution(int constitution) {
	abilityScores[0] = abilityScores[0] + constitution;
}
//defintion of getter for modifiers
int Character::getModStrenght() {
	return  modifiers[0];
}
int Character::getModDexterity() {
	return  modifiers[1];
}
int Character::getModIntelligence() {
	return modifiers[2];
}
int Character::getModCharisma() {
	return  modifiers[3];
}
int Character::getModWisdom() {
	return  modifiers[4];
}
int Character::getModConstitution() {
	return  modifiers[5];
}
