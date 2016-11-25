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
#include "CombatService.h"
#include "LogSettings.h"

#include <sstream>

void UserPlayerStrategy::move(GamePlayer* player, Map* map) {
}
void UserPlayerStrategy::attack(GamePlayer* player, GamePlayer* victim) {
}
void UserPlayerStrategy::freeAction(GamePlayer* player) {
}



bool UserPlayerStrategy::turn(GamePlayer* player, Map* map){

    bool turnDone = true;
    bool quit = false;
    bool gameOver = false;
    Character* character = CharacterRepository::instance()->getEntity(player->getElementReference());
    string goTo;
    int input;
    Coordinate exitDoor = map->getExitDoorCoordinate();
    Coordinate nextPosition;
    int col = exitDoor.column;
    int row = exitDoor.row;
    stringstream stringStream;
    stringStream << "What you want to do next[i]?"
               << "\n    Enter map location to move"
               << "\n    Press 'a' for attack"
               << "\n    Press 'bp' for backpack"
               << "\n    Press 'i' to see game info"
               << "\n    Press 's' for settings"
               << "\n    Press 'q' to quit"
               << "\nYour choice[i]: ";
    do {

        turnDone = true;
        goTo = MapInteractionHelper::readMapLocationWhileInGame(map, stringStream.str(), "i");
        if (goTo == "bp") {
            turnDone = false;
            this->backpackOption(character);
            map->render();
        }
        else if (goTo == "q") {
            gameOver = readYesNoInput("Do you really want to quit the game?[Y/n]", true);
        }
        else if (goTo == "a") {

            turnDone = postAttack(character, map);
            map->render();

        }
        else if (goTo == "i") {
            turnDone = false;
            // TODO Display detailed info about the game
            map->render();

        }
        else if (goTo == "s") {
            turnDone = false;
            this->modifyGameLogSettings();
            map->render();
        }
        else {

            nextPosition = MapInteractionHelper::convertToCoordinate(map, goTo);
            turnDone = map->movePlayer(nextPosition.row, nextPosition.column);

            // CHECK ALL ITEMS WERE COLLECTED
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
    } while (!turnDone);


    return gameOver;
}



void UserPlayerStrategy::backpackOption(Character* character) {
    bool quit = false;
    string goTo, itemNameEquip, itemNameUnequip;
    int input;
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

}


bool UserPlayerStrategy::postAttack(Character* character, Map* map) {

    Coordinate userLocation = map->getPlayerPosition();
    Coordinate* enemyLocation;
    vector<GamePlayer*> directAttackable = vector<GamePlayer*>();
    vector<GamePlayer*> rangeAttackable = vector<GamePlayer*>();
    GamePlayer* player, victim;
    bool isDirectAttack;


    vector<GamePlayer*>* players = map->getGamePlayers();
    for (size_t i = 0; i < players->size(); i++) {
        player = players->at(i);
        enemyLocation = player->getLocation();
        if (CombatService::isAdjacent(userLocation, *enemyLocation)) {
            directAttackable.push_back(player);
        }
        else if (CombatService::canRangeAttack(userLocation, *enemyLocation, 2, map)) {
            rangeAttackable.push_back(player);
        }
    }
    int rangeSize = rangeAttackable.size();
    int directSize = directAttackable.size();
    if ((rangeSize + directSize) > 0) {

        cout << "Please select the character you want to attack: " << endl;
        string name;

        for (size_t i = 0; i < (directSize+rangeSize); i++) {
            if (i < directSize) {
                player = directAttackable.at(i);
            } else {
                player = rangeAttackable.at(i-directSize);
            }
            cout << (i + 1) << ". " << player->getElementReference() << " - " << player->getTypeName() << " - " << MapInteractionHelper::coordinateToString(*(player->getLocation()))  << endl;
        }
        int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, directSize+rangeSize);
        if (index <= directSize) {
            isDirectAttack = true;
            victim = directAttackable.at(index-1);
        } else {
            isDirectAttack = false;
            victim = rangeAttackable.at(index-1-directSize);
        }

        // PROCESS ATTACK



        return true;

    } else {
        cout << "No one to attack!" << endl;
        return false;
    }
}


string onOff(bool value) {
    if(value)
        return "ON";
    return "OFF";
}
void UserPlayerStrategy::modifyGameLogSettings() {
    bool done = false;
    do {
        cout << "Settings: " << endl
        << "1. Toggle Game Logs: " << onOff(LOG::GAME) << endl
        << "2. Toggle Map Log: " << onOff(LOG::MAP) << endl
        << "3. Toggle Dice Logs: " << onOff(LOG::DICE) << endl
        << "4. Toggle Character Logs: " << onOff(LOG::CHAR) << endl
        << "5. Exit" << endl;
        int choice = readIntegerInputWithRange("Your choice[5]: ", 5, 1, 5);

        switch (choice) {
            case 1:
                LOG::GAME = !LOG::GAME;
                break;
            case 2:
                LOG::MAP = !LOG::MAP;
                break;
            case 3:
                LOG::DICE = !LOG::DICE;
                break;
            case 4:
                LOG::CHAR = !LOG::CHAR;
                break;
            case 5:
                done = true;
        }
    }while (!done);

}
