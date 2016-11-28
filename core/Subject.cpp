#include "Subject.h"
#include "Observer.h"

Subject::Subject(){
	_observers = new list<Observer*>;

}

Subject::~Subject() {
        delete _observers;	
}

void Subject::Attach(Observer* addObserver) {
	_observers->push_back(addObserver);
}

void Subject::Detach(Observer* removeObserver) {
	_observers->remove(removeObserver);

}

void Subject::Notify() {

	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); i++)
		(*i)->update();
}

 