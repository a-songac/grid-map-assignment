/// @file
/// @brief Header file for implementation of CampaignRepository
/// @details  1. Game Rules: NONE \n\n
/// 2. inherits from Repository template, see Repopsitory.h file for more info
/// 3. Libraries: NONE


#pragma once

#include "../Campaign.h"
#include "../../core/Repository.h"
#include <vector>



class CampaignRepository : public Repository<Campaign> {
public:
    static CampaignRepository* instance();
    
private:
    CampaignRepository();
    void loadGeneratedEntities();
    static CampaignRepository* _instance;
    
};

