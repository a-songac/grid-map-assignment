//#include "Repository.h"
//#include "../utils/FileUtils.h"
//#include"../utils/LogUtils.h"
//#include "../entity_generator/MapGenerator.h"
//
//#include <fstream>
//#include <iostream>
//#include <stdio.h>
//#include <boost/filesystem.hpp>
//#include <sstream>
//
//using namespace std;
//
//Repository* Repository::Repository;
//
//Repository* Repository::instance() {
//    if (!_instance) {
//        _instance = new Repository;
//    }
//    return _instance;
//}
//
//Repository::~Repository() {
//    delete _proxies;
//}
//
//
//
/////  Load proxies of persisted map in the memory from _map_references
///// _map_references holds a list of all names of persisted map
//Repository::Repository() {
//
//    stringstream sStream;
//
//    #ifdef DEBUG
//        logInfo("Repository",
//                "Constructor",
//                "FOR " + getReferenceFileName() + ": Initialization of Repository; loading persisted map references...");
//    #endif // DEBUG
//
//    this->_proxies = new vector<ProxyEntity<T*>*>;
//    string entityName;
//    ProxyEntity<T*>* proxy;
//
//    ifstream in(ge);
//    if (!in) {
//        ofstream out;
//        out.open(getReferenceFileName(), ios::trunc);
//        out.close();
//        in.open(getReferenceFileName());
//
//        #ifdef DEBUG
//            logInfo("Repository",
//                    "Constructor",
//                    "FOR " + getReferenceFileName() + ":  references file does not exist, file created");
//                if (!in)
//                    logInfo("Repository",
//                    "Constructor",
//                    "FOR " + getReferenceFileName() + ": Could not create reference file.");
//        #endif // DEBUG
//    }
//
//    while (in >> entityName) {
//        #ifdef DEBUG
//            logInfo("Repository",
//                "Constructor",
//                "Load " + entityName);
//        #endif // DEBUG
//        proxy = new MapProxy(entityName);
//        this->_proxies->push_back(proxy);
//    }
//    in.close();
//    #ifdef DEBUG
//        sStream << "FOR " << getReferenceFileName() << ": Total of " << this->_proxies->size() << " map references loaded.";
//        logInfo("Repository",
//                "Constructor",
//                sStream.str());
//    #endif // DEBUG
//
//    if (0 == this->_proxies->size()) {
//        loadGeneratedMaps();
//
//        #ifdef DEBUG
//            logInfo("Repository",
//                    "Constructor",
//                    "FOR " + getReferenceFileName() + ": No existing maps, load and save the pregenerated maps");
//        #endif // DEBUG
//    }
//}
