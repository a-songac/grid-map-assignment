#include "NimblecharacterBuilder.h"
#include <algorithm>
using namespace std;
void NimbleCharacterBuilder::buildStrength(int str) {

	character->setStrength(str);
	int modStr = character->modifier(str);
	character->setModStrength(modStr);
}

void NimbleCharacterBuilder::buildConstitution(int consti) {

	character->setConstitution(consti);
	int modConsti = character->modifier(consti);
	character->setModConstitution(modConsti);
}

void NimbleCharacterBuilder::buildDexterity(int dex) {

	character->setDexterity(dex);
	int modDex = character->modifier(dex);
	character->setModDexterity(modDex);
}

void NimbleCharacterBuilder::buildIntelligence(int intel) {

	character->setIntelligence(intel);
	int modIntel = character->modifier(intel);
	character->setModIntelligence(modIntel);
}

void NimbleCharacterBuilder::buildCharisma(int cha) {

	character->setCharisma(cha);
	int modChar = character->modifier(cha);
	character->setModCharisma(modChar);

}

void NimbleCharacterBuilder::buildWisdom(int wis) {

	character->setWisdom(wis);
	int modWis = character->modifier(wis);
	character->setModWisdom(modWis);
}

void NimbleCharacterBuilder::buildHitPoints() {

	character->setHitPoints(10);
}


void NimbleCharacterBuilder::buildFighter() {

	std::vector<int> abilityScores;

	for (size_t i = 0; i < 6; i++)
	{
		abilityScores.push_back(character->genAbilityScores());
	}
	std::sort(abilityScores.begin(), abilityScores.end());
	buildDexterity(abilityScores[5]);
	buildConstitution(abilityScores[4]);
	buildStrength(abilityScores[3]);
	buildIntelligence(abilityScores[2]);
	buildCharisma(abilityScores[1]);
	buildWisdom(abilityScores[0]);
	buildHitPoints();
	
}