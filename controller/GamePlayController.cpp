#include "GamePlayController.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <list>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../entity/Character.h"
#include "../entity/GamePlayer.h"
#include "../entity/repo/MapRepository.h"
#include "../utils/IOUtils.h"
#include "../utils/LogUtils.h"
#include "MapInteractionHelper.h"
#include "../core/Repository.h"
#include "../controller/CharacterEditorController.h"
#include "../entity/repo/CharacterRepository.h"
#include "../view/CharacterView.h"
#include "../controller/CharacterEditorController.h"
#include "../controller/ItemEditor.h"
#include "CharacterInteractionHelper.h"
#include "MapInteractionHelper.h"

using namespace std;


GamePlayController::GamePlayController(): level(1), map(nullptr) {}

void GamePlayController::newGame() {

    bool gameLoop = false;
    cout << "\n************* New Game *************" << endl << endl;

    do {

		this->map = MapInteractionHelper::selectMap();
		if (nullptr == this->map) {
            return;
		}
        this->startGame();


    } while (gameLoop);

}


void GamePlayController::startGame() {

	string goTo, itemNameEquip, itemNameUnequip;
	int input = 0;
	bool quit = false;
	Character* character;

	character = CharacterInteractionHelper::selectCharacter();


    cout << endl << endl << "********** GET READY **********" << endl;
	cout << "The game is ready to be played, here are some advice before you start: " << endl;
	cout << "    - To move on the map, enter a location eg: a2" << endl;
	cout << "    - To view your back pack and equip yourself, type: 'bp'" << endl;
	cout << "    - To quit the game, type: 'q'" << endl;

    bool startGame = readYesNoInput("Ready to start the game " + character->getName() + "?[Y/n]", 1);
    if (!startGame) {
        return;
    }

    if (nullptr != this->map) {

        bool gameOver = false;

        cout << "\n************* Start Game *************" << endl << endl;
        Coordinate entryDoor = this->map->getEntryDoorCoordinate();


		vector<GamePlayer*>* gamePlayers = this->map->getGamePlayers();
		Coordinate* userLocation = new Coordinate(entryDoor.row, entryDoor.column);
		GamePlayer userPlayer(character->getName(), userLocation, Cell::OCCUPANT_PLAYER);

        this->map->movePlayer(entryDoor.row, entryDoor.column);
			do {

                gameOver = userPlayer.turn(this->map);

                if (!gameOver) {
                    for (size_t i = 0; i < gamePlayers->size(); i++) {
                        gamePlayers->at(i)->turn(this->map);
                    }
                }

			} while (!gameOver);

            // reset map to what it was
			MapRepository::instance()->clearEntity(this->map->getName());

    } else {
        logError("GamePlayController", "startGame", "No map was loaded for this game");
    }

}

