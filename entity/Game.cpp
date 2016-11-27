#include "Game.h"

using namespace std;

Game::Game(string name, Character* character) : userCharacter(character), gameSaveName(name) {
}

Game::Game() {
}

Game::Game(Game* game) : userCharacter(game->getUserCharacter()), gameSaveName(game->getGameSaveName()) {
}


