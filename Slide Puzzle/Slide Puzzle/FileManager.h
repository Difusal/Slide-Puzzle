#pragma once

#include "stdIncludes.h"

bool file_exists (const string & filename);
int char_to_int (char character);
string int_to_string (int num);
string char_to_string (char character);

string write_board_to_txt (const vector<vector<int> > & game_board);
string compute_SSS (int board_size, bool decrementSSS_enable);
vector<vector<int> > puzzle_numbers_txt_to_vec ();
void update_puzzlenumbers (int NxN);
vector<vector<int> > read_board_from_txt (int board_size, int puzzle_number);
vector<string> read_top_ten_from_txt (int board_size, int puzzle_number);
void update_file_top_ten (int board_size, int puzzle_number, const string & filename, const vector<string> & new_top_ten);