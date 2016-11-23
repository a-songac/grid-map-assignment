#include "UserPlayerStrategy.h"

#include "../entity/Cell.h"
#include "../entity/Character.h"
#include "../entity/GamePlayer.h"
#include "../entity/repo/MapRepository.h"
#include "../utils/IOUtils.h"
#include "../utils/LogUtils.h"
#include "../controller/MapInteractionHelper.h"
#include "../core/Repository.h"
#include "../controller/CharacterEditorController.h"
#include "../entity/repo/CharacterRepository.h"
#include "../view/CharacterView.h"
#include "../controller/CharacterEditorController.h"
#include "../controller/ItemEditor.h"
#include "../controller/CharacterInteractionHelper.h"
#include "../controller/MapInteractionHelper.h"


void UserPlayerStrategy::move(GamePlayer* player) {
}
void UserPlayerStrategy::attack(GamePlayer* player, GamePlayer* victim) {
}
void UserPlayerStrategy::freeAction(GamePlayer* player) {
}



bool UserPlayerStrategy::turn(GamePlayer* player, Map* map){

    bool quit = false;
    bool gameOver = false;
    Character* character = CharacterRepository::instance()->getEntity(player->getElementReference());
    string goTo, itemNameEquip, itemNameUnequip;
    int input;
    Coordinate exitDoor = map->getExitDoorCoordinate();
    Coordinate nextPosition;
    int col = exitDoor.column;
    int row = exitDoor.row;

    goTo = MapInteractionHelper::readMapLocationWhileInGame(map, "Go to [bp]: ", "bp");

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

        map->render();
    }
    else if (goTo == "q") {
        gameOver = readYesNoInput("Do you really want to quit the game?[Y/n]", true);
    }
    else {
//					ch->display();
        character->printAbilityScores();
        nextPosition = MapInteractionHelper::convertToCoordinate(map, goTo);

        map->movePlayer(nextPosition.row, nextPosition.column);

        // CHECL ALL ITEMS WERE COLLECTED
        if (nextPosition.row == row && nextPosition.column == col)
        {
            cout << "you have reached the end of the map " << endl;
            cout << "You will now be returned to the main menu" << endl;
            character->levelUp();
            cout << "++++++++++++++++++++++++Level Up!++++++++++++++++++++++"<< endl;
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


    return gameOver;
}
