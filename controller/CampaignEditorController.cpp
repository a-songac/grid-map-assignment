#include <fstream>
#include <iostream>

#include "CampaignEditorController.h"
#include "../utils/IOUtils.h"
#include "../entity/repo/CampaignRepository.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "../entity/repo/MapRepository.h"
#include "MapInteractionHelper.h"

CampaignEditorController::CampaignEditorController(Campaign* c) {
    campaign = c;
}

CampaignEditorController::CampaignEditorController() {
    campaign = new Campaign;
}

void CampaignEditorController::createCampaign(){
    cout << "In order to create a campaign you must first add maps." << endl;
    
    bool done = false;
    vector<string>* m;
    this->setCampaign(new Campaign(m));
    
    //Check if maps actually exist
    if(!(MapRepository::instance()->listAll()->empty())){
        vector<string> vs;
        //Add Maps
        do{
            MapEditorController mapEditor;
            Map* map = MapInteractionHelper::selectMap();
            string mapName = map->getName();
        
            if(map->validate()){
                vs.push_back(mapName);
                done = !(readYesNoInput("Would you like to add another map to add to your campaign? (Y/n)", false));
            }
            else{
                cout << "Invalid map, please try again!" << endl;
            }
        
            delete map;
        }while(done != true);
        
        //Add vector of map names to campaign
        vector<string>* vsp = &vs;
        this->campaign->setMaps(vsp);
        
        //Save Campaign
        bool save = readYesNoInput("Would you like to save this campaign? (Y/n)", true);
    
        if(save){
            string filename = readStringInput("Enter a Name for the File: ", "userCampaign");
            this->campaign->setName(filename);
            CampaignRepository::instance()->save(filename, this->campaign);
            cout << "Campaign successfully saved." << endl;
        }
        
    }
    else{
        cout << "No maps currently saved. You must first create maps to create a campaign."<< endl;
    }

    

    
}

void CampaignEditorController::editCampaign(Campaign* c){
    
        
        this->setCampaign(c);
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
                    //Add Map
                    MapEditorController m;
                    Map* map = m.loadMap();
                    this->addMap(map);
                    break;
                    
                }
                case 2:
                {
                    if(this->campaign->getMaps()->empty()){
                        cout << "Cannot remove map from empty campaign." << endl;
                    }
                    else{
                        //Remove Map
                        this->removeMap();
                    }
                    break;
                }
            }
            
            done = !(readYesNoInput("Do you wish to further edit this campaign?(Y/n)", true));
        }while(done!=true);
        
        
        bool save = readYesNoInput("Do you wish to save these changes?(Y/n)", true);
        
        if(save){
            if(c->validate()){
                CampaignRepository::instance()->save(c->getName(), c);
                cout << "Campaign successfully saved." << endl;
            }
            else{
                cout << "Invalid Campaign, Please Try Again. (Campaign not Saved)" << endl;
            }
        }
        
}

    


void CampaignEditorController::addMap(Map map){
    vector<string>* m = this->campaign->getMaps();
    m->push_back(map.getName());
//    Campaign* c = new Campaign(m);
//    this->setCampaign(c);
}

void CampaignEditorController::removeMap(){
    this->campaign->getMaps()->pop_back();
}

//void CampaignEditorController::saveCampaign(string filename){
//    string file = filename;
//    std::ofstream ofs(file);
//    boost::archive::text_oarchive oa(ofs);
//    oa << this->campaign;
//    ofs.close();

    //Save maps contained in campaign
//    int count = 0;
//    for(std::vector<Map>::iterator it = campaign->getMaps().begin(); it != campaign->getMaps().end(); ++it) {
//        string mapFile = "map"+ std::to_string(count) + filename + ".map";
//        count++;
//        Map map = *it;
//        Map* map1 = &map;
//        std::ofstream ofs(mapFile);
//        boost::archive::text_oarchive oa(ofs);
//        oa << map1;
//        ofs.close();
//    }
    





Campaign* CampaignEditorController::loadCampaign(){
    
    Campaign* campaign;
    string filename;
    vector<string>* campaignReferences = CampaignRepository::instance()->listAll();
    if(campaignReferences->empty()){
        cout << "No campaigns currently saved. Redirecting to editor menu." << endl;
    }
    else{
        for (size_t i = 0; i < campaignReferences->size(); i++) {
            cout << (i+1) << ":" << campaignReferences->at(i) << endl;
        }
        
        int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, campaignReferences->size());
        campaign = CampaignRepository::instance()->getEntity(index-1);
        
        //If not in memory, load into memory
        if(campaign==nullptr){
            campaign = CampaignRepository::instance()->loadCampaign(campaignReferences->at(index-1));
        }
        
    }
    
    return campaign;

}
