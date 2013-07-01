#include "TrainingModeState.h"
#include "StateControl.h"

void TrainingModeState::Initialize()
{
	switch (PuzzleSize)
	{
	case 3: screen_bg = al_load_bitmap(GameBoardScreen3x3); break;
	case 4: case 5: screen_bg = al_load_bitmap(GameBoardScreen4x4); break;
	}
	if (!screen_bg)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load background.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	switch (PuzzleSize)
	{
	case 3: board_x = 175; board_y = 75; break;
	case 4: case 5: board_x = 150; board_y = 50; break;
	}

	/* loading puzzle */
	string pic;
	stringstream ss;
	switch (PuzzleSize)
	{
	case 3:
		{
			switch (PuzzleImage)
			{
			default:
			case 1: puzzle = al_load_bitmap("res//puzzles//3x3//1.png"); break;
			case 2: puzzle = al_load_bitmap("res//puzzles//3x3//2.png"); break;
			case 3: puzzle = al_load_bitmap("res//puzzles//3x3//3.png"); break;
			case 4: puzzle = al_load_bitmap("res//puzzles//3x3//4.png"); break;
			case 5: puzzle = al_load_bitmap("res//puzzles//3x3//5.png"); break;
			case 6: puzzle = al_load_bitmap("res//puzzles//3x3//6.png"); break;
			}
			break;
		}
	case 4:
	case 5:
		{
			switch (PuzzleImage)
			{
			default:
			case 1: puzzle = al_load_bitmap("res//puzzles//4x4//1.png"); break;
			case 2: puzzle = al_load_bitmap("res//puzzles//4x4//2.png"); break;
			case 3: puzzle = al_load_bitmap("res//puzzles//4x4//3.png"); break;
			case 4: puzzle = al_load_bitmap("res//puzzles//4x4//4.png"); break;
			case 5: puzzle = al_load_bitmap("res//puzzles//4x4//5.png"); break;
			case 6: puzzle = al_load_bitmap("res//puzzles//4x4//6.png"); break;
			}
			break;
		}
	}
	if (!puzzle)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not puzzle.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	piece_size = al_get_bitmap_height(puzzle) / PuzzleSize;

	peek_original_image = false;
	unsigned int add_to_shuffle_moves = 0;
	piece_is_moving = false;
	current_frame = 0;
	
	/* creating GAME VECTOR on TRAINING mode */
	game_board = create_new_board(PuzzleSize, add_to_shuffle_moves);

	/* creating WIN VECTOR */
	win_vector = start_game_board_vector(PuzzleSize);

	/* getting START TIME */
	start_time = (unsigned int) time (NULL);
}

