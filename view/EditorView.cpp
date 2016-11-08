
#include "EditorView.h"
#include "../utils/IOUtils.h"
#include <boost/filesystem.hpp>
#include "MapView.h"
#include "../entity/repo/MapRepository.h"

void EditorView::editorMenu(MapRepository* mapRepo) {
    
    top:
    cout << "*********** Choose an Editor ************" << endl << endl;
    cout << "Map Editor: 1"<< endl << "Campaign Editor: 2" << endl << "Exit Editor Menu: 3" << endl;
    int eChoice = readIntegerInput("",1);
    while (eChoice != 1 && eChoice != 2 && eChoice != 3) {
        cout << "This is not a choice, please retry" << endl;
        eChoice = readIntegerInput("Your choice[1]:", 1);
    }
    
    //Return chosen editor
    if(eChoice == 1){
        cout << "************** Map Creator **************" << endl << endl;
        
        cout << "Please select one of the following options:" << endl << "Create New Map: 1"
        << endl << "Edit an Existing Map: 2" << endl;
        
        int cChoice = readIntegerInput("", 1);
        while (cChoice != 1 && cChoice != 2) {
            cout << "This is not a choice, please retry" << endl;
            eChoice = readIntegerInput("Your choice[1]:", 1);
        }
        
        //Create Map
        if (cChoice == 1){
            
            MapEditorController mapEditor;
            Map* map = mapEditor.createMap();
            mapEditor.buildMap();
            
            bool save = readYesNoInput("Would you like to save this map? (Y/n)", true);
            
            if(save){
                if(map->validate()){
                    string filename = readStringInput("Enter a Name for the File: ", "userMap");
                    mapEditor.saveMap(filename);
                    cout << "Map successfully saved." << endl;
                }
                else{
                    cout << "Invalid Map, Please Try Again. (Map not Saved)" << endl;
                }
                
                delete map;
                map = nullptr;
                goto top;
                
            }
            else{
                delete map;
                map = nullptr;
                //Back to choose editor
                goto top;
            }
        }
        else{
            //Load map for editing
            cout << "************** Map Editor **************" << endl << endl;
            
            
            ///TODO show repo files
            string filename;
            list<MapProxy*> mp = *(mapRepo->listAll());
            if(mp.empty()){
                cout << "No maps currently saved. Redirecting to editor menu." << endl;
                goto top;
            }
            else{
                int count = 0;
                for (std::list<MapProxy*>::const_iterator iterator = mp.begin(), end = mp.end(); iterator != end; ++iterator) {
                    count++;
                    cout << count << ":" <<(*iterator)->getMap()->getName();
                }
                
                int index = readIntegerInput("Please enter the index of your chosen map.", 0);
                std::list<MapProxy*>::iterator it = mp.begin();
                std::advance(it, index);
                filename = (*it)->getMap()->getName();
            }
            
            
           // string filename = readStringInput("Please enter the name of the .map file you want to edit:", "userMap.map");
            
            boost::filesystem::path myfile(filename);
            
            if( !boost::filesystem::exists(myfile) )
            {
                cout << "File not found! Redirecting to editor menu." << endl;
                goto top;
            }
            

            

            Map map = MapEditorController::loadMap(filename);
            
            //Edit Options
            if(map.validate()){
                Map* m = &map;
                MapEditorController mapEditor(m);
                
                bool done = false;
                
                do{
                    m->render();
                    
                    cout << "What changes do you want to make to this map?:" << endl;
                    cout << "Add/Remove Wall: 1" << endl;
                    cout << "Add Occupant: 2" << endl;
                
                    int choice = readIntegerInput("Your choice[1]:", 1);
                    while (choice != 1 && choice != 2) {
                        cout << "This is not a choice, please retry" << endl;
                        choice = readIntegerInput("Your choice[1]:", 1);
                    }
                
                    switch (choice) {
                        case 1:
                            mapEditor.addWall();
                            break;
                        case 2:
                            mapEditor.addOccupant();
                            break;
                    }
 
                    done = !(readYesNoInput("Do you wish to further edit this map?(Y/n)", false));
                }while(done!=true);
               
                
                bool saveEdit = readYesNoInput("Do you wish to save your changes?(Y/n)", false);
                if(saveEdit){
                    if(map.validate()){
                        mapEditor.saveMap(filename);
                        cout << "Map successfully saved." << endl;
                    }
                    else{
                        cout << "Invalid Map. (Map not Saved)" << endl;
                    }

                }
            
                cout << "Redirecting to editor menu." << endl;
                goto top;
                
            }
            else{
                cout << "Invalid map. Redirecting to editor menu." << endl;
                goto top;
            }
            
        }
    }
    else if(eChoice == 2){
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
                
                goto top;
                
            }
            else{
                delete campaign;
                campaign = nullptr;
                //Back to choose editor
                goto top;
            }

            
            
        }
        else{
            //Edit a Campaign
            cout << "*********** Campaign Editor ************" << endl << endl;
            
            string filename = readStringInput("Please enter the name of the .campaign file you want to edit:", "userCampaign.campaign");
            
            boost::filesystem::path myfile(filename);
            
            if( !boost::filesystem::exists(myfile) )
            {
                cout << "File not found! Redirecting to editor menu." << endl;
                goto top;
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
                            string filename = readStringInput("Please enter the name of the .map file you want to add:", "userMap.map");
                            
                            boost::filesystem::path myfile(filename);
                            
                            if( !boost::filesystem::exists(myfile) )
                            {
                                cout << "Map file not found!" << endl;
                            }
                            
                            Map map = MapEditorController::loadMap(filename);
                            
                            if(map.validate()){
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
                goto top;
                
                
            }
            else{
                cout << "Invalid campaign. Redirecting to editor menu." << endl;
                goto top;
            }
        }

    }
    else{
        cout << "Program terminated.";
    }


}