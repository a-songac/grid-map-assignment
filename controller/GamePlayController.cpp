
#include "GamePlayController.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <list>

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../entity/Character.h"
#include "../entity/GamePlayer.h"
#include "../entity/repo/MapRepository.h"
#include "../entity/repo/GameRepository.h"
#include "../utils/IOUtils.h"
#include "../utils/LogUtils.h"
#include "MapInteractionHelper.h"
#include "../core/Repository.h"
#include "../controller/CharacterEditorController.h"
#include "../entity/repo/CharacterRepository.h"
#include "../view/CharacterView.h"
#include "../controller/CharacterEditorController.h"
#include "../controller/ItemEditor.h"
#include "CharacterInteractionHelper.h"
#include "MapInteractionHelper.h"
#include "../service/Settings.h"
#include "CampaignEditorController.h"
#include "../entity/repo/CampaignRepository.h"

using namespace std;


GamePlayController::GamePlayController() : level(1), map(nullptr) {}

void GamePlayController::newGame() {

	cout << "\n************* New Game *************" << endl << endl;

    CampaignEditorController campaignEditorController;
    this->campaign = campaignEditorController.loadCampaign();
    if (this->campaign->getMaps()->empty()) {
        return;
    }

    this->map = MapRepository::instance()->getEntity(this->campaign->getMaps()->at(0));

    Character* referenceCharacter;
	Character* gameCharacter;
	referenceCharacter = CharacterInteractionHelper::selectCharacter();

	cout << endl << endl << "********** GAME READY TO BE PLAYED **********" << endl;

	bool startGame = readYesNoInput("Ready to start the game " + referenceCharacter->getName() + "?[Y/n]", 1);
	if (startGame) {

        gameCharacter = new Character(referenceCharacter);
        CharacterView* charView = new CharacterView(gameCharacter);
        Game* game = new Game("", gameCharacter, this->campaign->getName(), 0);

        this->startGame(game);
	}

}

void GamePlayController::loadGame() {

    Game* game = nullptr;

    bool confirm = false;
    string filename, name1;
    vector<string>* gameReferences = GameRepository::instance()->listAll();

    if(gameReferences->size() > 0){

        do {
            cout << "Please select a game: " << endl;
            for (size_t i = 0; i < gameReferences->size(); i++) {
                cout << i+1 << ". " << gameReferences->at(i) << endl;
            }
            int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, gameReferences->size());

            game = GameRepository::instance()->getEntity(index-1);

            if (nullptr == game) {

                cout << "Sorry, could not load game" << endl;
                confirm = true;

            } else {
                // TODO
                cout << "Game Character: "+ game->getCharacterName() << endl;
                game->getUserCharacter()->display();
                confirm = readYesNoInput("You confirm the selection of this game displayed above?[Y/n]: ", true);
            }

        } while (!confirm);


        // LOGIC TO LOAD THE MAP AT WHICH THE O+PLAYER IS IN HIS PROGRESSION
        this->campaign = CampaignRepository::instance()->getEntity(game->getCampaignName());
        this->map = MapRepository::instance()->getEntity(this->campaign->getMaps()->at(game->getMapIndex()));

        this->startGame(game);

    } else {
        cout << "No games to be loaded" << endl;
    }




}


void GamePlayController::startGame(Game* game) {

    Character* gameCharacter = game->getUserCharacter();
    game->setCharacterName(game->getUserCharacter()->getName());
    int characterLevel = gameCharacter->getLevel();
    SETTINGS::IN_GAME = true;
    int initialHp = 0;

    bool mapOver = false;
    bool gameOver = false;
    bool died = false;

    cout << "\n************* Start Game *************" << endl << endl;

    do{

        map->setInGamePlayers();
        Coordinate entryDoor = this->map->getEntryDoorCoordinate();
        Coordinate* userLocation = new Coordinate(entryDoor.row, entryDoor.column);
        GamePlayer userPlayer(gameCharacter->getName(), userLocation, Cell::OCCUPANT_PLAYER);
        userPlayer.setInGameCharacter(gameCharacter);
        map->setUserGamePlayer(&userPlayer);
        initialHp = gameCharacter->getHitPoints();

        vector<GamePlayer*>* gamePlayers = this->map->getGamePlayers();

        this->map->movePlayer(entryDoor.row, entryDoor.column);
        do {

            mapOver = userPlayer.turn(this->map);
            if (!mapOver) {
                for (size_t i = 0; i < gamePlayers->size(); i++) {
                    gamePlayers->at(i)->turn(this->map);
                    map->render();
                    gamePlayers->at(i)->display();
                    readStringInput("Player above finishied his turn, press any key to continue...", "");

                    if (gameCharacter->getHitPoints() <= 0) {
                        died = true;
                        gameOver = true;
                        mapOver = true;
                        cout << "\n\n\n************ GAME OVER, YOU DIED ************" << endl << endl;
                        gameCharacter->setHitPoints(initialHp);
                        readStringInput("Press any key to continue and go back to menu...", "");
                        break;
                    }
                }
            }

        } while (!mapOver);

        //Assuming map completion
        if(characterLevel!=gameCharacter->getLevel()){
            //map completed

            if(game->getMapIndex() == (this->campaign->getMaps()->size()-1)){
                //campaign completed
                cout << "Campaign Completed!" << endl;
                //Reset Campaign
                game->setMapIndex(0);
                gameOver=true;

            }
            else{
                MapRepository::instance()->clearEntity(this->map->getName());
                string nextMapName = this->campaign->getMaps()->at(game->getMapIndex()+1);
                this->map = MapRepository::instance()->getEntity(nextMapName);
                game->setMapIndex(game->getMapIndex()+1);
                map->unsetInGamePlayers();

                if (readYesNoInput("Would you like to save your progress?[Y/n]", 1))
                {


                    if ("" == game->getGameSaveName()) {
                        game->setGameSaveName(readStringInputNoEmpty("Please provide a name for the game: "));
                    }
                    if (GameRepository::instance()->save(game->getGameSaveName(), game)) {
                        cout << "Game successfully saved" << endl;
                    }

                }
            }

        }
        else{
            //Quit or died
            gameOver=true;
        }



        // reset map to what it was


        //SETTINGS::IN_GAME = false;
        map->unsetInGamePlayers();

    } while (!gameOver);

    // SAVING OF THE GAME, NOT ONLY THE CHARACTER, PLUS SAVE A COPY OF THE CHARACTER
    if (!died && readYesNoInput("Would you like to save your progress?[Y/n]", 1))

    {
        if ("" == game->getGameSaveName()) {
            game->setGameSaveName(readStringInputNoEmpty("Please provide a name for the game: "));
        }
        if (GameRepository::instance()->save(game->getGameSaveName(), game)) {
            cout << "Game successfully saved" << endl;
        }

    }


    // reset map to what it was


    SETTINGS::IN_GAME = false;
    map->unsetInGamePlayers();
    MapRepository::instance()->clearEntity(this->map->getName());
}
