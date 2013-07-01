#include "MainMenuState.h"
#include "StateControl.h"

void MainMenuState::Initialize()
{
	main_menu_screen = al_load_bitmap(MainMenuScreen);
	if (!main_menu_screen)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load main menu.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	_trainingmode.p1_x = _competitionmode.p1_x = _instructions.p1_x = _exit.p1_x = 246;
	_trainingmode.p2_x = _competitionmode.p2_x = _instructions.p2_x = _exit.p2_x = 555;

	_trainingmode.p1_y = 231;
	_trainingmode.p2_y = 270;
	
	_competitionmode.p1_y = 283;
	_competitionmode.p2_y = 322;
	
	_instructions.p1_y = 386;
	_instructions.p2_y = 425;

	_exit.p1_y = 438;
	_exit.p2_y = 476;
}

bool MainMenuState::Update(ALLEGRO_EVENT * ev)
{
	/* button presses */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		_trainingmode.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _trainingmode.p2_x &&
		_trainingmode.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _trainingmode.p2_y)
	{
		cout << "Training Mode button pressed." << endl;
		StateControl::GetInstance()->GameMode = TrainingMode;
		StateControl::GetInstance()->ChangeState(ChooseSize);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		_competitionmode.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _competitionmode.p2_x &&
		_competitionmode.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _competitionmode.p2_y)
	{
		cout << "Competition Mode button pressed." << endl;
		//StateControl::GetInstance()->ChangeState(SignUp);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		_instructions.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _instructions.p2_x &&
		_instructions.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _instructions.p2_y)
	{
		cout << "Instructions button pressed." << endl;
		StateControl::GetInstance()->ChangeState(Instructions);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		_exit.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _exit.p2_x &&
		_exit.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _exit.p2_y)
	{
		cout << "Exit button pressed." << endl;
		StateControl::GetInstance()->done = true;
		return true;
	}

	return false;
}

void MainMenuState::Draw()
{
	/* drawing main menu */
	al_draw_bitmap(main_menu_screen, 0, 0, NULL);

	/* button hovers */
	if (_trainingmode.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _trainingmode.p2_x &&
		_trainingmode.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _trainingmode.p2_y)
	{
		al_draw_rectangle(_trainingmode.p1_x, _trainingmode.p1_y, _trainingmode.p2_x, _trainingmode.p2_y, Yellow, 1.0);
	}
	/*
	else if (_competitionmode.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _competitionmode.p2_x &&
		_competitionmode.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _competitionmode.p2_y)
	{
		al_draw_rectangle(_competitionmode.p1_x, _competitionmode.p1_y, _competitionmode.p2_x, _competitionmode.p2_y, Yellow, 1.0);
	}
	*/
	else if (_instructions.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _instructions.p2_x &&
		_instructions.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _instructions.p2_y)
	{
		al_draw_rectangle(_instructions.p1_x, _instructions.p1_y, _instructions.p2_x, _instructions.p2_y, Yellow, 1.0);
	}
	else if (_exit.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _exit.p2_x &&
		_exit.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _exit.p2_y)
	{
		al_draw_rectangle(_exit.p1_x, _exit.p1_y, _exit.p2_x, _exit.p2_y, Yellow, 1.0);
	}
}

void MainMenuState::Terminate()
{
	al_destroy_bitmap(main_menu_screen);
}