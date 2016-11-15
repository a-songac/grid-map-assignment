#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

#include "../entity/repo/CharacterRepository.h"
#include "CharacterEditorController.h"
#include "../entity/Character.h"
#include "../view/CharacterView.h"
#include "../entity/ItemContainer.h"
#include "../utils/IOUtils.h"
#include "ItemEditor.h"
#include "../entity/repo/ItemRepository.h"

using namespace std;

const size_t CharacterEditorController::BACKPACK_INIT_SIZE = 2;

void CharacterEditorController::selectAction() {

    int abilityScore;
    bool exit;

	srand(static_cast<unsigned int>(time(0)));

    do {
        exit = false;
        cout << "\n\n******* Character Editor ********" << endl;
        cout << "1. Create character with randomly generated ability scores" << endl;
        cout << "2. Create character with standard d20 game ability scores" << endl;
        cout << "3. View existing characters" << endl;
        cout << "4. Exit" << endl;
        abilityScore = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 4);

        switch (abilityScore)
        {
            case 1:
                createCharacter(false);
                break;

            case 2:
                createCharacter(true);
                break;

            case 3:
                editExistingcharacter();
                break;

            case 4:
                exit = true;
        }
	} while (!exit);
}

void CharacterEditorController::createCharacter(bool pregenerated) {

    int level;

    Character* character = new Character();
	CharacterView* cView = new CharacterView(character);

    level = readIntegerInput("What level do you consider yourself?[1]: ", 1);
    cout << "*********************************" << endl;
    if (pregenerated) {
        cout << "Your ability scores are: " << endl;
        character->preGenAbilityScores();
    } else {
        cout << "generating your ability scores....." << endl;
            character->randomlyGenAbilityScores();
    }
    cout << "*********************************" << endl;

    character->setLevel(level);
    character->armor();
    character->attackBonus();
    character->damageBonus();
    character->levelUp();

    initializeBackpack(character);

    cout << "\nHere is your backpack: " << endl;
    character->displayBackpack();

    cout << endl << endl;

    saveCharacter(character);

}

void CharacterEditorController::initializeBackpack(Character* character) {

    cout << "\nIt is now time to add items to your character's backpack" << endl;
    cout << "You have the possibility to select 2 items.  If you want more, you'll have to earn new ones while playing the game!!!" << endl << endl;
    cout << "Here is the selection: " << endl;

    bool invalid;
    string choiceName;
    stringstream sStream;
    vector<string>* allItems = ItemRepository::instance()->listAll();


    for (size_t i = 0; i < min(BACKPACK_INIT_SIZE, allItems->size()); i++) {

        do {
            for (size_t j = 0; j < allItems->size(); j++) {
                cout << (j+1) << ". " << allItems->at(j) << endl;
            }

            invalid = false;
            sStream << "See details of item: ";
            choiceName = allItems->at(readIntegerInputWithRange(sStream.str(), 1, allItems->size()) - 1);
            cout << endl;
            ItemRepository::instance()->getEntity(choiceName)->displayItem();
            cout << endl;

            sStream.str("");
            sStream << "Confirm the selection of this item for your choice " << (i+1) << "?[Y/n] ";
            if (readYesNoInput(sStream.str(), true)) {
                if (character->hasItemInBackpack(choiceName)) {
                    invalid = true;
                    cout << "You already have this item, please choose another one" << endl;
                } else {
                    character->backpack->push_back(choiceName);
                }
            } else {
                invalid = true;
            }
            cout << endl;

            sStream.str("");
        } while (invalid);
    }

}


// TODO Currently only displays existing characters, need to add the possibility to modify them
void CharacterEditorController::editExistingcharacter() {

    Character* character;

    vector<string>* characterReferences = CharacterRepository::instance()->listAll();
    if (characterReferences->empty()) {
        cout << "No characters currently saved. Redirecting to editor menu." << endl;
    } else {
        cout << "Please select the character you want to load and view: "<< endl;
        for (size_t i = 0; i < characterReferences->size(); i++) {
            cout << (i+1) << ":" << characterReferences->at(i) << endl;
        }

        int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, characterReferences->size());
        character = CharacterRepository::instance()->getEntity(index-1);

        // TODO Display or no?
		// cv->display();

        if (nullptr == character) {
            cout << "Error, could not load chosen character" << endl;
        } else {
            // TODO What is thi for?
            character->levelUp();
        }
    }
}

void CharacterEditorController::saveCharacter(Character* character) {

    string name;

    if (readYesNoInput("Would you like to save your character?[Y/n]", 1))
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
    }
}














// /////////////////////
// USED IN GAMEPLAY CONTROLLER ONLLY
// /////////////////////

Character* CharacterEditorController::selectCharacter() {
	string name1;
	bool confirm1 = false;
	Character* character;
	srand(static_cast<unsigned int>(time(0)));
	vector<string>* characterReferences = CharacterRepository::instance()->listAll();

	do {
		if (characterReferences->empty()) {
			cout << "No characters currently saved. Redirecting to editor menu." << endl;
		}
		else {
			cout << "Please select the character you want to load and view: " << endl;
			for (size_t i = 0; i < characterReferences->size(); i++) {
				cout << (i + 1) << ":" << characterReferences->at(i) << endl;
			}

			int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, characterReferences->size());
			character = CharacterRepository::instance()->getEntity(index-1);
//			cv->display();
			character->levelUp();


			confirm1 = readYesNoInput("You confirm the selection of this character displayed above?[Y/n]: ", true);
			if (confirm1) {
				return character;
			}
			if (nullptr == character) {
				cout << "Error, could not load character " << name1 << endl;
				return nullptr;
			}
		}
	} while (!confirm1);
	return character;
}
