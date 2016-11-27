#include "CharacterBuilder.h"

//! Implementation of a getCharacter method
//! @return Character*:: value of character
Character* CharacterBuilder::getCharacter() {
	return character;
}
//! implementation of a createCharacter method, that initializes a new character
void CharacterBuilder::createCharacter() {
	character = new Character();
}
 