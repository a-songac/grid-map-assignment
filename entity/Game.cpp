#include "Game.h"

using namespace std;

Game::Game(string name, Character* character, string campaignName, int currentMapIndex) : userCharacter(character), gameSaveName(name), campaignName(campaignName), currentMapIndex(currentMapIndex) {
}

Game::Game() {
}

Game::Game(Game* game) : userCharacter(game->getUserCharacter()), gameSaveName(game->getGameSaveName()), characterName(game->getCharacterName()), campaignName(game->getCampaignName()), currentMapIndex(game->getMapIndex()) {
}


