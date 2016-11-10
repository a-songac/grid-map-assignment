#pragma once
#pragma once
#include <iostream>

#include "../entity/Item.h"
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
 ItemContainer * createItem();
	void saveFile(string name);
	ItemContainer* loadFile(string load);
	~ItemEditor();
	static void readItem(ItemContainer*, string name, ItemContainer*);

private:
	Item item;

	Enhancement enhance;
	vector<Item> All_items;
	vector <Enhancement> Enhancements;

	int armorBonus;
	int ringBonus;
	int helmetBonus;
	int swordBonus;
	int shieldBonus;
	int beltBonus;
	int bootsBonus;

	char answer;
	int choice;
	string type;




};

