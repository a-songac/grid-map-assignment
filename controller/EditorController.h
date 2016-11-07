//
//  EditorControler.h
//  CppUnitTest
//
//  Created by MacBook SSD on 2016-10-27.
//
//

#pragma once

/// Class that implements 
class MapEditorController {
public:
    MapEditorController();
    MapEditorController(Map* map);
    
    void buildMap();
    Map* createMap();
    
private:
    void addWall();
    void addOccupant();
    Coordinate defineDoor(string message, Map* map, string defaultLocation);
    Coordinate promptForMapLocation(string message, string defaultLocation);
    char setOccupantOnMap();
    Map* map;
};