#include <fstream>
#include <iostream>

#include "CampaignEditorController.h"
#include "../utils/IOUtils.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

CampaignEditorController::CampaignEditorController(Campaign* c) {
    campaign = c;
}

CampaignEditorController::CampaignEditorController() {
    campaign = nullptr;
}

Campaign* CampaignEditorController::createCampaign(){
    cout << "In order to create a campaign you must first create a map." << endl;
    
    bool done = false;
    std::vector<Map> campaign;
    
    do{
        MapEditorController mapEditor;
        mapEditor.createMap();
        Map* map = mapEditor.getMap();
        mapEditor.buildMap();
        
        if(map->validate()){
            campaign.push_back(*map);
            done = !(readYesNoInput("Would you like to create another map to add to your campaign? (Y/n)", true));
        }
        else{
            cout << "Invalid map, please try again!" << endl;
        }
        delete map;
        map = nullptr;
    }while(done!=true);
    
    //Create campaign with created maps
    
    Campaign* c = new Campaign(campaign);
    
    return c;
    
}

void CampaignEditorController::addMap(Map map){
    vector<Map> m = this->campaign->getMaps();
    m.push_back(map);
    Campaign* c = new Campaign(m);
    this->setCampaign(c);
}

void CampaignEditorController::removeMap(){
    this->campaign->getMaps().pop_back();
    vector<Map> m = this->campaign->getMaps();
    m.pop_back();
    Campaign* c = new Campaign(m);
    this->setCampaign(c);
}

void CampaignEditorController::saveCampaign(string filename){
    string file = filename;
    std::ofstream ofs(file);
    boost::archive::text_oarchive oa(ofs);
    oa << this->campaign;
    ofs.close();
    
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
    


}


Campaign CampaignEditorController::loadCampaign(string filename){
    Campaign* c;
    std::ifstream ifs(filename, std::ios::binary);
    boost::archive::text_iarchive ia(ifs);
    ia >> c;
    ifs.close();
    return *c;
}
