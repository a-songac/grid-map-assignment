#include "FileUtils.h"

using namespace std;

ifstream loadInputFileStream(string path) {
    ifstream in(path);
    if (!in) {
        cout << "Could not load for input stream the file: " << path << endl;
        exit(0);
    }
    return in;
}


ofstream loadOutputFileStream(string path) {
    ofstream out;
    out.open(path, ios::trunc);
    if (!out) {
        cout << "Could not load for output stream the file: " << path << endl;
        exit(0);
    }
    return out;
}
