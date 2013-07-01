#pragma once

#include "stdIncludes.h"
#include "State.h"

class ChooseSizeState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_BITMAP * screen_bg;

	Button _3x3;
	Button _4x4;
	Button _5x5;
	Button _goback;
};