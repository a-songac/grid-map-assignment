#include "ProxyEntity.h"
#include "Repository.h"
#include "../utils/LogUtils.h"

template <class T>
ProxyEntity<T>::~ProxyEntity() {
    if (this->entity != nullptr)
        delete this->entity;
}

template <class T>
ProxyEntity<T>::ProxyEntity() {
    this->entity = nullptr;
    this->name = "";
}

template <class T>
ProxyEntity<T>::ProxyEntity(T* entity, string name) {
    this->entity = entity;
    this->name = name;
}

template <class T>
ProxyEntity<T>::ProxyEntity(string name) {
    this->entity = nullptr;
    this->name = name;
}

template <class T>
T* ProxyEntity<T>::getEntity() {
    if (nullptr == this->entity) {
        this->entity = this->getRepo()->loadEntity(this->name);
        #ifdef DEBUG
            logInfo("ProxyEntity", "getentity", "entity not yet loaded, load into memory");
        #endif // DEBUG
    }
    return this->entity;
}
