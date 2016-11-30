#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

#include "../entity/repo/CharacterRepository.h"
#include "CharacterEditorController.h"
#include "CharacterInteractionHelper.h"
#include "../entity/Character.h"
#include "../view/CharacterView.h"
#include "../entity/ItemContainer.h"
#include "../utils/IOUtils.h"
#include "ItemEditor.h"
#include "../entity/repo/ItemRepository.h"
#include "CharacterInteractionHelper.h"
#include "../entity/BullycharacterBuilder.h"
#include "../entity/NimbleCharacterBuilder.h"
#include "../entity/TankCharacterBuilder.h"
#include "../entity/CharacterBuilder.h"
#include "../entity/DDMaster.h"
#include "ItemInteractionHelper.h"

using namespace std;

const size_t CharacterEditorController::BACKPACK_INIT_SIZE = 2;

void CharacterEditorController::selectAction() {

    int abilityScore;
    bool exit;

	srand(static_cast<unsigned int>(time(0)));

    do {
        exit = false;
        cout << "\n\n******* Character Editor ********" << endl;
        cout << "1. Create a new character" << endl;
        cout << "2. Edit existing characters" << endl;
        cout << "3. Exit" << endl;
        abilityScore = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 3);

        switch (abilityScore)
        {
            case 1:
                createCharacter();
                break;
            case 2:
				editExistingcharacter();
                break;
            case 3:
				exit = true;
        }
	} while (!exit);
}

void CharacterEditorController::createCharacter() {
	DDMaster ddMaster;
	CharacterBuilder* bullyCharacterBuilder;
	CharacterBuilder* nimbleCharacterBuilder;
	CharacterBuilder* tankCharacterBuilder;
    int lvl, fighter;
	cout << "\n\n******* Choose a Fighter ********" << endl;
	cout << "1. Bully" << endl;
	cout << "2. Nimble" << endl;
	cout << "3. Tank" << endl;
	fighter = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 3);
	switch (fighter)
	{
		case 1:
		{
			bullyCharacterBuilder = new BullyCharacterBuilder();
			ddMaster.setCharacterBuilder(bullyCharacterBuilder);
			ddMaster.constructCharacter();
			Character* bully = ddMaster.getCharacter();
			CharacterView* bView = new CharacterView(bully);
			initializeBackpack(bully);
			bully->display();
			cout << "\nHere is your backpack: " << endl;
			bully->displayBackpack();
			saveCharacter(bully);
			cout << endl << endl;
			break;
		}
		case 2:
		{
			nimbleCharacterBuilder = new NimbleCharacterBuilder();
			ddMaster.setCharacterBuilder(nimbleCharacterBuilder);
			ddMaster.constructCharacter();
			Character* nimble = ddMaster.getCharacter();
			CharacterView* nView = new CharacterView(nimble);
			initializeBackpack(nimble);
			nimble->display();
			cout << "\nHere is your backpack: " << endl;
			nimble->displayBackpack();
			cout << endl << endl;
			saveCharacter(nimble);
			break;
		}
		case 3:
		{
			tankCharacterBuilder = new TankCharacterBuilder();
			ddMaster.setCharacterBuilder(tankCharacterBuilder);
			ddMaster.constructCharacter();
			Character* tank = ddMaster.getCharacter();
			CharacterView* tView = new CharacterView(tank);
			initializeBackpack(tank);
			tank->display();
			cout << "\nHere is your backpack: " << endl;
			tank->displayBackpack();
			cout << endl << endl;
			saveCharacter(tank);
			break;
		}
	}

}

void CharacterEditorController::initializeBackpack(Character* character) {
	bool invalid;
	string choiceName;
	stringstream sStream;
	vector<string>* allItems = ItemRepository::instance()->listAll();

	if (character->backpack->size() >= 2)
	{
		cout << "the character already has 2 or more items inside of his backpack " << endl;
		for (int i = 0; i < character->backpack->size();i++) {


				cout << (i + 1) << ". " << character->backpack->at(i) << endl;
			}

	}
	else
	{

		cout << "\nIt is now time to add items to your character's backpack" << endl;
		cout << "You have the possibility to select 2 items.  If you want more, you'll have to earn new ones while playing the game!!!" << endl << endl;
		cout << "Here is the selection: " << endl;




		for (size_t i = 0; i < min(BACKPACK_INIT_SIZE, allItems->size()); i++) {

			do {
				for (size_t j = 0; j < allItems->size(); j++) {
					cout << (j + 1) << ". " << allItems->at(j) << endl;
				}

				invalid = false;
				sStream << "See details of item: ";
				choiceName = allItems->at(readIntegerInputWithRange(sStream.str(), 1, allItems->size()) - 1);
				cout << endl;
				ItemRepository::instance()->getEntity(choiceName)->displayItem();
				cout << endl;

				sStream.str("");
				sStream << "Confirm the selection of this item for your choice " << (i + 1) << "?[Y/n] ";
				if (readYesNoInput(sStream.str(), true)) {
					if (character->hasItemInBackpack(choiceName)) {
						invalid = true;
						cout << "You already have this item, please choose another one" << endl;
					}
					else {
						character->backpack->push_back(choiceName);
					}
				}
				else {
					invalid = true;
				}
				cout << endl;

				sStream.str("");
			} while (invalid);
		}

	}
}


// TODO Currently only displays existing characters, need to add the possibility to modify them
void CharacterEditorController::editExistingcharacter() {
	bool quit = false;
	string goTo;
	Item* chosenItem;
	int input;
	//TODO call a selectCharacter from CharacterInteractionHelper.cpp
	Character* character = CharacterInteractionHelper::selectCharacter();
	do {

		cout << "************* Menu *************" << endl << endl;
		cout << "1. View Character" << endl;
		cout << "2. View backpack" << endl;
		cout << "3. View worn items" << endl;
		cout << "4. Equip item" << endl;
		cout << "5. Unequip item" << endl;
		cout << "6. Save and Exit" << endl;
		cout << "7. Exit without saving" << endl;
		input = readIntegerInputWithRange("Your selection[1]: ", 1, 1, 7);
		switch (input) {
		case 1:
			character->printAbilityScores();
		case 2:
			character->displayBackpack();
			break;
		case 3:
			character->displayWornItems();
			break;
		case 4:
			chosenItem = ItemInteractionHelper::selectItemFromBackpack(character);
            if (nullptr != chosenItem) {
                character->equipItem(chosenItem->getName());
                character->displayWornItems();
                character->printAbilityScores();
            }
			break;
		case 5:
			if (nullptr != chosenItem) {
                character->unequipItem(chosenItem->getName());
                character->displayBackpack();
                character->printAbilityScores();
            }
            break;
		case 6:
            CharacterRepository::instance()->save(character->getName(), character);
            cout << "Changes successfully saved" << endl;
            quit = true;
            break;
		case 7:
			quit = readYesNoInput("Do you really want to leave without saving your changes?[Y/n]: ", true);
            if (quit) {
                CharacterRepository::instance()->clearEntity(character->getName());
            }
			break;
		}
	} while (!quit);
}

void CharacterEditorController::saveCharacter(Character* character) {

    string name;

    if (readYesNoInput("Would you like to save your character?[Y/n]: ", 1))
    {
        name = readFileName("please provide a name for the character: ");
        character->setName(name);
        if (CharacterRepository::instance()->save(name, character)) {
            cout << "Character successfully saved!" << endl;
        }
        else
        {
            cout << "ERROR, character could not be saved" << endl;
        }
    } else {
        delete character;
    }
}

