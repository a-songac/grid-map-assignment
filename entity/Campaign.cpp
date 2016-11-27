
#include "Campaign.h"

using namespace std;

Campaign::Campaign(){

}

Campaign::Campaign(vector<string>* m){
        maps = m;
}

Campaign::Campaign(Campaign* c){
    this->setMaps(c->getMaps());
    this->setName(c->getName());
}


bool Campaign::validate(){
    if(this->getMaps()->empty()){
        return false;
    }
    else
        return true;
}

void Campaign::display() {
    cout << "Campaign maps: " << endl;
    for(size_t i = 0; i < this->maps->size(); i++) {
        cout << (i+1) << ". " << this->maps->at(i) << endl;
    }
    cout << endl;
}
