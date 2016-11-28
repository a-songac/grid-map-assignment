#include "TankcharacterBuilder.h"
#include "../utils/IOUtils.h"
#include <algorithm>
using namespace std;

//! Implementation of a buildStrength method that sets the strength ability score and its modifier
void TankCharacterBuilder::buildStrength(int str) {

	character->setStrength(str);
	int modStr = character->modifier(str);
	character->setModStrength(modStr);
}
//! Implementation of a buildConstitution method that sets the constitution ability score and its modifier
void TankCharacterBuilder::buildConstitution(int consti) {

	character->setConstitution(consti);
	int modConsti = character->modifier(consti);
	character->setModConstitution(modConsti);
}
//! Implementation of a buildDexterity method that sets the dexterity ability score and its modifier
void TankCharacterBuilder::buildDexterity(int dex) {

	character->setDexterity(dex);
	int modDex = character->modifier(dex);
	character->setModDexterity(modDex);
}
//! Implementation of a buildIntelligence method that sets the intelligence ability score and its modifier
void TankCharacterBuilder::buildIntelligence(int intel) {

	character->setIntelligence(intel);
	int modIntel = character->modifier(intel);
	character->setModIntelligence(modIntel);
}
//! Implementation of a buildCharisma method that sets the charisma ability score and its modifier
void TankCharacterBuilder::buildCharisma(int cha) {

	character->setCharisma(cha);
	int modChar = character->modifier(cha);
	character->setModCharisma(modChar);

}
//! Implementation of a buildWisdom method that sets the wisdom ability score and its modifier
void TankCharacterBuilder::buildWisdom(int wis) {

	character->setWisdom(wis);
	int modWis = character->modifier(wis);
	character->setModWisdom(modWis);
}
//! Implementation of a buildHitPoints method that sets the Hit points to 10
void TankCharacterBuilder::buildHitPoints() {

	character->setHitPoints(10);
}
//! Implementation of a buildArmorClass method that sets the ac
void TankCharacterBuilder::buildArmorClass() {

	character->armorClass();

}
//! Implementation of a buildAttackBonus method that sets the attackB
void TankCharacterBuilder::buildAttackBonus() {

	character->attackBonus();
}
//! Implementation of a buildDamageBonus method that sets the strength damageB
void TankCharacterBuilder::buildDamageBonus() {
	character->damageBonus();
}
//! Implementation of a buildLevel method that sets the level of the fighter to what he chooses
void TankCharacterBuilder::buildLevel() {
	int level;
	level = readIntegerInput("Select a starting level[1]: ", 1);
	character->setLevel(level);
}
//! Implementation of a buildFighter method that builds a complete fighter
void TankCharacterBuilder::buildFighter() {

<<<<<<< HEAD
	buildLevel();
	std::vector<int> abilityScores;
=======
	std::vector<int> newAbilityScores;
>>>>>>> ability score generation method completed for various type of fighter

	for (size_t i = 0; i < 6; i++)
	{
		newAbilityScores.push_back(character->genAbilityScores());
	}
<<<<<<< HEAD
	std::sort(abilityScores.begin(), abilityScores.end());
	buildConstitution(abilityScores[5]);
	buildDexterity(abilityScores[4]);
	buildStrength(abilityScores[3]);
	buildIntelligence(abilityScores[2]);
	buildCharisma(abilityScores[1]);
	buildWisdom(abilityScores[0]);
	buildArmorClass();
	buildAttackBonus();
	buildDamageBonus();
=======
	std::sort(newAbilityScores.begin(), newAbilityScores.end());
	buildConstitution(newAbilityScores[5]);
	buildDexterity(newAbilityScores[4]);
	buildStrength(newAbilityScores[3]);
	buildIntelligence(newAbilityScores[2]);
	buildCharisma(newAbilityScores[1]);
	buildWisdom(newAbilityScores[0]);
>>>>>>> ability score generation method completed for various type of fighter
	buildHitPoints();

}