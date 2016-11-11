#pragma once

#include "Repository.h"
#include <string>
#include <vector>

template <class T> class Repository {
    public:

        const static int REPO_CAPACITY;

        static Repository* instance();
        ~Repository();


        std::vector<std::string>* listAll();
        bool save(std::string name, T* entity);
        bool exists(std::string name);
        T* getEntity(std::string name);
        T* getEntity(int index);
        bool remove(std::string name);
        T* find(std::string name);


    private:
        std::vector<std::string>* _references;
        T* _entities;

        virtual std::string getReferenceFileName() = 0;
        virtual T* loadEntity(std::string name);

        static Repository<T>* _instance;
        Repository();
        void updateRepoReference();
        int getIndex(std::string name);

        virtual void loadGeneratedEntities() = 0;
        virtual bool persist(T* entity) = 0;

};

template <class T>
inline std::vector<std::string>* Repository<T>::listAll() {
    return this->_references;
}
