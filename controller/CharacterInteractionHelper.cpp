#include "CharacterInteractionHelper.h"

#include "../entity/repo/CharacterRepository.h"
#include "../utils/IOUtils.h"
#include "../entity/Cell.h"

#include <vector>

using namespace std;

Character* CharacterInteractionHelper::selectCharacter() {
	string name1;
	bool confirm1 = false;
	Character* character;
	vector<string>* characterReferences = CharacterRepository::instance()->listAll();

	do {
		if (characterReferences->empty()) {
			cout << "No characters currently saved. Redirecting to editor menu." << endl;
		}
		else {
			cout << "Please select the character you want to load and view: " << endl;
			for (size_t i = 0; i < characterReferences->size(); i++) {
				cout << (i + 1) << ". " << characterReferences->at(i) << endl;
			}

			int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, characterReferences->size());
			character = CharacterRepository::instance()->getEntity(index-1);

			if (nullptr == character) {

				cout << "Error, could not load character " << name1 << endl;
				return nullptr;

			} else {

                character->display();
                confirm1 = readYesNoInput("You confirm the selection of this character displayed above?[Y/n]: ", true);

			}
		}
	} while (!confirm1);
	return character;
}

std::string CharacterInteractionHelper::getStrategyName(char type) {
    switch (type) {
        case Cell::OCCUPANT_FRIEND:
            return "Friendly";
        case Cell::OCCUPANT_OPPONENT:
            return "Hostile";
    }
    return "";
}
