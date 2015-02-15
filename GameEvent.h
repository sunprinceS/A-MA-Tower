#pragma once
#include "ofMain.h"
#include "pearl.h"

class GameEvent : public ofEventArgs {

public:

	pearl* p;
    string   message;

    GameEvent() {
		p = NULL;
    }

    static ofEvent <GameEvent> events;
};

