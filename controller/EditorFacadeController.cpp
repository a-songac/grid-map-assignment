
#include "EditorFacadeController.h"
#include "../utils/IOUtils.h"
#include <boost/filesystem.hpp>
#include "../view/MapView.h"
#include "../entity/repo/MapRepository.h"
#include "CharacterEditorController.h"
#include "../controller/ItemEditor.h"

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
            cout << "************** Map Creator **************" << endl << endl;

            cout << "Please select one of the following options:" << endl << "1. Create New Map"
            << endl << "2. Edit an Existing Map" << endl;

            int cChoice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 2);

            //Create Map
            if (cChoice == 1){

                MapEditorController mapEditor;
                mapEditor.createMap();

            }
            else{

                //Load map for editing
                MapEditorController mapEditor;
                Map* map = mapEditor.loadMap();

                //Edit Options

                mapEditor.editMap(map);
                cout << "Redirecting to editor menu." << endl;

            }
        }
        else if(eChoice == 2){ // Campaign Editor
            // Disable feature
            cout << "To be implemented." << endl;
            continue;
            cout << "*********** Campaign Creator ************" << endl << endl;

            cout << "Please select one of the following options:" << endl << "Create New Campaign: 1"
                << endl << "Edit an Existing Campaign: 2" << endl;

            int cChoice = readIntegerInput("", 1);
            while (cChoice != 1 && cChoice != 2) {
                cout << "This is not a choice, please retry" << endl;
                eChoice = readIntegerInput("Your choice[1]:", 1);
            }

            //Create Campaign
            if(cChoice == 1){

                CampaignEditorController campaignEditor;
                Campaign* campaign = campaignEditor.createCampaign();
                campaignEditor.setCampaign(campaign);

                bool save = readYesNoInput("Would you like to save this campaign? (Y/n)", true);

                if(save){
                    if(campaign->validate()){
                            string filename = readStringInput("Enter a Name for the File: ", "userCampaign");
                            campaignEditor.saveCampaign(filename);
                            cout << "Campaign successfully saved." << endl;
                    }
                    else{
                        cout << "Invalid Campaign, Please Try Again. (Campaign not Saved)" << endl;
                    }

                    delete campaign;
                    campaign = nullptr;

                }
                else{
                    cout << "Redirecting to editor menu." << endl;
                }

            }
            else{
                //Edit a Campaign
                cout << "*********** Campaign Editor ************" << endl << endl;

                string filename = readStringInput("Please enter the name of the .campaign file you want to  edit:", "userCampaign.campaign");

                boost::filesystem::path myfile(filename);

                if( !boost::filesystem::exists(myfile) )
                {
                    cout << "File not found! Redirecting to editor menu." << endl;
                }

                Campaign campaign = CampaignEditorController::loadCampaign(filename);

                //Edit Options
                if(campaign.validate()){
                    Campaign* c = &campaign;
                    CampaignEditorController campaignEditor(c);

                    bool done = false;

                    do{

                        cout << "What changes do you want to make to this campaign?:" << endl;
                        cout << "Add map: 1" << endl;
                        cout << "Remove last map: 2" << endl;

                        int choice = readIntegerInput("Your choice[1]:", 1);
                        while (choice != 1 && choice != 2) {
                            cout << "This is not a choice, please retry" << endl;
                            choice = readIntegerInput("Your choice[1]:", 1);
                        }

                        switch (choice) {
                            case 1:
                            {
                                string filename = readStringInput("Please enter the name of the .map file you   want to add:", "userMap.map");

                                boost::filesystem::path myfile(filename);

                                if( !boost::filesystem::exists(myfile) )
                                {
                                    cout << "Map file not found!" << endl;
                                }

                                Map* map = MapRepository::instance()->getEntity(filename);

                                if(map->validate()){
                                    campaignEditor.addMap(map);
                                }
                                else{
                                    cout << "Invalid map. Please try Again." << endl;
                                }

                                break;

                            }
                            case 2:
                                campaignEditor.removeMap();
                                break;
                        }

                        done = !(readYesNoInput("Do you wish to further edit this campaign?(Y/n)", true));
                    }while(done!=true);


                    bool save = readYesNoInput("Do you wish to save these changes?(Y/n)", true);

                    if(save){
                        if(c->validate()){
                            campaignEditor.saveCampaign(filename);
                            cout << "Campaign successfully saved." << endl;
                        }
                        else{
                            cout << "Invalid Campaign, Please Try Again. (Campaign not Saved)" << endl;
                        }
                    }

                    // delete c;
                    c = nullptr;

                }
                else{
                    cout << "Invalid campaign. Redirecting to editor menu." << endl;
                }
            }

        } // END Campaign editor
        else if(eChoice == 3){

            CharacterEditorController::createCharacter();
        }

        else if(eChoice == 4){
			ItemEditor* item = new ItemEditor();
			item->createItem();
        }
        else{
            editorLoop = false;
        }

    }while(editorLoop);

}
