
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
#include "../service/Settings.h"

using namespace std;


GamePlayController::GamePlayController() : level(1), map(nullptr) {}

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

    // TODO Change: select character before, probably selecting it from the saved game
	Character* referenceCharacter;
	Character* gameCharacter;
	referenceCharacter = CharacterInteractionHelper::selectCharacter();
    // ////////////////////////







	string goTo, itemNameEquip, itemNameUnequip;
	int input = 0;
	bool quit = false;



	cout << endl << endl << "********** GAME READY TO BE PLAYED **********" << endl;

	bool startGame = readYesNoInput("Ready to start the game " + referenceCharacter->getName() + "?[Y/n]", 1);
	if (!startGame) {
		return;
	}

    SETTINGS::IN_GAME = true;
    map->setInGamePlayers();
    Coordinate entryDoor = this->map->getEntryDoorCoordinate();
	gameCharacter = new Character(referenceCharacter);
    Coordinate* userLocation = new Coordinate(entryDoor.row, entryDoor.column);
    GamePlayer userPlayer(gameCharacter->getName(), userLocation, Cell::OCCUPANT_PLAYER);
    userPlayer.setInGameCharacter(gameCharacter);
    map->setUserGamePlayer(&userPlayer);


    bool gameOver = false;

    cout << "\n************* Start Game *************" << endl << endl;


    vector<GamePlayer*>* gamePlayers = this->map->getGamePlayers();

    this->map->movePlayer(entryDoor.row, entryDoor.column);
    do {

        gameOver = userPlayer.turn(this->map);

        if (!gameOver) {
            for (size_t i = 0; i < gamePlayers->size(); i++) {
                gamePlayers->at(i)->turn(this->map);
            }
        }

    } while (!gameOver);



    // SAVING OF THE GAME, NOT ONLY THE CHARACTER, PLUS SAVE A COPY OF THE CHARACTER
    if (readYesNoInput("Would you like to save your character?[Y/n]", 1))
    {

        // TODO
    }


    // reset map to what it was


    SETTINGS::IN_GAME = false;
    map->unsetInGamePlayers();
    MapRepository::instance()->clearEntity(this->map->getName());
}
