#pragma once
#include "Observer.h"
#include <list>
using namespace std;

class Subject {
public:
	~Subject();
	virtual void attach(Observer* addObserver);
	virtual void detach(Observer* removeObserver);
	virtual void notify();
	Subject();
private:
	list<Observer*> *_observers;



};