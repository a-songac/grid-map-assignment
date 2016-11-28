#include "GameRepository.h"
#include "../../utils/FileUtils.h"
#include"../../utils/LogUtils.h"
#include "../../entity_generator/MapGenerator.h"


using namespace std;

GameRepository* GameRepository::_instance;

GameRepository::GameRepository(): Repository<Game>("_game_references", "games"){
    loadEntity = &Repository<Game>::loadGame;
    persistEntity = &Repository<Game>::persistGame;
}

GameRepository* GameRepository::instance() {
    if (!_instance) {
        _instance = new GameRepository();
    }
    return _instance;
}



