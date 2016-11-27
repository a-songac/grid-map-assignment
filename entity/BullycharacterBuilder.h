#pragma once

#include "CharacterBuilder.h"

class BullyCharacterBuilder : public CharacterBuilder {

public:
	virtual void buildStrength(int str);
	virtual void buildDexterity(int dex);
	virtual void buildConstitution(int consti);
	virtual void buildIntelligence(int intel);
	virtual void buildWisdom(int wis);
	virtual void buildCharisma(int wis);
	virtual void buildHitPoints();
	virtual void buildFighter();
	virtual void buildLevel();
	virtual void buildArmorClass();
	virtual void buildAttackBonus();
	virtual void buildDamageBonus();
};