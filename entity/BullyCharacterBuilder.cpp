#include "BullycharacterBuilder.h"
#include <algorithm>
void BullyCharacterBuilder::buildStrength(int str) {
	
	character->setStrength(str);
	int modStr = character->modifier(str);
	character->setModStrength(modStr);
}

void BullyCharacterBuilder::buildConstitution(int consti) {

	character->setConstitution(consti);
	int modConsti = character->modifier(consti);
	character->setModConstitution(modConsti);
}

void BullyCharacterBuilder::buildDexterity(int dex) {

	character->setDexterity(dex);
	int modDex = character->modifier(dex);
	character->setModDexterity(modDex);
}

void BullyCharacterBuilder::buildIntelligence(int intel) {

	character->setIntelligence(intel);
	int modIntel = character->modifier(intel);
	character->setModIntelligence(modIntel);
}

void BullyCharacterBuilder::buildCharisma(int cha) {

	character->setCharisma(cha);
	int modChar = character->modifier(cha);
	character->setModCharisma(modChar);

}

void BullyCharacterBuilder::buildWisdom(int wis) {

	character->setWisdom(wis);
	int modWis = character->modifier(wis);
	character->setModWisdom(modWis);
}

void BullyCharacterBuilder::buildHitPoints() {

	character->setHitPoints(10);
}

void BullyCharacterBuilder::buildFighter() {

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
	buildHitPoints();

}