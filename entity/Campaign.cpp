
#include "Campaign.h"

Campaign::Campaign(){
    
}

Campaign::Campaign(vector<Map> m){
        maps = m;
}


bool Campaign::validate(){
    if(this->getMaps().empty()){
        return false;
    }
    else
        return true;
}