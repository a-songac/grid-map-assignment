#pragma once

#include "Repository.h"
#include <string>

template <class T>
class ProxyEntity {
    public:
        ~ProxyEntity();
        ProxyEntity();
        ProxyEntity(T* entity, std::string name);
        ProxyEntity(std::string name);

        std::string getName();
        void setName(std::string name);
        T* getEntity();
        void setEntity(T* entity);

    private:
        T* entity;
        std::string name;

};

template <class T>
inline void ProxyEntity<T>::setName(std::string name) {
    this->name = name;
}

template <class T>
inline void ProxyEntity<T>::setEntity(T* entity) {
    this->entity = entity;
}

template <class T>
inline std::string ProxyEntity<T>::getName() {
    return this->name;
}