bool TrainingModeState::Update(ALLEGRO_EVENT * ev)
{
	int blank_x, blank_y;

	/* check if game was won */
	if (!piece_is_moving && game_board == win_vector)
	{
		/* getting END TIME and computing TIME taken */
		end_time = (unsigned int) time (NULL);
		/* total seconds taken */
		elapsed_time = end_time - start_time;
		elapsed_mins = elapsed_time / 60;
		elapsed_secs = elapsed_time % 60;

		stringstream ss;
		ss << "Time taken: " << setfill('0') << setw(2) << elapsed_mins << ":" << setw(2) << elapsed_secs << setfill(' ');
		cout << "Congratulations! " << ss.str() << endl;
		ss << endl << "Do you wish to play again?";
		int dialog_action = al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Congratulations!", "You have solved the puzzle.", ss.str().c_str(), NULL, ALLEGRO_MESSAGEBOX_YES_NO);
		switch (dialog_action)
		{
		case 1:
			cout << "Selected \"Yes\": starting another game." << endl;
			StateControl::GetInstance()->ChangeState(TrainingMode);
			break;
		case 0:
		case 2:
			cout << "Returning to Main Menu." << endl;
			StateControl::GetInstance()->ChangeState(MainMenu);
			break;
		}
		
		return true;
	}

	/* getting BLANK SPACE COORDS */
	bool breaking = false;
	for (unsigned int i = 0; i < game_board.size() && !breaking; i++)
	{
		for (unsigned int j = 0; j < game_board.size(); j++)
		{
			if (game_board[i][j] == 0)
			{ blank_x = j; blank_y = i; breaking = true; break; }
		}
	}
	
	if (StateControl::GetInstance()->right_mouse_button_pressed)
	{
		peek_original_image = true;
		return true;
	}
	else
	{ peek_original_image = false; }

	// analyzes mouse input
	if (StateControl::GetInstance()->left_mouse_button_pressed)
	{
		StateControl::GetInstance()->left_mouse_button_pressed = false;
		mouse_source_x = StateControl::GetInstance()->mouse_x;
		mouse_source_y = StateControl::GetInstance()->mouse_y;

		if ((board_x < mouse_source_x && mouse_source_x < board_x + al_get_bitmap_width(puzzle)) &&
			(board_y < mouse_source_y && mouse_source_y < board_y + al_get_bitmap_width(puzzle)))
		{
			for (int i = 0; i < PuzzleSize; i++)
			{
				for (int j = 0; j < PuzzleSize; j++)
				{
					if (((board_x + (i*piece_size)) < mouse_source_x && mouse_source_x < ((board_x + (i*piece_size)) + piece_size)) &&
						((board_y + (j*piece_size)) < mouse_source_y && mouse_source_y < ((board_y + (j*piece_size)) + piece_size)))
					{
						cout << "Pressed piece number: " << game_board[j][i] << endl;
						piece_to_move = game_board[j][i];
					}
				}
			}
			game_board = move_piece(game_board, piece_to_move);

			return true;
		}
	}

	// analyzes keyboard input
	if (ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
		cout << "You chose to quit." << endl;
		StateControl::GetInstance()->ChangeState(MainMenu);
		return true;
	}
	else if (((ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_W) ||
		(ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_UP))
		&& blank_y != game_board.size() - 1)
	{
		piece_to_move = wasd_search_piece_to_move (game_board, blank_x, blank_y, "up");
		game_board = move_piece (game_board, piece_to_move);
		return true;
	}
	else if (((ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_S) ||
		(ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_DOWN))
		&& blank_y != 0)
	{
		piece_to_move = wasd_search_piece_to_move (game_board, blank_x, blank_y, "down");
		game_board = move_piece (game_board, piece_to_move);
		return true;
	}
	else if (((ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_D) ||
		(ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_RIGHT))
		&& blank_x != 0)
	{
		piece_to_move = wasd_search_piece_to_move (game_board, blank_x, blank_y, "right");
		game_board = move_piece (game_board, piece_to_move);
		return true;
	}
	else if (((ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_A) ||
		(ev->type == ALLEGRO_EVENT_KEY_CHAR && ev->keyboard.keycode == ALLEGRO_KEY_LEFT))
		&& blank_x != game_board.size() - 1)
	{
		piece_to_move = wasd_search_piece_to_move (game_board, blank_x, blank_y, "left");
		game_board = move_piece(game_board, piece_to_move);
		return true;
	}

	return false;
}

