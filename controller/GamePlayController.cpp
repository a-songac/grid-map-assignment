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
#include "../entity/MapProxy.h"
#include "../entity/repo/MapRepository.h"
#include "../utils/LogUtils.h"
#include "../controller/CharacterEditorController.h"
#include "../entity/Character.h"
#include "../entity/CharacterProxy.h"
#include "../entity/repo/CharacterRepository.h"
#include "../view/CharacterView.h"
#include "../controller/CharacterEditorController.h"
#include "../controller/ItemEditor.h"

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
    vector<MapProxy*> mapProxies = *(MapRepository::instance()->listAll());

    if(mapProxies.size() > 0){

        do {
            cout << "Please select a map: " << endl;
            for (size_t i = 0; i < mapProxies.size(); i++) {
                cout << i+1 << ":" << mapProxies.at(i)->getFileName() << endl;
            }
            int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, mapProxies.size());

            this->map = mapProxies.at(index-1)->getMap();
            this->map->render();
            confirm = readYesNoInput("You confirm the selection of this map displayed above?[Y/n]: ", true);

        } while (!confirm);
    } else {
        cout << "Error could not load maps" << endl;
    }

}


void GamePlayController::startGame() {
	string load,goTo, itemNameEquip, itemNameUnequip;
	int input = 0;
	Character* cha = new Character();
	CharacterView* ch = new CharacterView(cha);
	CharacterEditorController* selectC = new CharacterEditorController();
	ItemEditor* itemToLoad = new ItemEditor();
	ItemContainer* backpack = new ItemContainer();
	ItemContainer* wornItem = new ItemContainer();

	cha = selectC->selectCharacter();

	cout << "Please enter the name of the file which contains your item " << endl;
	cin >> load;
	backpack = itemToLoad->loadFile(load);
	

    bool startGame = readYesNoInput("Ready to start the game?[Y/n]", 1);
    if (!startGame) {
        return;
    }
	
    if (nullptr != this->map) {
		
        bool gameOver = false;

        cout << "\n************* Start Game *************" << endl << endl;
        Coordinate entryDoor = this->map->getEntryDoorCoordinate();
        Coordinate nextPosition;
		
		Coordinate exitDoor = this->map->getExitDoorCoordinate();

		int col = exitDoor.column;
		int row = exitDoor.row;
        this->map->movePlayer(entryDoor.row, entryDoor.column);
			do {
				cout << "Go to [bp] >>";
				cin >> goTo;
				
				if (goTo == "bp") {
					do {
						cout << "1 - View backpack" << endl;
						cout << "2 = Equip item" << endl;
						cout << "3 - Unequip item" << endl;
						cout << "4 - Exit" << endl;
						cout << "Your selection[1]: ";
						cin >> input;

						if (input == 1) {
							backpack->displayItem();
						}
						else if (input == 2)
						{
							cout << "Enter the item name you wish to equip >> ";
							cin >> itemNameEquip;
							wornItem->equipItem(backpack, itemNameEquip);
							ch->display();
						}
						else if (input == 3) {
							cout << "Enter the item name you wish to unequip >> ";
							cin >> itemNameUnequip;
							wornItem->unequipItem(backpack, itemNameUnequip);
							ch->display();
						}
					} while (input != 4);
					ch->display();
					this->map->render();
				}
				else
				{
					ch->display();
					nextPosition = MapInteractionHelper::readMapLocation(this->map, goTo, "");
					this->map->movePlayer(nextPosition.row, nextPosition.column);
					if (nextPosition.row == row && nextPosition.column == col)
					{
						cout << "you have reached the end of the map " << endl;

						cout << "You will now be returned to the main menu" << endl;
						cha->levelUp();
						cout << "++++++++++++++++++++++++Level Up!++++++++++++++++++++++"<< endl;
						ch->display();
						break;
					}
				}
			} while (!gameOver);


    } else {
        logError("GamePlayController", "startGame", "No map was loaded for this game");
    }

}

