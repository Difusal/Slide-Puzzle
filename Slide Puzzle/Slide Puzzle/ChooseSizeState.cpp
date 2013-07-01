#include "ChooseSizeState.h"
#include "StateControl.h"

void ChooseSizeState::Initialize()
{
	screen_bg = al_load_bitmap(ChooseSizeScreen);
	if (!screen_bg)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load login background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	_3x3.p1_x = _4x4.p1_x = _5x5.p1_x = _goback.p1_x = 300;
	_3x3.p2_x = _4x4.p2_x = _5x5.p2_x = _goback.p2_x = 500;

	_3x3.p1_y = 235;
	_3x3.p2_y = 264;

	_4x4.p1_y = 287;
	_4x4.p2_y = 316;

	_5x5.p1_y = 339;
	_5x5.p2_y = 368;

	_goback.p1_y = 442;
	_goback.p2_y = 472;
}

bool ChooseSizeState::Update(ALLEGRO_EVENT * ev)
{
	if (ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
		cout << "Returning to Main Menu." << endl;
		StateControl::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	/* button presses */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		_3x3.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _3x3.p2_x &&
		_3x3.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _3x3.p2_y)
	{
		cout << "3x3 button pressed." << endl; PuzzleSize = 3;
		StateControl::GetInstance()->ChangeState(ChooseImage);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		_4x4.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _4x4.p2_x &&
		_4x4.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _4x4.p2_y)
	{
		cout << "4x4 button pressed." << endl; PuzzleSize = 4;
		StateControl::GetInstance()->ChangeState(ChooseImage);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		_5x5.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _5x5.p2_x &&
		_5x5.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _5x5.p2_y)
	{
		cout << "5x5 button pressed." << endl; PuzzleSize = 5;
		StateControl::GetInstance()->ChangeState(ChooseImage);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		_goback.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _goback.p2_x &&
		_goback.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _goback.p2_y)
	{
		cout << "Go Back button pressed." << endl;
		StateControl::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	return false;
}

void ChooseSizeState::Draw()
{
	/* drawing background */
	al_draw_bitmap(screen_bg, 0, 0, NULL);

	/* button hovers */
	if (_3x3.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _3x3.p2_x &&
		_3x3.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _3x3.p2_y)
	{
		al_draw_rectangle(_3x3.p1_x, _3x3.p1_y, _3x3.p2_x, _3x3.p2_y, Yellow, 1.0);
	}
	else if (_4x4.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _4x4.p2_x &&
		_4x4.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _4x4.p2_y)
	{
		al_draw_rectangle(_4x4.p1_x, _4x4.p1_y, _4x4.p2_x, _4x4.p2_y, Yellow, 1.0);
	}
	else if (_5x5.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _5x5.p2_x &&
		_5x5.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _5x5.p2_y)
	{
		al_draw_rectangle(_5x5.p1_x, _5x5.p1_y, _5x5.p2_x, _5x5.p2_y, Yellow, 1.0);
	}
	else if (_goback.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _goback.p2_x &&
		_goback.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _goback.p2_y)
	{
		al_draw_rectangle(_goback.p1_x, _goback.p1_y, _goback.p2_x, _goback.p2_y, Yellow, 1.0);
	}
}

void ChooseSizeState::Terminate()
{
	al_destroy_bitmap(screen_bg);
}