void TrainingModeState::Draw()
{
	/* drawing background */
	al_draw_bitmap(screen_bg, 0, 0, NULL);

	int source_x, source_y;
	double framerate = piece_size / 10.0;
	
	/* drawing pieces */
	bool drawing_blank_space;
	for (unsigned int i = 0; i < game_board.size(); i++)
	{
		for (unsigned int j = 0; j < game_board.size(); j++)
		{
			drawing_blank_space = false;

			switch (PuzzleSize)
			{
			case 3:
				switch (game_board[i][j])
				{
				case 0: drawing_blank_space = true; break;
				case 1: source_x = 0;				source_y = 0;				break;
				case 2: source_x = piece_size;		source_y = 0;				break;
				case 3: source_x = 2*piece_size;	source_y = 0;				break;
				case 4: source_x = 0;				source_y = piece_size;		break;
				case 5: source_x = piece_size;		source_y = piece_size;		break;
				case 6: source_x = 2*piece_size;	source_y = piece_size;		break;
				case 7: source_x = 0;				source_y = 2*piece_size;	break;
				case 8: source_x = piece_size;		source_y = 2*piece_size;	break;
				}
				break;
			case 4:
				switch (game_board[i][j])
				{
				case 0: drawing_blank_space = true; break;
				case 1: source_x = 0;				source_y = 0;				break;
				case 2: source_x = piece_size;		source_y = 0;				break;
				case 3: source_x = 2*piece_size;	source_y = 0;				break;
				case 4: source_x = 3*piece_size;	source_y = 0;				break;
				case 5: source_x = 0;				source_y = piece_size;		break;
				case 6: source_x = piece_size;		source_y = piece_size;		break;
				case 7: source_x = 2*piece_size;	source_y = piece_size;		break;
				case 8: source_x = 3*piece_size;	source_y = piece_size;		break;
				case 9: source_x = 0;				source_y = 2*piece_size;	break;
				case 10: source_x = piece_size;		source_y = 2*piece_size;	break;
				case 11: source_x = 2*piece_size;	source_y = 2*piece_size;	break;
				case 12: source_x = 3*piece_size;	source_y = 2*piece_size;	break;
				case 13: source_x = 0;				source_y = 3*piece_size;	break;
				case 14: source_x = piece_size;		source_y = 3*piece_size;	break;
				case 15: source_x = 2*piece_size;	source_y = 3*piece_size;	break;
				}
				break;
			case 5:
				switch (game_board[i][j])
				{
				case 0: drawing_blank_space = true; break;
				case 1: source_x = 0;				source_y = 0;				break;
				case 2: source_x = piece_size;		source_y = 0;				break;
				case 3: source_x = 2*piece_size;	source_y = 0;				break;
				case 4: source_x = 3*piece_size;	source_y = 0;				break;
				case 5: source_x = 4*piece_size;	source_y = 0;				break;
				case 6: source_x = 0;				source_y = piece_size;		break;
				case 7: source_x = piece_size;		source_y = piece_size;		break;
				case 8: source_x = 2*piece_size;	source_y = piece_size;		break;
				case 9: source_x = 3*piece_size;	source_y = piece_size;		break;
				case 10: source_x = 4*piece_size;	source_y = piece_size;		break;
				case 11: source_x = 0;				source_y = 2*piece_size;	break;
				case 12: source_x = piece_size;		source_y = 2*piece_size;	break;
				case 13: source_x = 2*piece_size;	source_y = 2*piece_size;	break;
				case 14: source_x = 3*piece_size;	source_y = 2*piece_size;	break;
				case 15: source_x = 4*piece_size;	source_y = 2*piece_size;	break;
				case 16: source_x = 0;				source_y = 3*piece_size;	break;
				case 17: source_x = piece_size;		source_y = 3*piece_size;	break;
				case 18: source_x = 2*piece_size;	source_y = 3*piece_size;	break;
				case 19: source_x = 3*piece_size;	source_y = 3*piece_size;	break;
				case 20: source_x = 4*piece_size;	source_y = 3*piece_size;	break;
				case 21: source_x = 0;				source_y = 4*piece_size;	break;
				case 22: source_x = piece_size;		source_y = 4*piece_size;	break;
				case 23: source_x = 2*piece_size;	source_y = 4*piece_size;	break;
				case 24: source_x = 3*piece_size;	source_y = 4*piece_size;	break;
				}
				break;
			}
			
			if (!drawing_blank_space)
			{
				if (piece_is_moving && piece_to_move == game_board[i][j])
				{
					switch (direction)
					{
					case up:
						al_draw_bitmap_region(puzzle, source_x, source_y, piece_size, piece_size, board_x + (j*piece_size), board_y + ((i+1) * piece_size) - (current_frame*framerate), NULL);
						current_frame++;
						break;
					case down:
						al_draw_bitmap_region(puzzle, source_x, source_y, piece_size, piece_size, board_x + (j*piece_size), board_y + ((i-1) * piece_size) + (current_frame*framerate), NULL);
						current_frame++;
						break;
					case left:
						al_draw_bitmap_region(puzzle, source_x, source_y, piece_size, piece_size, board_x + ((j+1)*piece_size) - (current_frame*framerate), board_y + (i * piece_size), NULL);
						current_frame++;
						break;
					case right:
						al_draw_bitmap_region(puzzle, source_x, source_y, piece_size, piece_size, board_x + ((j-1)*piece_size) + (current_frame*framerate), board_y + (i * piece_size), NULL);
						current_frame++;
						break;
					}

					if (current_frame == 11)
					{ current_frame = 0; piece_is_moving = false; }
				}
				else
				{
					al_draw_bitmap_region(puzzle, source_x, source_y, piece_size, piece_size, board_x + (j * piece_size), board_y + (i * piece_size), NULL);
				}
			}
		}
	}

	/* drawing original image if right mouse button is pressed */
	if (peek_original_image)
	{ al_draw_bitmap(puzzle, board_x, board_y, NULL); }
}

void TrainingModeState::Terminate()
{
	al_destroy_bitmap(screen_bg);
	al_destroy_bitmap(puzzle);
}

