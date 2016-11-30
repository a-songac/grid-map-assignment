#include "ItemInteractionHelper.h"

#include "../entity/repo/ItemRepository.h"
#include "../utils/IOUtils.h"

#include <vector>

using namespace std;

Item* ItemInteractionHelper::selectItem() {
	return selectItem(ItemRepository::instance()->listAll());
}

Item* ItemInteractionHelper::selectItemFromBackpack(Character* character) {
	return selectItem(character->backpack);
}

Item* ItemInteractionHelper::selectItemFromWornItems(Character* character) {
	return selectItem(character->wornItems);
}

Item* ItemInteractionHelper::selectItem(vector<std::string>* itemReferences) {
    string name1;
	bool confirm1 = false;
	Item* item = nullptr;

	do {
		if (itemReferences->empty()) {
			cout << "No items currently saved. Redirecting to editor menu." << endl;
			break;
		}
		else {
			cout << "Please select the item you want to load and view: " << endl;
			for (size_t i = 0; i < itemReferences->size(); i++) {
				cout << (i + 1) << ". " << itemReferences->at(i) << endl;
			}

			int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, itemReferences->size());
			item = ItemRepository::instance()->getEntity(itemReferences->at(index-1));

			if (nullptr == item) {

				cout << "Error, could not load item " << name1 << endl;
				return nullptr;

			} else {
                item->displayItem();
                confirm1 = readYesNoInput("You confirm the selection of this item displayed above?[Y/n]: ", true);
            }
		}
	} while (!confirm1);
	return item;
}

