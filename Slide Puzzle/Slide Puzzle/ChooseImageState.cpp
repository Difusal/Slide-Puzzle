#include "ChooseImageState.h"
#include "StateControl.h"

void ChooseImageState::Initialize()
{
	screen_bg = al_load_bitmap(ChooseImageScreen);
	if (!screen_bg)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	switch (PuzzleSize)
	{
	case 3:
		thumbnail_1 = al_load_bitmap("res//puzzles//3x3//1.png");
		thumbnail_2 = al_load_bitmap("res//puzzles//3x3//2.png");
		thumbnail_3 = al_load_bitmap("res//puzzles//3x3//3.png");
		thumbnail_4 = al_load_bitmap("res//puzzles//3x3//4.png");
		thumbnail_5 = al_load_bitmap("res//puzzles//3x3//5.png");
		thumbnail_6 = al_load_bitmap("res//puzzles//3x3//6.png");
		break;
	case 4:
	case 5:
		thumbnail_1 = al_load_bitmap("res//puzzles//4x4//1.png");
		thumbnail_2 = al_load_bitmap("res//puzzles//4x4//2.png");
		thumbnail_3 = al_load_bitmap("res//puzzles//4x4//3.png");
		thumbnail_4 = al_load_bitmap("res//puzzles//4x4//4.png");
		thumbnail_5 = al_load_bitmap("res//puzzles//4x4//5.png");
		thumbnail_6 = al_load_bitmap("res//puzzles//4x4//6.png");
		break;
	}
	if (!thumbnail_1 || !thumbnail_2 || !thumbnail_3 || !thumbnail_4 || !thumbnail_5 || !thumbnail_6)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load thumbnails.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	button_1.p1_x = button_2.p1_x = 50;
	button_1.p2_x = button_2.p2_x = 250;

	button_3.p1_x = button_4.p1_x = 300;
	button_3.p2_x = button_4.p2_x = 500;

	button_5.p1_x = button_6.p1_x = 550;
	button_5.p2_x = button_6.p2_x = 750;

	button_1.p1_y = button_3.p1_y = button_5.p1_y = 125;
	button_1.p2_y = button_3.p2_y = button_5.p2_y = 325;

	button_2.p1_y = button_4.p1_y = button_6.p1_y = 350;
	button_2.p2_y = button_4.p2_y = button_6.p2_y = 550;
}

bool ChooseImageState::Update(ALLEGRO_EVENT * ev)
{
	if (ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
		cout << "Returning to Main Menu." << endl;
		StateControl::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	/* button presses */
	if (StateControl::GetInstance()->left_mouse_button_released &&
		button_1.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_1.p2_x &&
		button_1.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_1.p2_y)
	{
		cout << "1st image chosen." << endl; PuzzleImage = 1;
		StateControl::GetInstance()->ChangeState(StateControl::GetInstance()->GameMode);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		button_2.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_2.p2_x &&
		button_2.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_2.p2_y)
	{
		cout << "2nd image chosen." << endl; PuzzleImage = 2;
		StateControl::GetInstance()->ChangeState(StateControl::GetInstance()->GameMode);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		button_3.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_3.p2_x &&
		button_3.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_3.p2_y)
	{
		cout << "3rd image chosen." << endl; PuzzleImage = 3;
		StateControl::GetInstance()->ChangeState(StateControl::GetInstance()->GameMode);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		button_4.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_4.p2_x &&
		button_4.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_4.p2_y)
	{
		cout << "4th image chosen." << endl; PuzzleImage = 4;
		StateControl::GetInstance()->ChangeState(StateControl::GetInstance()->GameMode);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		button_5.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_5.p2_x &&
		button_5.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_5.p2_y)
	{
		cout << "5th image chosen." << endl; PuzzleImage = 5;
		StateControl::GetInstance()->ChangeState(StateControl::GetInstance()->GameMode);
		return true;
	}
	else if (StateControl::GetInstance()->left_mouse_button_released &&
		button_6.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_6.p2_x &&
		button_6.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_6.p2_y)
	{
		cout << "6th image chosen." << endl; PuzzleImage = 6;
		StateControl::GetInstance()->ChangeState(StateControl::GetInstance()->GameMode);
		return true;
	}

	return false;
}

void ChooseImageState::Draw()
{
	/* drawing background */
	al_draw_bitmap(screen_bg, 0, 0, NULL);

	/* puzzles thumbnails */
	int thumbnails_size = al_get_bitmap_width(thumbnail_1);
	al_draw_scaled_bitmap(thumbnail_1, 0, 0, thumbnails_size, thumbnails_size, button_1.p1_x, button_1.p1_y, 200, 200, NULL);
	al_draw_scaled_bitmap(thumbnail_2, 0, 0, thumbnails_size, thumbnails_size, button_2.p1_x, button_2.p1_y, 200, 200, NULL);
	al_draw_scaled_bitmap(thumbnail_3, 0, 0, thumbnails_size, thumbnails_size, button_3.p1_x, button_3.p1_y, 200, 200, NULL);
	al_draw_scaled_bitmap(thumbnail_4, 0, 0, thumbnails_size, thumbnails_size, button_4.p1_x, button_4.p1_y, 200, 200, NULL);
	al_draw_scaled_bitmap(thumbnail_5, 0, 0, thumbnails_size, thumbnails_size, button_5.p1_x, button_5.p1_y, 200, 200, NULL);
	al_draw_scaled_bitmap(thumbnail_6, 0, 0, thumbnails_size, thumbnails_size, button_6.p1_x, button_6.p1_y, 200, 200, NULL);

	/* button hovers */
	if (button_1.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_1.p2_x &&
		button_1.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_1.p2_y)
	{
		al_draw_rectangle(button_1.p1_x, button_1.p1_y, button_1.p2_x, button_1.p2_y, Yellow, 1.0);
	}
	else if (button_2.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_2.p2_x &&
		button_2.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_2.p2_y)
	{
		al_draw_rectangle(button_2.p1_x, button_2.p1_y, button_2.p2_x, button_2.p2_y, Yellow, 1.0);
	}
	else if (button_3.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_3.p2_x &&
		button_3.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_3.p2_y)
	{
		al_draw_rectangle(button_3.p1_x, button_3.p1_y, button_3.p2_x, button_3.p2_y, Yellow, 1.0);
	}
	else if (button_4.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_4.p2_x &&
		button_4.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_4.p2_y)
	{
		al_draw_rectangle(button_4.p1_x, button_4.p1_y, button_4.p2_x, button_4.p2_y, Yellow, 1.0);
	}
	else if (button_5.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_5.p2_x &&
		button_5.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_5.p2_y)
	{
		al_draw_rectangle(button_5.p1_x, button_5.p1_y, button_5.p2_x, button_5.p2_y, Yellow, 1.0);
	}
	else if (button_6.p1_x < StateControl::GetInstance()->mouse_x && StateControl::GetInstance()->mouse_x < button_6.p2_x &&
		button_6.p1_y < StateControl::GetInstance()->mouse_y && StateControl::GetInstance()->mouse_y < button_6.p2_y)
	{
		al_draw_rectangle(button_6.p1_x, button_6.p1_y, button_6.p2_x, button_6.p2_y, Yellow, 1.0);
	}
}

void ChooseImageState::Terminate()
{
	al_destroy_bitmap(screen_bg);

	al_destroy_bitmap(thumbnail_1);
	al_destroy_bitmap(thumbnail_2);
	al_destroy_bitmap(thumbnail_3);
	al_destroy_bitmap(thumbnail_4);
	al_destroy_bitmap(thumbnail_5);
	al_destroy_bitmap(thumbnail_6);
}