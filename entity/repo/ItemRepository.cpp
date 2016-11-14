#include "ItemRepository.h"
#include "../../utils/FileUtils.h"
#include"../../utils/LogUtils.h"


using namespace std;

ItemRepository* ItemRepository::_instance;

ItemRepository::ItemRepository(): Repository<Item>("_item_references"){
    loadEntity = &Repository<Item>::loadItem;
    persistEntity = &Repository<Item>::persistItem;
}

ItemRepository* ItemRepository::instance() {
    if (!_instance) {
        _instance = new ItemRepository();
        if (_instance->listAll()->size() == 0) {
           // TODO preload items if none
        }
    }
    return _instance;
}


