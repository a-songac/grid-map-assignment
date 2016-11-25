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
#include "CharacterInteractionHelper.h"
#include "MapInteractionHelper.h"
#include "../Combat.h"
#include "../entity/GamePlayer.h"

using namespace std;

GamePlayer *enemy = new GamePlayer;
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
	int input1 = 0;
	int input2 = 0;
	int input3 = 0;
	int input4 = 0;
	bool quit = false;
	Character* character;

	character = CharacterInteractionHelper::selectCharacter();


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
		if (enemy->getType() == 'o')
		{
			;
		}

        this->map->movePlayer(entryDoor.row, entryDoor.column);
			do {
				goTo = MapInteractionHelper::readMapLocationWhileInGame(this->map, "Go to [bp]: ", "bp");

				if (goTo == "bp") {
					do {
						cout << "************* Menu *************" << endl << endl;
						cout << "1 - View backpack" << endl;
						cout << "2 - View worn items" << endl;
						cout << "3 - Equip itemUnequip item" << endl;
						cout << "4 - Unequip item" << endl;
						cout << "5 - Exit" << endl;
						input = readIntegerInputWithRange("Your selection[1]: ", 1, 1, 5);

						switch (input) {
						case 1:
							character->displayBackpack();
							break;
						case 2:
							character->displayWornItems();
							break;
						case 3:
							itemNameEquip = readStringInputNoEmpty("Enter the item name with which you want to equip: ");
							character->equipItem(itemNameEquip);
							character->displayWornItems();
							character->printAbilityScores();
							break;
						case 4:
							itemNameUnequip = readStringInputNoEmpty("Enter the item name which you want to unequip: ");
							character->unequipItem(itemNameUnequip);
							character->displayBackpack();
							character->printAbilityScores();
							break;
						case 5:
							quit = true;
							break;
						}
					} while (!quit);

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
						if (character->getLevel() == 4 || character->getLevel() == 6 || character->getLevel() == 8 || character->getLevel() == 12 || character->getLevel() == 14 || character->getLevel() ==16 || character->getLevel() == 19 )
						{
							cout << "You have the possibility to increase your ability scores !! " << endl;
							cout << "Press 1 - to increase one ability score 2 " << endl;
							cout << "Press 2 - to increase two ability scores by 1" << endl;
							input1 = readIntegerInputWithRange("Your selection[1]: ", 1, 1, 2);

							switch (input1)
							{
							case 1:
								cout << "1-Strength" << endl;
								cout << "2-Dexterity" << endl;
								cout << "3-Intelligence " << endl;
								cout << "4-Charisma" << endl;
								cout << "5-Constitution" << endl;
								input2 = readIntegerInputWithRange("Your selection[1]: ", 1, 1, 5);
								switch (input2)
								{
									
								case 1:
									character->setStrength(character->getStrength() + 2);
									break;
								case 2:
									character->setDexterity(character->getDexterity() + 2);
									break;
								case 3:
									character->setIntelligence(character->getIntelligence() + 2);
									break;
								case 4:
									character->setCharisma(character->getCharisma() + 2);
									break;
								case 5:
									character->setConstitution(character->getConstitution() + 2);
									break;

								}break;

							case 2:
								int i = 0;
								
						
								while (i <=1 )
								{
									cout << "Please chose the first ability that you want to increase by 1 " << endl;
									cout << "1-Strength" << endl;
									cout << "2-Dexterity" << endl;
									cout << "3-Intelligence " << endl;
									cout << "4-Charisma" << endl;
									cout << "5-Constitution" << endl;
									input3 = readIntegerInputWithRange("Your selection[1]: ", 1, 1, 5);
									switch (input3)
									{
									case 1:
										character->setStrength(character->getStrength() + 1);
										i++;
										break;
									case 2:
										character->setDexterity(character->getDexterity() + 1);
										i++;
										break;
									case 3:
										character->setIntelligence(character->getIntelligence() + 1);
										i++;
										break;
									case 4:
										character->setCharisma(character->getCharisma() + 1);
										i++;
										break;
									case 5:
										character->setConstitution(character->getConstitution() + 1);
										i++;
										break;
									}
								}

								i = 0;
								break;

							}
							

						}
						else
						{
							true;
						}
						string name;

						if (readYesNoInput("Would you like to save your character?[Y/n]", 1))
						{
							name = readFileName("please provide a name for the character: ");

							if (CharacterRepository::instance()->save(name, character)) {
								cout << "Character successfully saved!" << endl;
							}
						}
						gameOver = true;
					}
				}
			} while (!gameOver);


    } else {
        logError("GamePlayController", "startGame", "No map was loaded for this game");
    }

}

