#include "MapInteractionHelper.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include "../utils/IOUtils.h"

const string CELL_LOCATION_REGEX = "^([a-zA-Z]{1})([0-9]+)$";


Coordinate MapInteractionHelper::readMapLocation(Map* map, string message, string defaultLocation) {

    bool error = false;
    string row, column;
    int rowIndex, columnIndex;
	string input;
    do {
        error = false;
		string cellLocation = message;
        regex regex (CELL_LOCATION_REGEX);
        smatch match;

        if (regex_search(cellLocation, match, regex)) {
            row = match.str(2);
            column = match.str(1);
            rowIndex = stoi(row, nullptr) - 1;
            columnIndex = column.at(0) - 'A'; //TODO Handle over 26 case
            if (columnIndex + 'A' >= 97 && columnIndex + 'A' <= 122) // if lowercase was given
                columnIndex -= 32;

            if (!map->isInbound(rowIndex, columnIndex)) {
                cout << "Out of range, please retry" << endl;
                error = true;
				cout << "Go to >>";
				cin >> input;
				message = input;
            }

        } else {
            error = true;
            cout << "Invalid input, please retry" << endl;
			cout << "Go to >>";
			cin >> input;
			message = input;
        }

    } while (error);

    Coordinate location = {rowIndex, columnIndex};
    return location;

}
