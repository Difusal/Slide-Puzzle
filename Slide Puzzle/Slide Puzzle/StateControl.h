#pragma once

#include "stdIncludes.h"

extern int PuzzleSize;
extern int PuzzleImage;
int random_number (int min, int max);

class State;

enum _screenState
{
	MainMenu,
	Instructions,
	ChooseSize,
	ChooseImage,
	TrainingMode,
};

class StateControl
{
public:
	void Initialize();
	void CreateAllegroDisplay();
	void LoadFonts();
	void start_game();
	void Terminate();

	static StateControl * GetInstance();
	void ChangeState(int newState);

	ALLEGRO_DISPLAY * GetDisplay() { return display; }

	_screenState PreviousState;
	_screenState GameMode;

	int mouse_x, mouse_y;

	bool left_mouse_button_pressed;
	bool left_mouse_button_released;
	bool left_mouse_button_pressed_twice;
	bool right_mouse_button_pressed;
	bool right_mouse_button_released;
	
	ALLEGRO_FONT * big_font;
	ALLEGRO_FONT * medium_font;
	ALLEGRO_FONT * small_font;
	ALLEGRO_FONT * tiny_font;
	
private:
	int scroll_time_pause;
	bool background_going_left;
	int background_mask;

	bool possible_double_press;
	unsigned int double_press_counter;
	bool done, draw;

	//StateControl();
	static StateControl * instance;

	int state;
	vector<State*> states;

	ALLEGRO_BITMAP * background;
	ALLEGRO_EVENT ev;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;

	friend class MainMenuState;
};