#include "stdIncludes.h"
#include "StateControl.h"
#include "FileManager.h"

int main() {
	/* checking if program is running for the first time */
	if (!file_exists(ReadMeTxt)) {
		cout << "First time opening the program." << endl;

		/* making folder */
		/*
		int err = _mkdir("puzzle_data");
		if (err != 0) {
			al_show_native_message_box(NULL, "Critical Error",
					"Ups! What have you done?",
					"Could not find necessary data files.\nPlease delete \"puzzle_data\" folder completely and restart the program.",
					NULL, ALLEGRO_MESSAGEBOX_WARN);
			cout << endl << endl;
			cout
					<< "..:: An error has occured, please delete puzzle_data folder ::.."
					<< endl;
			cout << "Press enter to quit ";
			cin.get();
			exit(-1);
		}
		*/

		/* creating ReadMe.txt */
		/* opening stream */
		ofstream readme_txt(ReadMeTxt);
		readme_txt << "--------------" << endl;
		readme_txt << "Slide Puzzle 2" << endl;
		readme_txt << "--------------" << endl;
		readme_txt << endl;
		readme_txt << "Game created by Henrique Ferrolho." << endl;
		readme_txt << "04-06-2013";
		/* closing stream */
		readme_txt.close();
	}

	StateControl::GetInstance()->start_game();

	return 0;
}
