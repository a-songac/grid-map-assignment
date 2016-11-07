//
//  EditorView.cpp
//  CppUnitTest
//
//  Created by MacBook SSD on 2016-10-27.
//
//

#include "EditorView.h"
#include "../utils/IOUtils.h"

void EditorView::editorMenu() {
    
    cout << "*********** Choose an Editor ************" << endl << endl;
    cout << "Map Editor: 1"<< endl << "Campaign Editor: 2" << endl;
    int eChoice = readIntegerInput("",1);
    
    //Return chosen editor
    if(eChoice == 1){
        cout << "************** Map Creator **************" << endl << endl;
        
        cout << "Please select one of the following options:" << endl << "Create New Map: 1"
        << endl << "Edit an Existing Map: 2" << endl;
        
        int cChoice = readIntegerInput("", 1);
        
        //Create or edit Map
        if (cChoice == 1){
            
            MapEditorController mapEditor;
            Map* map = mapEditor.createMap();
            mapEditor.buildMap();
            
            bool save = readYesNoInput("Would you like to save this map? (Y/n)","Y");
            
            if(save){
                
            }
            else{
                //Back to choose editor
                editorMenu();
            }
        }
        else{
            
        }
    }
    else{
        cout << "*********** Campaign Creator ************" << endl << endl;
    }

}