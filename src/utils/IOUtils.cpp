#include <iostream>
#include <string> //for conversion from string to int/double

#include "IOUtils.h"

using namespace std;

bool readYesNoInput(string prompt, bool defaultAns) {

    string input;

    cout << prompt;
    getline(cin, input);

    if (input == "")
        return defaultAns;

    if (input == "N" || input == "n")
        return false;

    if (input == "Y" || input == "y")
        return true;

    return defaultAns;

}

string readStringInput(string prompt, string defaultAns) {

    string input;
    cout << prompt;
    getline(cin, input);

    if (input != "")
        return input;
    return defaultAns;

}

int readIntegerInput(string prompt, int defaultAns) {

    string input;
    int result;

    cout << prompt;
    getline(cin, input);

    if (input != "") {

        result = stoi(input, nullptr);
        return result;
    }
    return defaultAns;


}

double readDoubleInput(string prompt, double defaultAns) {

    string input;
    double result;

    cout << prompt;
    getline(cin, input);

    if (input != "") {

        result = stod(input, nullptr);
        return result;
    }
    return defaultAns;

}
