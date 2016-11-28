#include "BullycharacterBuilder.h"
#include "../utils/IOUtils.h"
#include <algorithm>

//! Implementation of a buildStrength method that sets the strength ability score and its modifier
void BullyCharacterBuilder::buildStrength(int str) {
	
	character->setStrength(str);
	int modStr = character->modifier(str);
	character->setModStrength(modStr);
}
//! Implementation of a buildConstitution method that sets the constitution ability score and its modifier
void BullyCharacterBuilder::buildConstitution(int consti) {

	character->setConstitution(consti);
	int modConsti = character->modifier(consti);
	character->setModConstitution(modConsti);
}
//! Implementation of a buildDexterity method that sets the dexterity ability score and its modifier
void BullyCharacterBuilder::buildDexterity(int dex) {

	character->setDexterity(dex);
	int modDex = character->modifier(dex);
	character->setModDexterity(modDex);
}
//! Implementation of a buildIntelligence method that sets the intelligence ability score and its modifier
void BullyCharacterBuilder::buildIntelligence(int intel) {

	character->setIntelligence(intel);
	int modIntel = character->modifier(intel);
	character->setModIntelligence(modIntel);
}
//! Implementation of a buildCharisma method that sets the charisma ability score and its modifier
void BullyCharacterBuilder::buildCharisma(int cha) {

	character->setCharisma(cha);
	int modChar = character->modifier(cha);
	character->setModCharisma(modChar);

}
//! Implementation of a buildWisdom method that sets the wisdom ability score and its modifier
void BullyCharacterBuilder::buildWisdom(int wis) {

	character->setWisdom(wis);
	int modWis = character->modifier(wis);
	character->setModWisdom(modWis);
}
//! Implementation of a buildHitPoints method that sets the Hit points to 10
void BullyCharacterBuilder::buildHitPoints() {

	character->setHitPoints(10);
}
//! Implementation of a buildLevel method that sets the level of the fighter to what he chooses
void BullyCharacterBuilder::buildLevel() {

	int level;
	level = readIntegerInput("Select a starting level[1]: ", 1);
	character->setLevel(level);
}
//! Implementation of a buildArmorClass method that sets the ac
void BullyCharacterBuilder::buildArmorClass() {

	character->armorClass();

}
//! Implementation of a buildAttackBonus method that sets the attackB
void BullyCharacterBuilder::buildAttackBonus() {

	character->attackBonus();
}
//! Implementation of a buildDamageBonus method that sets the strength damageB
void BullyCharacterBuilder::buildDamageBonus() {
	character->damageBonus();
}
//! Implementation of a buildFighter method that builds a complete fighter
void BullyCharacterBuilder::buildFighter() {

	buildLevel();
	std::vector<int> abilityScores;


	for (size_t i = 0; i < 6; i++)
	{
		abilityScores.push_back(character->genAbilityScores());
	}

	std::sort(abilityScores.begin(), abilityScores.end());
	buildStrength(abilityScores[5]);
	buildConstitution(abilityScores[4]);
	buildDexterity(abilityScores[3]);
	buildIntelligence(abilityScores[2]);
	buildCharisma(abilityScores[1]);
	buildWisdom(abilityScores[0]);
	buildArmorClass();
	buildAttackBonus();
	buildDamageBonus();

	buildHitPoints();
	

}