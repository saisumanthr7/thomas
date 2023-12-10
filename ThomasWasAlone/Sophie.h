#pragma once
#include "PlayableCharacter.h"

class Sophie : public PlayableCharacter {
public:
    Sophie();

    // Overridden input handler for Sophie
    bool virtual handleInput();
};
