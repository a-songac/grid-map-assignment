#include "LogUtils.h"

#include <iostream>
#include <chrono>

void logInfo(string file, string method, string message) {
    cout << "LOG INFO - <" << file << "::" << method << "> " << message << endl;
}
void logWarning(string file, string method, string message) {
    cout << "LOG WARNING - <" << file << "::" << method << "> " << message << endl;
}
void logError(string file, string method, string message) {
    cout << "LOG ERROR - <" << file << "::" << method << "> " << message << endl;
}
