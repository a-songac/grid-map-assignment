#pragma once
#include "CharacterBuilder.h"
class DDMaster {

public: 
	void setCharacterBuilder(CharacterBuilder* cb);
	Character* getCharacter();
	void constructCharacter();
private:
	CharacterBuilder* characterBuilder;
};