#include "CharacterBuilder.h"

Character* CharacterBuilder::getCharacter() {
	return character;
}

void CharacterBuilder::createCharacter() {

	character = new Character();
}
 