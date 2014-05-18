#include "FileManager.h"

bool file_exists(const string & filename) {
	/* trying to open input file stream */
	ifstream infile(filename.c_str());

	return infile.good();
}

int char_to_int(char character) {
	return atoi(char_to_string(character).c_str());
}

string int_to_string(int num) {
	/* create a stringstream */
	stringstream ss;

	/* add number to the stream */
	ss << num;

	/* return a string with the contents of the stream */
	return ss.str();
}

string char_to_string(char character) {
	stringstream ss;
	ss << character;
	return ss.str();
}

/*
 Function: Returns game_board as a string ready to write to a text file
 @params: vector game_board;
 @return: string game_board;
 */
string write_board_to_txt(const vector<vector<int> > & game_board) {
	string board_string = "";
	for (unsigned int i = 0; i < game_board.size(); i++) {
		for (unsigned int j = 0; j < game_board.size(); j++) {
			/* converting piece number to a string */
			string temp = int_to_string(game_board[i][j]);

			/* write ' ' if value == 0 (blank space) */
			if (game_board[i][j] == 0) {
				temp = " ";
			}

			/* formatting the values to write them to text */
			if (game_board.size() < 4)					// piece width == 2
					{
				if (temp.size() == 1) {
					stringstream ss;
					ss << board_string << " " << temp;
					board_string = ss.str();
				}
			} else if (game_board.size() < 11)			// piece width == 3
					{
				if (temp.size() == 1) {
					stringstream ss;
					ss << board_string << "  " << temp;
					board_string = ss.str();
				} else if (temp.size() == 2) {
					stringstream ss;
					ss << board_string << " " << temp;
					board_string = ss.str();
				}
			} else										// piece width == 4
			{
				if (temp.size() == 1) {
					stringstream ss;
					ss << board_string << "   " << temp;
					board_string = ss.str();
				} else if (temp.size() == 2) {
					stringstream ss;
					ss << board_string << "  " << temp;
					board_string = ss.str();
				} else if (temp.size() == 3) {
					stringstream ss;
					ss << board_string << " " << temp;
					board_string = ss.str();
				}
			}
		}

		board_string = board_string + "\n";
	}
	return board_string;
}

/*
 Function: gets SSS in a the form of a string, already formatted
 @params: int board size, bool decrementSSS_enable
 @return: string SSS
 */
string compute_SSS(int board_size, bool decrementSSS_enable) {
	string SSS;
	int SSS_int;

	/* if file exists, compute SSS. else, return "001" */
	if (file_exists(puzzle_numbers_txt)) {
		/* opening input file stream */
		ifstream readfrom_puzzlenumbers(puzzle_numbers_txt);

		/* looking for correct dimension record until 'end of file' */
		char first_num_chr, second_num_chr;
		int first_num, second_num, num;
		string line;
		do {
			/* reading a line from the text file and saving it to a string */
			getline(readfrom_puzzlenumbers, line);

			/* getting first char from the string */
			first_num_chr = line[0];
			/* converting the char to an int */
			first_num = char_to_int(first_num_chr);

			/* getting second char from the string */
			second_num_chr = line[1];
			/* converting the char to an int */
			second_num = char_to_int(second_num_chr);

			/* if size is in the form of NxN */
			if (board_size < 9) {
				/* if there is a match == correct line was found */
				if (first_num == board_size) {
					int c = 4;
					SSS = "";

					/* reading SSS while we don't reach the end of the string ('/0') */
					while (true) {
						SSS = SSS + line[c];
						if (line[c + 1] != '\0') {
							c++;
						} else {
							break;
						}
					}

					/* string to int */
					SSS_int = atoi(SSS.c_str());
					/* if decrementSSS flag is disabled, increment SSS */
					if (decrementSSS_enable == false) {
						SSS_int++;
					}
					/* int to string */
					SSS = int_to_string(SSS_int);

					/* formatting SSS string */
					if (SSS.size() < 2) {
						stringstream ss;
						ss << "00" << SSS;
						return ss.str();
					} else if (SSS.size() < 3) {
						stringstream ss;
						ss << "0" << SSS;
						return ss.str();
					} else {
						return SSS;
					}
				}
			}
			/* else, size is in the form of NNxNN */
			else {
				/* getting correct number from read chars */
				num = (first_num * 10) + second_num;

				/* if there is a match == correct line was found */
				if (num == board_size) {
					int c = 6;
					SSS = "";

					while (true) {
						SSS = SSS + line[c];
						if (line[c + 1] != '\0') {
							c++;
						} else {
							break;
						}
					}

					SSS_int = atoi(SSS.c_str());
					if (decrementSSS_enable == false) {
						SSS_int++;
					}
					SSS = int_to_string(SSS_int);

					if (SSS.size() < 2) {
						stringstream ss;
						ss << "00" << SSS;
						return ss.str();
					} else if (SSS.size() < 3) {
						stringstream ss;
						ss << "0" << SSS;
						return ss.str();
					} else {
						return SSS;
					}
				}
			}
		} while (!readfrom_puzzlenumbers.eof());
		return "001";
	} else {
		return "001";
	}
}

