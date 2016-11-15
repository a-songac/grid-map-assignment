#include <iostream>
#include <string> //for conversion from string to int/double

#include <regex>

#include "IOUtils.h"

using namespace std;

const string FILE_NAME_REGEX = "^[a-zA-Z_0-9]+$";

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

string readStringInputNoEmpty(string prompt) {

	string input;
	bool error,result;

	do {
		error = false;
		cout << prompt;
		getline(cin, input);

		if (input == "") {
			error = true;
			cout << "Invalid Input, please retry: " << endl;
		}

	} while (error);
	return input;
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

                cout << "Invalid input, please retry: " << endl;
                error = true;
            }
        } else {

            return defaultAns;
        }

    } while (error);

    return result;

}
int readIntegerInput(string prompt) {
	bool error = false;
	string input;
	int result;
	cout << prompt;
	do {
		error = false;
		getline(cin, input);

		if (input == "") {
			error = true;
			cout << "Invalid Input, please retry: " << endl;
		}
	} while (error);
	result = stoi(input, nullptr);
	return result;
}
int readIntegerInputWithRange(string prompt, int minimum, int maximum) {
	int result;
	result = readIntegerInput(prompt);
	while (result < minimum || result > maximum) {
		result = readIntegerInput("Invalid input, please retry: ");
	}
	return result;
}
int readIntegerInputWithRange(string prompt, int defaultAns, int minimum, int maximum) {

    int result;
    result = readIntegerInput(prompt, defaultAns);
    while (result < minimum || result > maximum) {
        result = readIntegerInput("Invalid input, please retry: ", defaultAns);
    }
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

string readFileName(string message) {
    bool error = false;
    regex regex (FILE_NAME_REGEX);
    smatch match;
    string name;

    do {
        error = false;
        name = readStringInput(message, "%%"); // provide faulty input as default to force loop

        if (!regex_search(name, match, regex)
            || name == "_map_references"
            || name == "_characher_references"
            || name == "_item_references"
            || name == "_campaign_references") {

            error = true;
            cout << "Invalid input, please retry" << endl;
        }

    } while(error);
    return name;
}
