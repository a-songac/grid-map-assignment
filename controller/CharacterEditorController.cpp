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

using namespace std;

void CharacterEditorController::createCharacter() {

    int abilityScore, level;

    Character *character = new Character();
	CharacterView *c = new CharacterView(character);
	srand(static_cast<unsigned int>(time(0)));
	bool answer;
	string name, name1;
	//driver
	cout << "******* Character Editor ********" << endl;
	level = readIntegerInput("What level do you consider yourself?[1]: ", 1);
	cout << "Press 1: Generate randomly your ability scores" << endl;
	cout << "Press 2: In relation with your race, pregenerated ability scores will be chosen" << endl;
	cout << "Press 3 : To load a character from a saved file" << endl;
	abilityScore = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 3);

	if (abilityScore == 1)
	{
		cout << "*********************************" << endl;
		cout << "generating your ability scores....." << endl;
		Character(character->genAbilityScores(), character->genAbilityScores(), character->genAbilityScores(),
			character->genAbilityScores(), character->genAbilityScores(), character->genAbilityScores());
	}
	else if (abilityScore == 2)
	{
		cout << "*********************************" << endl;
		cout << "Your ability scores are: " << endl;
		character->preGenAbilityScores();
		cout << "*********************************" << endl;
	}
	else if (abilityScore == 3)
	{
		name1 = readFileName("please enter the name of the file that you want to load: ");
		character->loadCharacter(name1 + ".txt");
		character->printAbilityScores();
	}

	character->setLevel(level);
	character->setHitPoints();
	character->armor();
	character->attackBonus();
	character->attackDamage();

	answer = readYesNoInput("Would you like to save your character?[Y/n]", 1);

	if (answer)
	{
		name = readFileName("please enter the name of the file you want to save: ");
		if (character->saveCharacter(name + ".txt")) {
            cout << "Character successfully saved!" << endl;
		} else {
            cout << "ERROR, character could not be saved" << endl;
		}
	}
}