/*
 Function: transfers puzzle_numbers.txt to a vector
 @params: <none>
 @return: vector<vector<int> > vec
 */
vector<vector<int> > puzzle_numbers_txt_to_vec() {
	/* declaring vector to return and a temporary vector */
	vector<vector<int> > vec;
	vector<int> temp(2);

	/* opening input file stream */
	ifstream readfrom_puzzlenumbers(puzzle_numbers_txt);

	int dimension, dimension_pt2, SSS;
	string line;
	string dimension_str, SSS_str;
	char space, next_char;

	/* read line from text file and put it to a string */
	getline(readfrom_puzzlenumbers, line);
	while (true) {
		/* reading puzzle dimension */
		dimension = line[0];
		dimension_pt2 = line[1];
		/* if NxN */
		if (dimension_pt2 == 'x') {
			/* converting to int */
			dimension = char_to_int(dimension);
		}
		/* else, NNxNN */
		else {
			/* concatenating chars */
			dimension_str = dimension + dimension_pt2;
			/* converting to int */
			dimension = atoi(dimension_str.c_str());
		}

		/* reading SSS */
		int i = 2;
		/* reading and ignoring until a space is found */
		do {
			space = line[i];
			i++;
		} while (space != ' ');

		SSS_str = "";
		next_char = line[i];
		/* while the end of string ('/0') isn't found, read SSS */
		while (next_char != '\0') {
			SSS_str = SSS_str + next_char;
			i++;
			next_char = line[i];
		}
		/* converting to int */
		SSS = atoi(SSS_str.c_str());

		/* creating temp vector */
		temp[0] = dimension;
		temp[1] = SSS;

		/* pushing back to return vector */
		vec.push_back(temp);

		getline(readfrom_puzzlenumbers, line);
		if (line[0] == '\0') {
			/* end loop */
			break;
		}
	}
	return vec;
}

/*
 Function: Updates puzzle_numbers.txt values
 @params: int NxN, int SSS
 @return: <void>
 */
void update_puzzlenumbers(int NxN) {
	/* getting .txt current data */
	vector<vector<int> > vec_to_write = puzzle_numbers_txt_to_vec();
	vector<vector<int> > inverted_vec = vec_to_write;
	vector<vector<int> > new_vec;
	bool replaced = false;

	/* inverting the vec order, this is needed to compare and correctly sort the top 10 players */
	for (unsigned int i = 0; i < vec_to_write.size(); i++) {
		inverted_vec[vec_to_write.size() - 1 - i] = vec_to_write[i];
	}
	vec_to_write = inverted_vec;

	/* updating vec */
	for (unsigned int i = 0; i < vec_to_write.size(); i++) {
		if (vec_to_write[i][0] == NxN) {
			vec_to_write[i][1]++;
			replaced = true;
		}
	}

	/* if line didn't exist, adding entry to vec */
	if (replaced == false) {
		for (unsigned int i = 0; i < vec_to_write.size(); i++) {
			if ((NxN > vec_to_write[i][0]) && (replaced == false)) {
				vector<int> temp;
				temp.push_back(NxN);
				temp.push_back(1);

				new_vec.push_back(temp);

				replaced = true;
			}
			new_vec.push_back(vec_to_write[i]);
		}
		vec_to_write = new_vec;
	}

	/* opening output file strem (puzzle_numbers.txt) */
	ofstream writeto_puzzlenumbers(puzzle_numbers_txt);

	int pos;
	for (unsigned int i = 0; i < vec_to_write.size(); i++) {
		/* rewriting the file with updated data */
		pos = vec_to_write.size() - 1 - i;
		writeto_puzzlenumbers << vec_to_write[pos][0] << "x"
				<< vec_to_write[pos][0] << " " << vec_to_write[pos][1] << '\n';
	}

	/* closing output file strem (puzzle_numbers.txt) */
	writeto_puzzlenumbers.close();
}

/*
 Function: Reads board from text file
 @params: int board size, int puzzle number
 @return: vector game_board
 */
