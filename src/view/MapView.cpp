#include "MapView.h"

#include <iostream>

using namespace std;

const int CELL_HEIGHT = 5;
const int CELL_WIDTH = 10;
const int LEFT_MARGIN = 5;
const string HORIZONTAL_BORDER = "*";
const string VERTICAL_BORDER = "*";
const string FLOOR = " ";
const string WALL = "*";
const string ENTRY_DOOR = "+";
const string EXIT_DOOR = "-";

const char ENTRY_DOOR_PATTERN[CELL_HEIGHT][CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', 'E', 'N', 'T', 'R', 'Y', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

const char EXIT_DOOR_PATTERN[CELL_HEIGHT][CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', 'E', 'X', 'I', 'T', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

const char OPPONENT_PATTERN[CELL_HEIGHT][CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', 'M', 'E', 'A', 'N', ' ', ' ',},
        {' ', ' ', 'G', 'U', 'Y', '!', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

const char CHEST_PATTERN[CELL_HEIGHT][CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', 'C', 'H', 'E', 'S', 'T', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

const char FRIEND_PATTERN[CELL_HEIGHT][CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', 'F', 'R', 'I', 'E', 'N', 'D', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

const char PLAYER_PATTERN[CELL_HEIGHT][CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', '*', 'M', 'E', '*', ' ', ' ',}
    };


MapView::MapView(){
}

MapView::~MapView(){
    map->detach(this);
}

MapView::MapView(Map* m) {
    map = m;
    map->attach(this);
}

void MapView::update(){
    renderMap();
}

void MapView::renderMap() {

    int height = map->getHeight();
    int width = map->getWidth();
    int charsWidth = (CELL_WIDTH-1)*width + 1;

    MapView::displayLeftMargin(false, -1, LEFT_MARGIN);
    MapView::displayHeaderNavigation(charsWidth, CELL_WIDTH);
    cout << endl << endl;

    for (int i = 0; i < height; i++) {

        for (int h = 0; h < CELL_HEIGHT; h++) {

        MapView::displayLeftMargin(
                        h == CELL_HEIGHT/2,
                        i,
                        LEFT_MARGIN);

            for (int j = 0; j < width; j++) {

                if (h == 0) {

                    for (int x=0;x<CELL_WIDTH-1;x++)
                        cout << HORIZONTAL_BORDER;

                } else {

                    cout << VERTICAL_BORDER;
                    for (int x=0;x<CELL_WIDTH - 2;x++) {
                        if (map->isWall(i,j))
                            cout << WALL;
                        else if (map->hasPlayer(i, j))
                            cout << PLAYER_PATTERN[h][x];
                        else if (map->isOccupied(i,j)) {

                            switch (map->getOccupant(i,j)) {
                                case Cell::OCCUPANT_FRIEND:
                                    cout << FRIEND_PATTERN[h][x];
                                    break;
                                case Cell::OCCUPANT_OPPONENT:
                                    cout << OPPONENT_PATTERN[h][x];
                                    break;
                                case Cell::OCCUPANT_CHEST:
                                    cout << CHEST_PATTERN[h][x];
                                    break;
                            }
                        }
                        else if (map->isEntryDoor(i,j))
                            cout << ENTRY_DOOR_PATTERN[h][x];
                        else if (map->isExitDoor(i,j))
                            cout << EXIT_DOOR_PATTERN[h][x];
                        else {
                            cout << FLOOR;
                        }


                    }
                }
                if (j == width -1) {
                    cout << VERTICAL_BORDER;
                }

            } // end width loop
            cout << endl;
        } // end cell height loop
    }// cell grid height loop

    MapView::displayLeftMargin(false, -1, LEFT_MARGIN);

    for (int x=0;x<charsWidth;x++)
        cout << HORIZONTAL_BORDER;
    cout << endl << endl;

}


void MapView::displayHeaderNavigation(int charsWidth, int cellWidth) {

    for (int i = 0; i < charsWidth; i++) {
        if ((i-(cellWidth-1)/2)%(cellWidth-1) == 0)
            cout << (char)((i)/(cellWidth-1) + 'A');
        else
            cout << " ";
    }
}

// TODO Support height greater than 26 since I use letters
void MapView::displayLeftMargin(bool displayNavigation, int n, int margin) {
    for(int i = 0; i < margin; i++) {
        if (displayNavigation &&  i == margin/2)
            cout << n+1;
        else
            cout << " ";
    }
}
