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
    bool error = false;
    string input;
    int result;

    do {
        error =false;
        cout << prompt;
        getline(cin, input);

        if (input != "") {
            try {
                result = stoi(input, nullptr);
            } catch (const std::invalid_argument& ia) {

                cout << "Invalid input, please retry" << endl;;
                error = true;
            }
        } else {

            return defaultAns;
        }

    } while (error);

    return result;

}

double readDoubleInput(string prompt, double defaultAns) {

    bool error = false;
    string input;
    double result;

    do {
        error =false;
        cout << prompt;
        getline(cin, input);

        if (input != "") {
            try {
                result = stod(input, nullptr);
            } catch (const std::invalid_argument& ia) {
                cout << "Invalid input, please retry" << endl;;
                error = true;
            }
        } else {

            return defaultAns;
        }

    } while (error);

    return result;

}
