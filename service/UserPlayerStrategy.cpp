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
#include "Settings.h"

#include <sstream>

using namespace std;

void UserPlayerStrategy::move(GamePlayer* player, Map* map) {
}
void UserPlayerStrategy::attack(GamePlayer* player, GamePlayer* victim, bool melee) {

    CombatService::attack(
            player->getInGameCharacter(),
            victim->getInGameCharacter(),
            melee);

}
void UserPlayerStrategy::freeAction(GamePlayer* player) {
}



bool UserPlayerStrategy::turn(GamePlayer* player, Map* map) {

    bool turnDone = true;
    bool quit = false;
    bool gameOver = false;
    Character* character = player->getInGameCharacter();
    string goTo;
    Coordinate exitDoor = map->getExitDoorCoordinate();
    Coordinate nextPosition;
    int col = exitDoor.column;
    int row = exitDoor.row;
    stringstream stringStream;
    stringStream << "What you want to do next[i]?"
               << "\nTURN ACTION"
               << "\n    - Enter map location to move"
               << "\n    - Press 'a' for attack"
               << "\n    - Press 'f' for free action"
               << "\nNON-TURN ACTION"
               << "\n    - Press 'bp' for backpack"
//               << "\n    - Press 'i' to see game info"
               << "\n    - Press 's' for settings"
               << "\n    - Press 'q' to quit"
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
            if (character->getHitPoints() <= 0) {
                gameOver = true;
            }
            map->render();

        }
        else if (goTo == "i") {
            turnDone = false;
            // TODO Display detailed info about the game
            map->render();

        }
        else if (goTo == "s") {
            turnDone = false;
            this->modifyGameSettings();
            map->render();
        }
        else if (goTo == "f") {
            turnDone = true;
            map->render();
        }
        else {

            nextPosition = MapInteractionHelper::convertToCoordinate(map, goTo);
            turnDone = map->movePlayer(nextPosition.row, nextPosition.column);


            // CHECK ALL ITEMS WERE COLLECTED
            if(turnDone!=false){
               if (nextPosition.row == row && nextPosition.column == col
                    && readYesNoInput("You have reached the exit door, do you want to finish the map?[Y/n] ", true))
               {
                    character->levelUp();
                    cout << "++++++++++++++++++++++++Level Up!++++++++++++++++++++++"<< endl;
                    string name;

                    endGameLevelUp(character);

                    gameOver = true;

               } else if (map->getOccupant(nextPosition.row, nextPosition.column) == Cell::OCCUPANT_CHEST) {

                    GameItem* gameItem;
                    for (size_t i = 0; i < map->getGameItems()->size(); i++) {
                        gameItem = map->getGameItems()->at(i);
                        if (*(gameItem->getLocation()) == nextPosition) {
                            //character->lootItem(gameItem);
                            break;
                        }
                    }

               }
            }
            else{
                map->render();
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
        cout << "3 - Equip item" << endl;
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
    GamePlayer* player;
    GamePlayer* victim;
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


        this->attack(map->getUserGamePlayer(), victim, isDirectAttack);
        cout << "After attack, victim ends up with " << victim->getInGameCharacter()->getHitPoints() << " HP." << endl;
        readStringInput("Press any key to continue...", "");
        if (victim->getType() == Cell::OCCUPANT_FRIEND) {
            victim->makeHostile();
            map->fillCell(
                    victim->getLocation()->row,
                    victim->getLocation()->column,
                    Cell::OCCUPANT_OPPONENT);
        }
        if (character->getHitPoints() <= 0) {
            return true;
        }
        if (victim->getInGameCharacter()->getHitPoints() <= 0) {
            // character->lootItems(victim);
        }

        CombatService::eliminateDeadBodies(map);

        return true;

    } else {
        cout << "No one to attack! Please perform another turn action" << endl;
        readStringInputNoEmpty("Press any key to continue");
        return false;
    }
}


string onOff(bool value) {
    if(value)
        return "ON";
    return "OFF";
}
void UserPlayerStrategy::modifyGameSettings() {
    bool done = false;
    do {
        cout << "Settings: " << endl
        << "1. Toggle Game Logs: " << onOff(SETTINGS::LOG_GAME) << endl
        << "2. Toggle Map Logs: " << onOff(SETTINGS::LOG_MAP) << endl
        << "3. Toggle Dice Logs: " << onOff(SETTINGS::LOG_DICE) << endl
        << "4. Toggle Character Logs: " << onOff(SETTINGS::LOG_CHAR) << endl
        << "5. Toggle Map Elements View: " << onOff(SETTINGS::MAP_ELEMENTS_VIEW) << endl
        << "6. Exit" << endl;
        int choice = readIntegerInputWithRange("Your choice[6]: ", 6, 1, 6);

        switch (choice) {
            case 1:
                SETTINGS::LOG_GAME = !SETTINGS::LOG_GAME;
                break;
            case 2:
                SETTINGS::LOG_MAP = !SETTINGS::LOG_MAP;
                break;
            case 3:
                SETTINGS::LOG_DICE = !SETTINGS::LOG_DICE;
                break;
            case 4:
                SETTINGS::LOG_CHAR = !SETTINGS::LOG_CHAR;
                break;
            case 5:
                SETTINGS::MAP_ELEMENTS_VIEW = !SETTINGS::MAP_ELEMENTS_VIEW;
                break;
            case 6:
                done = true;
                break;
        }
    }while (!done);

}


void UserPlayerStrategy::endGameLevelUp(Character* character) {

    int input1, input2, input3;

    if (character->getLevel() == 4 || character->getLevel() == 6 || character->getLevel() == 8 || character->getLevel() == 12
            || character->getLevel() == 14 || character->getLevel() ==16 || character->getLevel() == 19 )
    {
                cout << "You have the possibility to increase your ability scores !! " << endl;
                cout << "Press 1 - to increase one ability score by 2 " << endl;
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
                // true; WHAT IS THAT CONDITION FOR?
            }

}
