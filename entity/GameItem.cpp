#include "GameItem.h"

GameItem::GameItem(std::string elementReference, Coordinate* location) :
GameElement::GameElement(elementReference, location), collected(false)
{
    //ctor
}

GameItem::GameItem() : collected(false) {}

GameItem::GameItem(GameItem* gameItem) :
collected(false), GameElement(gameItem) {}


