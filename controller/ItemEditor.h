#pragma once
#pragma once
#include <iostream>

//#include "../entity/Item.h"
#include "../entity/Enhancement.h"
#include "../entity/ItemContainer.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class ItemEditor
{

public:
	ItemEditor();
	~ItemEditor();
	ItemContainer* createItem();
	ItemContainer* loadFile(string load);
	void saveFile(string name);
	static void readItem(ItemContainer*, string name, ItemContainer*);

private:
	int i = 0;
	int choice;
	int armorBonus;
	int ringBonus;
	int helmetBonus;
	int swordBonus;
	int shieldBonus;
	int beltBonus;
	int bootsBonus;
	vector<int> bonus;
	vector<std::string> typeEnhancements;
	string save;
	string load;
	string itemType, enhancementType;
	string name;
	string itemName;
	string answer, quit;
	Item item;
	Enhancement enhance;
	vector<Item> All_items;
	vector <Enhancement> Enhancements;




};

