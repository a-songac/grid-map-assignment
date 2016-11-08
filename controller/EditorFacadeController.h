/// @file
/// @brief Header file containing class declaration for EditorView.class
/// @details  1. Game Rules:  Using the map editor, the user should be able to 1) create new maps 2)
/// define the adjacency relationships between maps to create campaigns. The editor should allow the user to either
/// create a new map/campaign from scratch or load and edit an existing map/campaign previously saved as a file.
/// The editor should allow the user to save the edited map/campaign to a file (every map and every campaign
/// should be saved as a separate file). Verification of map/campaign /validity (as expressed in project description and
/// in the first assignment) should be applied before the file is loaded or saved. . \n\n
/// 2. Design: View of the MVC pattern. Implements a Command Line Interface View to create/edit maps and campaigns. \n\n
/// 3. Libraries: The boost filesystem library was used to verify that a file indeed exists when the user tries to load it.

#pragma once
#include "MapEditorController.h"
#include "CampaignEditorController.h"
#include "../entity/repo/MapRepository.h"


/// User-interactive C++ component that enables the user to create/edit a map and connect them in a campaign.
class EditorFacadeController {
public:
    static void editorMenu();
private:

};
