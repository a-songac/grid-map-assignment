#include "GamePlayController.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <list>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../utils/IOUtils.h"
#include "MapInteractionHelper.h"
#include "../entity/repo/MapRepository.h"
#include "../core/Repository.h"
#include "../utils/LogUtils.h"
#include "../controller/CharacterEditorController.h"
#include "../entity/Character.h"
#include "../entity/repo/CharacterRepository.h"
#include "../view/CharacterView.h"
#include "../controller/CharacterEditorController.h"
#include "../controller/ItemEditor.h"

using namespace std;


GamePlayController::GamePlayController(): level(1), map(nullptr) {}

void GamePlayController::newGame() {

    bool gameLoop = false;
    cout << "\n************* New Game *************" << endl << endl;

    do {

		this->selectMap();
        this->startGame();


    } while (gameLoop);

}

void GamePlayController::selectMap() {

    bool confirm = false;
    string filename, name1;
    vector<string>* mapReferences = MapRepository::instance()->listAll();

    if(mapReferences->size() > 0){

        do {
            cout << "Please select a map: " << endl;
            for (size_t i = 0; i < mapReferences->size(); i++) {
                cout << i+1 << ":" << mapReferences->at(i) << endl;
            }
            int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, mapReferences->size());

            this->map = MapRepository::instance()->getEntity(index-1);
            this->map->render();
            confirm = readYesNoInput("You confirm the selection of this map displayed above?[Y/n]: ", true);

        } while (!confirm);
    } else {
        cout << "Error could not load maps" << endl;
    }

}


void GamePlayController::startGame() {

	string goTo, itemNameEquip, itemNameUnequip;
	int input = 0;
	Character* character;

	character = CharacterEditorController::selectCharacter();


	// //////////////////////////////
	// TMEPORARY
	// ////////////////////////////////
    CharacterEditorController::initializeBackpack(character);
    // END TEMPORARY


    cout << endl << endl << "********** GET READY **********" << endl;
	cout << "The game is ready to be played, here are some advice before you start: " << endl;
	cout << "    - To move on the map, enter a location eg: a2" << endl;
	cout << "    - To view your back pack and equip yourself, type: 'bp'" << endl;
	cout << "    - To quit the game, type: 'q'" << endl;

    bool startGame = readYesNoInput("Ready to start the game?[Y/n]", 1);
    if (!startGame) {
        return;
    }

    if (nullptr != this->map) {

        bool gameOver = false;

        cout << "\n************* Start Game *************" << endl << endl;
        Coordinate entryDoor = this->map->getEntryDoorCoordinate();
        Coordinate exitDoor = this->map->getExitDoorCoordinate();
		Coordinate nextPosition;
		int col = exitDoor.column;
		int row = exitDoor.row;

        this->map->movePlayer(entryDoor.row, entryDoor.column);
			do {
				goTo = MapInteractionHelper::readMapLocationWhileInGame(this->map, "Go to [bp]: ", "bp");

				if (goTo == "bp") {
					do {
						cout << "1 - View backpack" << endl;
						cout << "2 - Equip item" << endl;
						cout << "3 - Unequip item" << endl;
						cout << "4 - View your worn items" << endl;
						cout << "5 - Exit" << endl;
						input = readIntegerInputWithRange("Your selection[1]: ", 1, 1, 5);

						if (input == 1)
						{
							character->displayBackpack();
						}
						else if (input == 2)
						{
							cout << "Enter the item name you wish to equip >> ";
							character->displayWornItems();
							cin >> itemNameEquip;
							character->equipItem(itemNameEquip);
							cout << "**WORNITEMS**" << endl;
							character->displayWornItems();
							cout << "**BACKPACKITEMS" << endl;
							character->displayBackpack();
							character->printAbilityScores();
						}
						else if (input == 3) {
							cout << "Enter the item name you wish to unequip >> ";
							cin >> itemNameUnequip;
						//	character->unEquipItem(itemNameUnequip);
							cout << "**WORNITEMS**" << endl;
							//character->wornItems->displayItem();
							cout << "**BACKPACKITEMS" << endl;
							//character->backpack->displayItem();

						}
						else if(input == 4){
							//character->wornItems->displayItem();
						}
					} while (input != 5);

					this->map->render();
				}
				else if (goTo == "q") {
                    gameOver = readYesNoInput("Do you really want to quit the game?[Y/n]", true);
				}
				else {
//					ch->display();
					character->printAbilityScores();
					nextPosition = MapInteractionHelper::convertToCoordinate(this->map, goTo);

					this->map->movePlayer(nextPosition.row, nextPosition.column);
					if (nextPosition.row == row && nextPosition.column == col)
					{
						cout << "you have reached the end of the map " << endl;

						cout << "You will now be returned to the main menu" << endl;
						character->levelUp();
						cout << "++++++++++++++++++++++++Level Up!++++++++++++++++++++++"<< endl;
						gameOver = true;
					}
				}
			} while (!gameOver);


    } else {
        logError("GamePlayController", "startGame", "No map was loaded for this game");
    }

}

