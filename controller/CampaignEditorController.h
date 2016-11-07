/// @file
/// @brief Header file containing class declaration for CampaignEditorController.class
/// @details  1. Game Rules: The code allows the player to create/edit a campaign and to save/load it. \n\n
/// 2. Design: Controller class from the MVC pattern. It encapsulates all the logic to communicate with the user to create/edit a campaign \n\n
/// 3. Libraries: The boost archive libraries and the standard filestream libraries were used in order to save/load the campaign.

#pragma once

#include "../entity/Campaign.h"
#include "MapEditorController.h"


class CampaignEditorController{
    public:
        CampaignEditorController();
        CampaignEditorController(Campaign* c);
    
        Campaign* createCampaign();
        void saveCampaign(string filename);
        static Campaign loadCampaign(string filename);
        void addMap(Map map);
        void removeMap();
        void setCampaign(Campaign* c);
    
    
    private:
        Campaign* campaign;
    
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & campaign;
        
        }
    
};

inline void CampaignEditorController::setCampaign(Campaign* c){
    campaign = c;
}
