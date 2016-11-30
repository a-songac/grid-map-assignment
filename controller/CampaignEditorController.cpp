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
        vector<string>* vs = new std::vector<string>();
        //Add Maps
        do{

            map = MapInteractionHelper::selectMap();
            string mapName = map->getName();

            if(map->validate()){
                vs->push_back(mapName);
                done = !(readYesNoInput("Would you like to add another map to add to your campaign?[Y/n]: ", true));

            }
            else{
                cout << "Invalid map, please try again!" << endl;
            }


        }while(!done);

        //Add vector of map names to campaign
        this->campaign->setMaps(vs);

        //Save Campaign
        bool save = readYesNoInput("Would you like to save this campaign?[Y/n]: ", true);

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
            cout << "-------------------" << endl;
            c->display();
            cout << "-------------------" << endl;
            cout << "What changes do you want to make to this campaign?:" << endl;
            cout << "1. Add map" << endl;
            cout << "2. Remove last map" << endl;
            cout << "3. Save amd Exit" << endl;
            cout << "4. Exit without Saving" << endl;

            int choice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 4);

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
                case 3:
                {
                    if(c->validate()) {
                        CampaignRepository::instance()->save(c->getName(), c);
                        cout << "Campaign successfully saved." << endl;
                        done = true;
                    }
                    else{
                        cout << "Invalid Campaign, Please Try Again. (Campaign not Saved)" << endl;
                        done = false;
                    }
                    break;
                }
                case 4:
                {
                    done = readYesNoInput("Do you really want to leave without saving your changes?[Y/n]: ", true);
                    if (done) {
                        CampaignRepository::instance()->clearEntity(c->getName());
                    }
                    break;
                }
            }
        }while(done!=true);

}




void CampaignEditorController::addMap(Map map){
    vector<string>* m = this->campaign->getMaps();
    m->push_back(map.getName());
}

void CampaignEditorController::removeMap(){
    this->campaign->getMaps()->pop_back();
}


Campaign* CampaignEditorController::loadCampaign() {

    Campaign* campaign = nullptr;
    string filename;
    vector<string>* campaignReferences = CampaignRepository::instance()->listAll();
    if(campaignReferences->empty()) {
        cout << "No campaigns currently saved. Redirecting to menu." << endl;
        campaign = nullptr;
    }
    else {
        bool confirm = false;
        do{
            cout << "Please select a campaign: " << endl;
            for (size_t i = 0; i < campaignReferences->size(); i++) {
                cout << (i+1) << ". " << campaignReferences->at(i) << endl;
            }

            int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, campaignReferences->size());
            campaign = CampaignRepository::instance()->getEntity(index-1);

            if (nullptr == campaign) {
                cout << "Sorry, could not load campaign" << endl;
                confirm = true;
            } else {
                campaign->display();
                confirm = readYesNoInput("You confirm the selection of this campaign displayed above?[Y/n]: ", true);
            }

        } while (!confirm);
    }

    return campaign;

}
