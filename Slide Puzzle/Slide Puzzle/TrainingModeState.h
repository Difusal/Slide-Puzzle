#pragma once

#include "stdIncludes.h"
#include "State.h"

class TrainingModeState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

	int wasd_search_piece_to_move (const vector<vector<int> > & game_board, int blank_x, int blank_y, const string & direction);
	vector<vector<int> > move_piece (vector<vector<int> > & game_board, int piece);
	vector<vector<int> > start_game_board_vector (int board_size);
	vector<vector<int> > create_new_board (int board_size, int add_to_shuffle_moves);
	vector<vector<int> > shuffle_board (vector<vector<int> > & game_board, int add_to_shuffle_moves);

private:
	vector<vector<int> > win_vector;
	vector<vector<int> > game_board;
	
	int piece_size;
	int board_x, board_y;
	int start_time, end_time, elapsed_time;
	int elapsed_mins, elapsed_secs;
	
	int mouse_source_x, mouse_source_y;
	bool peek_original_image;

	int piece_to_move;
	bool piece_is_moving;
	enum Direction { up, down, left, right};
	Direction direction;
	int current_frame;
	
	ALLEGRO_BITMAP * screen_bg;
	ALLEGRO_BITMAP * puzzle;
};