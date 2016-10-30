/// @file
/// @brief Header file containing class declaration for Subject.class
/// @details Subject/Observable abstract class for observer pattern

#pragma once

#include <list>
#include "Observer.h"

using namespace std;

class Subject {
    public:
        virtual void attach(Observer* o);
        virtual void detach(Observer* o);
        virtual void notify();
        int getNbObservers();
        Subject();
        ~Subject();

    private:
       list<Observer*> *_observers;
};
