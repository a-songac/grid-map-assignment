#pragma once
#include "Character.h"

class CharacterBuilder {

public:
	Character* getCharacter();
	void createCharacter();
	virtual void buildStrength(int str) = 0;
	virtual void buildDexterity(int dex) = 0;
	virtual void buildConstitution(int consti) = 0;
	virtual void buildIntelligence(int intel) = 0;
	virtual void buildWisdom(int wis) = 0;
	virtual void buildCharisma(int wis) = 0;
	virtual void buildHitPoints() = 0;
	virtual void buildFighter() = 0;
	virtual void buildLevel() = 0;
protected:
	Character* character;




};