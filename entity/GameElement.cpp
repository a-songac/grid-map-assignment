#include "GameElement.h"

using namespace std;

GameElement::GameElement(string elementReference, Coordinate* location)
: elementReference(elementReference), location(location) {}

GameElement::GameElement() : elementReference(""), location(new Coordinate()) {
}

GameElement::GameElement(GameElement* toCopy)
: elementReference(toCopy->getElementReference()), location(toCopy->getLocation()) {}