/*
Function: Gets a direction, returns number of piece to move
@params: vector<vector<int> > & game_board, int blank_x, int blank_y, string direction
@return: int piece_to_move
*/
int TrainingModeState::wasd_search_piece_to_move (const vector<vector<int> > & game_board, int blank_x, int blank_y, const string & direction)
{
	int piece_to_move;

	// getting piece to move based on the given direction
	if (direction == "up")
	{ piece_to_move = game_board[blank_y + 1][blank_x]; }
	else if (direction == "right")
	{ piece_to_move = game_board[blank_y][blank_x - 1]; }
	else if (direction == "down")
	{ piece_to_move = game_board[blank_y - 1][blank_x]; }
	else if (direction == "left")
	{ piece_to_move = game_board[blank_y][blank_x + 1]; }

	return piece_to_move;
}

/*
Function: Moves a piece (if possible)
@params: vector<vector<int> > & game_board, int piece
@return: vector<vector<int> > game_board
*/
vector<vector<int> > TrainingModeState::move_piece (vector<vector<int> > & game_board, int piece)
{
	int piece_x, piece_y;
	int blank_x, blank_y;

	// getting piece_to_move coords
	for (unsigned int i = 0; i < game_board.size(); i++)
	{
		for (unsigned int j = 0; j < game_board.size(); j++)
		{
			if (game_board[i][j] == piece)
			{
				piece_x = j;
				piece_y = i;
				break;
			}
		}
	}

	// getting BLANK SPACE COORDS
	for (unsigned int i = 0; i < game_board.size(); i++)
	{
		for (unsigned int j = 0; j < game_board.size(); j++)
		{
			if (game_board[i][j] == 0)
			{
				blank_x = j;
				blank_y = i;
				break;
			}
		}
	}

	// SWITCH PIECE to BLANK SPACE -- !! if possible !!
	if ((piece_x == blank_x && (piece_y == blank_y + 1 || piece_y == blank_y - 1)) ||
		(piece_y == blank_y && (piece_x == blank_x + 1 || piece_x == blank_x - 1)))
	{
		cout << "Moving piece..." << endl;
		piece_is_moving = true;
		if (piece_x == blank_x && piece_y == blank_y + 1)
		{ direction = up; }
		if (piece_x == blank_x && piece_y == blank_y - 1)
		{ direction = down; }
		if (piece_y == blank_y && piece_x == blank_x + 1)
		{ direction = left; }
		if (piece_y == blank_y && piece_x == blank_x - 1)
		{ direction = right; }

		game_board[blank_y][blank_x] = piece;		// putting piece in blank space
		game_board[piece_y][piece_x] = 0;			// putting blank space in piece previous position
	}
	else
	{ cout << "Not possible." << endl; }

	return game_board;
}

/*
Function: creates a solved vector (all values are sorted)
@params: int board_size
@return: vector<vector<int> > sorted_board
*/
vector<vector<int> > TrainingModeState::start_game_board_vector (int board_size)
{
	/* creating vector of vectors */
	vector<vector<int> > sorted_board (board_size, vector<int> (board_size));

	/* n - number to be put to vector */
	int n = 1;

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			/* if we are writing the last position, write 0. This will be useful to easily identify the blank space */
			if (i == board_size - 1 && j == board_size - 1)
			{
				/* 0 == blank space identifier */
				sorted_board[i][j] = 0;
			}
			else
			{

				/* write the value contained in the variable n */
				sorted_board[i][j] = n;

				/* incrementing n */
				n++;
			}
		}
	}

	return sorted_board;
}

/*
Function: creates a GAME_BOARD ready to be solved
@params: int board_size, int add_to_shuffle_moves
@return: vector<vector<int> > game_board
*/
vector<vector<int> > TrainingModeState::create_new_board (int board_size, int add_to_shuffle_moves)
{
	vector<vector<int> > game_board;
	vector<vector<int> > win_board;

	/* creating a solved vector for comparison */
	win_board = start_game_board_vector (board_size);

	/* generating new board while game_board == win_board */
	do { game_board = shuffle_board (start_game_board_vector (board_size), add_to_shuffle_moves); }
	while (game_board == win_board);
	/* we don't want to present the player a puzzle that is already solved, right? */

	return game_board;
}

