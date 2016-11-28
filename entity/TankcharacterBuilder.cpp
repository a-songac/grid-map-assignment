#include "TankcharacterBuilder.h"
#include <algorithm>
using namespace std;
void TankCharacterBuilder::buildStrength(int str) {

	character->setStrength(str);
	int modStr = character->modifier(str);
	character->setModStrength(modStr);
}

void TankCharacterBuilder::buildConstitution(int consti) {

	character->setConstitution(consti);
	int modConsti = character->modifier(consti);
	character->setModConstitution(modConsti);
}

void TankCharacterBuilder::buildDexterity(int dex) {

	character->setDexterity(dex);
	int modDex = character->modifier(dex);
	character->setModDexterity(modDex);
}

void TankCharacterBuilder::buildIntelligence(int intel) {

	character->setIntelligence(intel);
	int modIntel = character->modifier(intel);
	character->setModIntelligence(modIntel);
}

void TankCharacterBuilder::buildCharisma(int cha) {

	character->setCharisma(cha);
	int modChar = character->modifier(cha);
	character->setModCharisma(modChar);

}

void TankCharacterBuilder::buildWisdom(int wis) {

	character->setWisdom(wis);
	int modWis = character->modifier(wis);
	character->setModWisdom(modWis);
}

void TankCharacterBuilder::buildHitPoints() {

	character->setHitPoints(10);
}


void TankCharacterBuilder::buildFighter() {

	std::vector<int> abilityScores;

	for (size_t i = 0; i < 6; i++)
	{
		abilityScores.push_back(character->genAbilityScores());
	}
	std::sort(abilityScores.begin(), abilityScores.end());
	buildConstitution(abilityScores[5]);
	buildDexterity(abilityScores[4]);
	buildStrength(abilityScores[3]);
	buildIntelligence(abilityScores[2]);
	buildCharisma(abilityScores[1]);
	buildWisdom(abilityScores[0]);
	buildHitPoints();

}