#include "CharacterEditorController.h"
#include "../entity/Character.h"
#include "../view/CharacterView.h"
#include "../entity/ItemContainer.h"
#include "ItemEditor.h"
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <string>
#include "../utils/IOUtils.h"
#include "../entity/repo/CharacterRepository.h"
#include "../entity/CharacterProxy.h"

Character* character = new Character();
CharacterView* cv = new CharacterView(character);

void CharacterEditorController::createCharacter() {

	cv = new CharacterView(character);
    int abilityScore, level;
    bool viewLoaded = false;


	srand(static_cast<unsigned int>(time(0)));
	bool answer;
	string name, name1;
	//driver
	cout << "\n\n******* Character Editor ********" << endl;

	cout << "1. Create character with randomly generated ability scores" << endl;
	cout << "2. Create character with standard d20 game ability scores" << endl;
	cout << "3. View existing characters" << endl;
	abilityScore = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 3);

	if (abilityScore == 1)
	{
        level = readIntegerInput("What level do you consider yourself?[1]: ", 1);
		cout << "*********************************" << endl;
		cout << "generating your ability scores....." << endl;
		Character(character->genAbilityScores(), character->genAbilityScores(), character->genAbilityScores(),
        character->genAbilityScores(), character->genAbilityScores(), character->genAbilityScores());

	}
	else if (abilityScore == 2)
	{
        level = readIntegerInput("What level do you consider yourself?[1]: ", 1);
		cout << "*********************************" << endl;
		cout << "Your ability scores are: " << endl;
		character->preGenAbilityScores();
		cout << "*********************************" << endl;

	}
	else if (abilityScore == 3)
	{
        viewLoaded = true;

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
			cv->display();
            if (nullptr == character) {
                cout << "Error, could not load character " << name1 << endl;
            } else {
                character->printAbilityScores();
            }
        }


	};
	if (!viewLoaded) {
		character->setLevel(level);
        character->setHitPoints();
        character->armor();
        character->attackBonus();
        character->attackDamage();
		character->printAbilityScores();
            answer = readYesNoInput("Would you like to save your character?[Y/n]", 1);

        if (answer)
        {
            name = readFileName("please enter the name of the file you want to save: ");
            character->setName(name);
            if (CharacterRepository::instance()->save(name, character)) {
                cout << "Character successfully saved!" << endl;
            } else {
                cout << "ERROR, character could not be saved" << endl;
            }
        }
	}
}

Character* CharacterEditorController::selectCharacter() {
	string name1;
	bool confirm1 = false;

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
			cv->display();

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