vector<vector<int> > read_board_from_txt(int board_size, int puzzle_number) {
	vector<vector<int> > vec(board_size, vector<int>(board_size));
	string line, N, NxN, SSS, filename, num_str;
	char space, num1, num2, num3;
	int num, piece_width;

	/* getting piece width */
	if (board_size < 4) {
		piece_width = 2;
	} else if (board_size < 11) {
		piece_width = 3;
	} else {
		piece_width = 4;
	}

	/* formatting SSS string */
	N = int_to_string(board_size);
	NxN = N + "x" + N;
	SSS = int_to_string(puzzle_number);
	if (SSS.size() == 1) {
		SSS = "00" + SSS;
	} else if (SSS.length() == 2) {
		SSS = "0" + SSS;
	}

	/* assigning correct filename */
	filename = "puzzle_" + NxN + "_" + SSS + ".txt";
	/* now that we have the correct filename, we can open it and read the board it stores */

	/* if file exists */
	if (file_exists(filename)) {
		/* opening input file stream */
		ifstream read_from_txt(filename.c_str());

		int k;
		for (int i = 0; i < board_size; i++) {
			/* reading first line of the file */
			getline(read_from_txt, line);
			k = 0;

			/* reading each value contained in the string */
			for (int j = 0; j < board_size; j++) {
				space = line[k];
				k++;
				if (piece_width == 2) {
					num1 = line[k];
					if (num1 == ' ') {
						num1 = '0';
					}

					num_str = num1;
				} else if (piece_width == 3) {
					num1 = line[k];
					if (num1 == ' ') {
						num1 = '0';
					}
					k++;
					num2 = line[k];
					if (num2 == ' ') {
						num2 = '0';
					}

					num_str = char_to_string(num1) + char_to_string(num2);
				} else if (piece_width == 4) {
					num1 = line[k];
					if (num1 == ' ') {
						num1 = '0';
					}
					k++;
					num2 = line[k];
					if (num2 == ' ') {
						num2 = '0';
					}
					k++;
					num3 = line[k];
					if (num3 == ' ') {
						num3 = '0';
					}

					num_str = char_to_string(num1) + char_to_string(num2)
							+ char_to_string(num3);
				}

				num = atoi(num_str.c_str());
				vec[i][j] = num;
				k++;
			}
		}
	} else {
		cout << "Error: Couldn't open file (" << filename << ").";
	}

	return vec;
}

/*
 Function: Reads top 10 from text file
 @params: int board size, int puzzle number
 @return: vector top_ten
 */
vector<string> read_top_ten_from_txt(int board_size, int puzzle_number) {
	vector<string> top_ten;
	string line, N, NxN, SSS, filename, num_str;

	/* formatting SSS string */
	N = int_to_string(board_size);
	NxN = N + "x" + N;
	SSS = int_to_string(puzzle_number);
	if (SSS.size() == 1) {
		SSS = "00" + SSS;
	} else if (SSS.length() == 2) {
		SSS = "0" + SSS;
	}

	/* assigning correct filename */
	filename = "puzzle_" + NxN + "_" + SSS + ".txt";

	/* if file exists, read top 10 from it */
	if (file_exists(filename)) {
		/* opening input file stream */
		ifstream read_from_txt(filename.c_str());

		for (int i = 0; i < board_size + 1; i++) {
			getline(read_from_txt, line);
		}
		while (true) {
			getline(read_from_txt, line);
			if (line[0] == '\0') {
				break;
			}
			top_ten.push_back(line);
		}
	} else {
		cout << "Error: Couldn't open file (" << filename << ").";
	}

	return top_ten;
}

/*
 Function: Updates specified file top 10
 @params: 1) string filename; 2) vec new_top_ten
 @return: <void>
 */
void update_file_top_ten(int board_size, int puzzle_number,
		const string & filename, const vector<string> & new_top_ten) {
	/* getting board from text file and saving it so we can write it again after we update the top 10 */
	vector<vector<int> > game_board = read_board_from_txt(board_size,
			puzzle_number);

	/* opening output file stream (deleting all its previous content) */
	ofstream write_to_file(filename.c_str());

	/* rewriting the board that was stored on the file */
	write_to_file << write_board_to_txt(game_board) << "\n";

	/* we want a top 10! even if the list is bigger than 10, the limit needs to be less or equal to 10! */
	unsigned int limit = new_top_ten.size();
	if (limit > 10) {
		limit = 10;
	}

	/* actually writing the updated top 10 players to the output file */
	for (unsigned int i = 0; i < limit; i++) {
		write_to_file << new_top_ten[i] << endl;
	}
}
