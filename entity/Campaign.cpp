
#include "Campaign.h"

using namespace std;

Campaign::Campaign(){

}

Campaign::Campaign(vector<string>* m){
        maps = m;
}

Campaign::Campaign(Campaign* c){
    this->setMaps(c->getMaps());
}


bool Campaign::validate(){
    if(this->getMaps()->empty()){
        return false;
    }
    else
        return true;
}
