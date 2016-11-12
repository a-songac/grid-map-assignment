//#pragma once
//
//#include "ProxyEntity.h"
//#include "Repository.h"
//#include <vector>
//
//
//class Repository {
//    public:
//        static Repository* instance();
//        ~Repository();
//
//
//        std::vector<ProxyEntity<T*>*>* listAll();
//        void save(ProxyEntity<T*>* entity);
//        void save(string name);
//        bool exists(string name);
//        ProxyEntity<T*>* getEntity(string name);
//        bool remove(string name);
//        ProxyEntity<T*>* find(string name);
//        T* loadEntity(string name);
//
//        virtual std::string getReferenceFileName() = 0;
//
//
//    private:
//        std::vector<ProxyEntity<T*>*>* _proxies;
//        static Repository* _instance;
//        Repository();
//        void updateRepoReference();
//        void loadGeneratedMaps();
//
//};
