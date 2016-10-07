#include "MapRenderer.h"

#include <iostream>

using namespace std;

const string MapRenderer::HORIZONTAL_BORDER = "*";
const string MapRenderer::VERTICAL_BORDER = "*";
const string MapRenderer::FLOOR = " ";
const string MapRenderer::WALL = "*";
const string MapRenderer::ENTRY_DOOR = "+";
const string MapRenderer::EXIT_DOOR = "-";

const char ENTRY_DOOR_PATTERN[MapRenderer::CELL_HEIGHT][MapRenderer::CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', 'E', 'N', 'T', 'R', 'Y', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

    const char EXIT_DOOR_PATTERN[MapRenderer::CELL_HEIGHT][MapRenderer::CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', 'E', 'X', 'I', 'T', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

    const char OPPONENT_PATTERN[MapRenderer::CELL_HEIGHT][MapRenderer::CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', 'M', 'E', 'A', 'N', ' ', ' ',},
        {' ', ' ', 'G', 'U', 'Y', '!', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

    const char CHEST_PATTERN[MapRenderer::CELL_HEIGHT][MapRenderer::CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', 'C', 'H', 'E', 'S', 'T', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

    const char FRIEND_PATTERN[MapRenderer::CELL_HEIGHT][MapRenderer::CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', 'F', 'R', 'I', 'E', 'N', 'D', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };

    const char PLAYER_PATTERN[MapRenderer::CELL_HEIGHT][MapRenderer::CELL_WIDTH-2] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', '*', 'M', 'E', '*', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
    };




void MapRenderer::renderMap(Map* map) {

    int height = map->getHeight();
    int width = map->getWidth();
    Cell **grid = map->getGrid();
    int charsWidth = (MapRenderer::CELL_WIDTH-1)*width + 1;

    displayLeftMargin(false, -1, MapRenderer::LEFT_MARGIN);
    displayHeaderNavigation(charsWidth, MapRenderer::CELL_WIDTH);
    cout << endl << endl;

    for (int i = 0; i < height; i++) {

        for (int h = 0; h < MapRenderer::CELL_HEIGHT; h++) {

        displayLeftMargin(
                        h == MapRenderer::CELL_HEIGHT/2,
                        i,
                        MapRenderer::LEFT_MARGIN);

            for (int j = 0; j < width; j++) {

                if (h == 0) {

                    for (int x=0;x<MapRenderer::CELL_WIDTH-1;x++)
                        cout << MapRenderer::HORIZONTAL_BORDER;

                } else {

                    cout << MapRenderer::VERTICAL_BORDER;
                    for (int x=0;x<MapRenderer::CELL_WIDTH - 2;x++) {
                        if (grid[i][j].getType() == Cell::WALL)
                            cout << MapRenderer::WALL;
                        else if (grid[i][j].getType() == Cell::DOOR_ENTRY)
                            cout << ENTRY_DOOR_PATTERN[h][x];
                        else if (grid[i][j].getType() == Cell::DOOR_EXIT)
                            cout << EXIT_DOOR_PATTERN[h][x];
                        else {
                            cout << MapRenderer::FLOOR;


                        }
                    }
                }
                if (j == width -1) {
                    cout << MapRenderer::VERTICAL_BORDER;
                }

            } // end width loop
            cout << endl;
        } // end cell height loop
    }// cell grid height loop

    displayLeftMargin(false, -1, MapRenderer::LEFT_MARGIN);

    for (int x=0;x<charsWidth;x++)
        cout << MapRenderer::HORIZONTAL_BORDER;
    cout << endl << endl;

}


void displayHeaderNavigation(int charsWidth, int cellWidth) {

    for (int i = 0; i < charsWidth; i++) {
        if ((i-(cellWidth-1)/2)%(cellWidth-1) == 0)
            cout << (char)((i)/(cellWidth-1) + 'A');
        else
            cout << " ";
    }
}

// TODO Support height greater than 26 since I use letters
void displayLeftMargin(bool displayNavigation, int n, int margin) {
    for(int i = 0; i < margin; i++) {
        if (displayNavigation &&  i == margin/2)
            cout << n+1;
        else
            cout << " ";
    }
}
