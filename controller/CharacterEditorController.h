#pragma once

#include "../entity/Character.h"
#include "../view/CharacterView.h"


class CharacterEditorController {
    public:

        static const size_t BACKPACK_INIT_SIZE;

        static void selectAction();
		static Character* selectCharacter();
        static void initializeBackpack(Character* character);

    private:
        static void createCharacter(bool pregenerated);
        static void editExistingcharacter();
        static void saveCharacter(Character* character);

};
