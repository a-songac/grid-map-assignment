#pragma once

#include "../entity/Item.h"
#include "../entity/Character.h"


class ItemInteractionHelper {
    public:
        static Item* selectItem();
        static Item* selectItemFromBackpack(Character* character);
        static Item* selectItemFromWornItems(Character* character);
    private:
        static Item* selectItem(vector<std::string>* listing);

};
