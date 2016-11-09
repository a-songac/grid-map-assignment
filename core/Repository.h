#pragma once

#include "Repository.h"
#include <vector>

template <typename T>
class Repository {
    public:
        const static std::string MAP_REFERENCE;


        static Repository* instance();
        ~Repository();


        std::vector<std::string>* listAll();
        void save(std::string name, T entity);
        bool exists(std::string name);
        T* getEntity(std::string name);
        bool remove(std::string name);
        T* find(string name);

        virtual std::string getReferenceFileName() = 0;

    private:
        std::vector<std::string>* _references;
        T* _entities;

        T* loadEntity(string name);
        static Repository<T>* _instance;
        Repository();
        void updateRepoReference();
        void loadGeneratedMaps();

};

template <class T>
inline std::vector<std::string*>* Repository<T>::listAll() {
    return this->_references;
}
