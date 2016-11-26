
#include "EditorFacadeController.h"
#include "../utils/IOUtils.h"
#include <boost/filesystem.hpp>
#include "../view/MapView.h"
#include "../entity/repo/MapRepository.h"
#include "CharacterEditorController.h"
#include "../controller/ItemEditor.h"
#include "MapInteractionHelper.h"

void EditorFacadeController::editorMenu() {

    bool editorLoop = true;
    do{
        cout << endl << "*********** Choose an Editor ************" << endl << endl;
        cout << "1. Map Editor"<< endl
                << "2. Campaign Editor" << endl
                << "3. Character Editor" << endl
                << "4. Item Editor" << endl
                << "5. Exit Editor Menu" << endl;

        int eChoice = readIntegerInputWithRange("Please select an option[5]: ", 5, 1, 5);

        //Return chosen editor
        if(eChoice == 1){
            cout << "************** Map Editor **************" << endl << endl;

            cout << "Please select one of the following options:" << endl << "1. Create New Map"
            << endl << "2. Edit an Existing Map" << endl;

            int cChoice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 2);


            if (cChoice == 1){

                //Create Map
                MapEditorController mapEditor;
                mapEditor.createMap();

            }
            else{

                //Load map for editing
                MapEditorController mapEditor;
                Map* map = MapInteractionHelper::selectMap();

                //Edit Options

                mapEditor.editMap(map);

                cout << "Redirecting to editor menu." << endl;



            }
        }
        else if(eChoice == 2){ // Campaign Editor

            cout << "*********** Campaign Editor ************" << endl << endl;

            cout << "Please select one of the following options:" << endl << "1. Create New Campaign"
                << endl << "2. Edit an Existing Campaign" << endl;

            int cChoice = readIntegerInput("", 1);
            while (cChoice != 1 && cChoice != 2) {
                cout << "This is not a choice, please retry" << endl;
                eChoice = readIntegerInput("Your choice[1]:", 1);
            }


            if(cChoice == 1){

                //Create Campaign

                CampaignEditorController campaignEditor;
                campaignEditor.createCampaign();

                cout << "Redirecting to editor menu." << endl;

            }
            else{
                //Load Campaign for editing
                CampaignEditorController campaignEditor;
                Campaign* campaign = campaignEditor.loadCampaign();

                //Edit Options
                if(campaign != nullptr){
                    campaignEditor.editCampaign(campaign);
                }

            }

        } // END Campaign editor
        else if(eChoice == 3){

            CharacterEditorController::selectAction();
        }

        else if(eChoice == 4){
			ItemEditor* item = new ItemEditor();
			item->editorAlternatives();
        }
        else{
            editorLoop = false;
        }

    }while(editorLoop);

}
