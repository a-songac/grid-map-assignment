#include "GameItem.h"
#include "../controller/MapInteractionHelper.h"

GameItem::GameItem(std::string elementReference, Coordinate* location) :
GameElement::GameElement(elementReference, location), collected(false)
{
    //ctor
}

GameItem::GameItem() : collected(false) {}

GameItem::GameItem(GameItem* gameItem) :
collected(false), GameElement(gameItem) {}

void GameItem::display() {
    std::string itemCollected = this->getCollected() ? "[Collected]" : "[Not Collected]";
    std::string locationString = MapInteractionHelper::coordinateToString(this->location);

    cout << this->elementReference << " - " << itemCollected
            << " - " << locationString << endl;
}


