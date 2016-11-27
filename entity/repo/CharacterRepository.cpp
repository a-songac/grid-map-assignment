
#include "CharacterRepository.h"
#include "../../utils/FileUtils.h"
#include"../../utils/LogUtils.h"


using namespace std;

CharacterRepository* CharacterRepository::_instance;

CharacterRepository::CharacterRepository(): Repository<Character>("_character_references", "characters") {
    loadEntity = &Repository<Character>::loadCharacter;
    persistEntity = &Repository<Character>::persistCharacter;
}


CharacterRepository* CharacterRepository::instance() {
    if (!_instance) {
        _instance = new CharacterRepository();
        if (_instance->listAll()->size() == 0) {
            // TODOL load preloaded characters if none
        }
    }
    return _instance;
}

