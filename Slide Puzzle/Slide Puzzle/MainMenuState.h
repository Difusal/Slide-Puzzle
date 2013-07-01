#pragma once

#include "stdIncludes.h"
#include "State.h"

class MainMenuState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_BITMAP * main_menu_screen;

	Button _trainingmode;
	Button _competitionmode;
	Button _instructions;
	Button _exit;
};