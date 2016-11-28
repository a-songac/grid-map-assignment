#include "DDMaster.h"

void DDMaster::setCharacterBuilder(CharacterBuilder* cb) {
	characterBuilder = cb;
}

Character* DDMaster::getCharacter() {
	return characterBuilder->getCharacter();
}

void DDMaster::constructCharacter() {
	characterBuilder->createCharacter();
	characterBuilder->buildFighter();
}
