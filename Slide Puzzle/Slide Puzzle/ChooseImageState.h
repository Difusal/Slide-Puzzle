#pragma once

#include "stdIncludes.h"
#include "State.h"

class ChooseImageState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_BITMAP * screen_bg;

	ALLEGRO_BITMAP * thumbnail_1;
	ALLEGRO_BITMAP * thumbnail_2;
	ALLEGRO_BITMAP * thumbnail_3;
	ALLEGRO_BITMAP * thumbnail_4;
	ALLEGRO_BITMAP * thumbnail_5;
	ALLEGRO_BITMAP * thumbnail_6;

	Button button_1;
	Button button_2;
	Button button_3;
	Button button_4;
	Button button_5;
	Button button_6;
};