#include <fstream>
#include <iostream>

#include "CampaignEditorController.h"
#include "../utils/IOUtils.h"
#include "../entity/repo/CampaignRepository.h"
#include "MapInteractionHelper.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "../entity/repo/MapRepository.h"

CampaignEditorController::CampaignEditorController(Campaign* c) {
    campaign = c;
}

CampaignEditorController::CampaignEditorController() {
    campaign = new Campaign;
}

void CampaignEditorController::createCampaign(){
    cout << "In order to create a campaign you must first add maps." << endl;

    Map* map;
    bool done = false;
    vector<string>* m;
    this->setCampaign(new Campaign(m));

    //Check if maps actually exist
    if(!(MapRepository::instance()->listAll()->empty())){
        vector<string> vs;
        //Add Maps
        do{
            map = MapInteractionHelper::selectMap();
            string mapName = map->getName();

            if(map->validate()){
                vs.push_back(mapName);
                done = !(readYesNoInput("Would you like to add another map to add to your campaign? [Y/n]", true));
            }
            else{
                cout << "Invalid map, please try again!" << endl;
            }

//            delete map;
        }while(!done);

        //Add vector of map names to campaign
        vector<string>* vsp = &vs;
        this->campaign->setMaps(vsp);

        //Save Campaign
        bool save = readYesNoInput("Would you like to save this campaign? [Y/n]", true);

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
            c->display();
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
                    Map* map = MapInteractionHelper::selectMap();
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

            done = !(readYesNoInput("Do you wish to further edit this campaign?[Y/n]", true));
        }while(done!=true);


        bool save = readYesNoInput("Do you wish to save these changes?[Y/n]", true);

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


Campaign* CampaignEditorController::loadCampaign() {

    Campaign* campaign;
    string filename;
    vector<string>* campaignReferences = CampaignRepository::instance()->listAll();
    if(campaignReferences->empty()) {
        cout << "No campaigns currently saved. Redirecting to editor menu." << endl;
        campaign = nullptr;
    }
    else {
        for (size_t i = 0; i < campaignReferences->size(); i++) {
            cout << (i+1) << ". " << campaignReferences->at(i) << endl;
        }

        int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, campaignReferences->size());
        campaign = CampaignRepository::instance()->getEntity(index-1);

    }

    return campaign;

}
