#include "Subject.h"
#include "Observer.h"

Subject::Subject(){
	_observers = new list<Observer*>;

}

Subject::~Subject() {
	delete _observers;
}

void Subject::attach(Observer* addObserver) {
	_observers->push_back(addObserver);
}

void Subject::detach(Observer* removeObserver) {
	_observers->remove(removeObserver);

}

void Subject::notify() {

	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); i++)
		(*i)->update();
}

