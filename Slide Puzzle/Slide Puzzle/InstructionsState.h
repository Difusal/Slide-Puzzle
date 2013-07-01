#pragma once

#include "stdIncludes.h"
#include "State.h"

class InstructionsState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_BITMAP * instructions_screen;

	Button _continue;
};