/*
Function: shuffling a game board vector
@params: vector<vector<int> > & game_board, int add_to_shuffle_moves = 0
@return: vector<vector<int> > game_board
*/
vector<vector<int> > TrainingModeState::shuffle_board (vector<vector<int> > & game_board, int add_to_shuffle_moves = 0)
{
	int blank_x, blank_y;
	int blank_space_move_direction;

	/* shuffle moves - this can become a GLOBAL VARIABLE for the game DIFFICULTY level */
	unsigned int shuffle_moves = 1003;
	shuffle_moves += add_to_shuffle_moves;

	for (unsigned int k = 0; k < shuffle_moves; k++)
	{
		// getting BLANK SPACE COORDS
		for (unsigned int i = 0; i < game_board.size(); i++)
		{
			for (unsigned int j = 0; j < game_board.size(); j++)
			{
				if (game_board[i][j] == 0)
				{
					blank_x = j;
					blank_y = i;
					break;
				}
			}
		}

		/*
		------------------
		DIRECTIONS LEGEND:
		------------------

		1
		/|\
		|
		4 <----|----> 2
		|
		\|/
		3
		*/

		/* ---------------- GETTING A RANDOM DIRECTION ---------------- */
		// (notice it isn't completely randomly)											// BLANK SPACE POSITION:
		if (blank_x == 0 && blank_y == 0)													// top left CORNER
		{
			/* if piece is in the top left corner, it can only move right or down */
			blank_space_move_direction = random_number(2,3);
			/* according to my directions legend, right or down == 2 or 3 */
		}
		else if (blank_x == game_board.size() - 1 && blank_y == 0)							// top right CORNER
		{
			blank_space_move_direction = random_number(3,4);
		}
		else if (blank_x == game_board.size() - 1 && blank_y == game_board.size() - 1)		// bottom right CORNER
		{
			do
			{
				/* if piece is in the top left corner, it can only move up or left */
				blank_space_move_direction = random_number(1,4);
				/* according to my directions legend, right or down == 1 or 4 (excluding 2 or 3) */
			}
			while (blank_space_move_direction == 2 || blank_space_move_direction == 3);
			/* because we are generating random numbers from 1-4 and we don't want 2 neither 3, *
			* we need to repeat this bit of code until the direction is different from 2 and 3 */
		}
		else if (blank_x == 0 && blank_y == game_board.size() - 1)							// bottom left CORNER
		{
			blank_space_move_direction = random_number(1,2);
		}
		else if (blank_y == 0)																// top BAR
		{
			/* blank space can move any direction except upwards (up == 1 in my directions legend) */
			blank_space_move_direction = random_number(2,4);
		}
		else if (blank_x == game_board.size() - 1)											// right BAR
		{
			do
			{
				blank_space_move_direction = random_number(1,4);
			}
			while (blank_space_move_direction == 2);
		}
		else if (blank_y == game_board.size() - 1)											// bottom BAR
		{
			do
			{
				blank_space_move_direction = random_number(1,4);
			}
			while (blank_space_move_direction == 3);
		}
		else if (blank_x == 0)																// left BAR
		{
			blank_space_move_direction = random_number(1,3);
		}
		else																				// the remaining (middle)
		{
			blank_space_move_direction = random_number(1,4);
		}

		/* ---------------- MOVING PIECE TO DIRECTION ---------------- */
		int temp_number;												// MOVING DIRECTION:
		if (blank_space_move_direction == 1)							// UP
		{
			/* temporary saving piece number */
			temp_number = game_board[blank_y - 1][blank_x];

			/* putting blank space in piece previous position */
			game_board[blank_y - 1][blank_x] = 0;
			/* putting piece in blank space */
			game_board[blank_y][blank_x] = temp_number;
		}
		else if (blank_space_move_direction == 2)						// RIGHT
		{
			temp_number = game_board[blank_y][blank_x + 1];

			game_board[blank_y][blank_x + 1] = 0;
			game_board[blank_y][blank_x] = temp_number;
		}
		else if (blank_space_move_direction == 3)						// DOWN
		{
			temp_number = game_board[blank_y + 1][blank_x];

			game_board[blank_y + 1][blank_x] = 0;
			game_board[blank_y][blank_x] = temp_number;
		}
		else if (blank_space_move_direction == 4)						// LEFT
		{
			temp_number = game_board[blank_y][blank_x - 1];

			game_board[blank_y][blank_x - 1] = 0;
			game_board[blank_y][blank_x] = temp_number;
		}
	}

	return game_board;
}