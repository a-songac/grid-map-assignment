/// @file
/// @brief Header file containing class declaration for Observer.class
/// @details Observer abstract class for observer pattern

#pragma once

class Observer {
    public:
        ~Observer();
        virtual void update()=0;
    protected:
        Observer();
};
