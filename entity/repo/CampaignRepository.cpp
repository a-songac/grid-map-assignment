#include "CampaignRepository.h"
#include "../../utils/FileUtils.h"
#include"../../utils/LogUtils.h"


using namespace std;

CampaignRepository* CampaignRepository::_instance;

CampaignRepository::CampaignRepository(): Repository<Campaign>("_campaign_references", "campaigns"){
    loadEntity = &Repository<Campaign>::loadCampaign;
    persistEntity = &Repository<Campaign>::persistCampaign;
}
CampaignRepository* CampaignRepository::instance() {
    if (!_instance) {
        _instance = new CampaignRepository();
        if (_instance->listAll()->size() == 0) {
            //TODO load preloaded campaigns if none
        }
    }
    return _instance;
}
