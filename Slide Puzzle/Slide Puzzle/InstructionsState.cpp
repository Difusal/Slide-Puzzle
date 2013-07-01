#include "InstructionsState.h"
#include "StateControl.h"

void InstructionsState::Initialize()
{
	instructions_screen = al_load_bitmap(InstructionsScreen);
	if (!instructions_screen)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load login background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	_continue.p1_x = 250; _continue.p1_y = 494;
	_continue.p2_x = 550; _continue.p2_y = 524;
}

bool InstructionsState::Update(ALLEGRO_EVENT * ev)
{
	/* button presses */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		_continue.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _continue.p2_x &&
		_continue.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _continue.p2_y)
	{
		cout << "Continue button pressed." << endl;
		StateControl::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	return false;
}

void InstructionsState::Draw()
{
	/* drawing background */
	al_draw_bitmap(instructions_screen, 0, 0, NULL);

	/* button hovers */
	if (_continue.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < _continue.p2_x &&
		_continue.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < _continue.p2_y)
	{
		al_draw_rectangle(_continue.p1_x, _continue.p1_y, _continue.p2_x, _continue.p2_y, Yellow, 1.0);
	}
}

void InstructionsState::Terminate()
{
	al_destroy_bitmap(instructions_screen);
}