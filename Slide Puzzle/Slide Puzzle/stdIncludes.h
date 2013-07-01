#pragma once

/* allegro includes */
#include "allegro5\allegro.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"

/* necessary includes */
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <direct.h>

using namespace std;

/* global variables */
#define ScreenWidth 800
#define ScreenHeight 600
const float FPS = 90.0;

/* defining user-friendly color names */
#define Black al_map_rgb(0, 0, 0)
#define DarkGray al_map_rgb(70, 70, 70)
#define LightGray al_map_rgb(110, 110, 110)
#define DarkBlue al_map_rgb(0, 0, 150)
#define Blue al_map_rgb(0, 0, 255)
#define DarkGreen al_map_rgb(0, 200, 0)
#define Green al_map_rgb(0, 255, 0)
#define LightBlue al_map_rgb(14, 108, 150)
#define DarkRed al_map_rgb(200, 0, 0)
#define Red al_map_rgb(255, 0, 0)
#define Yellow al_map_rgb(255, 255, 0)
#define White al_map_rgb(255, 255, 255)

#define UP_ARROW 72
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define LEFT_ARROW 75

/* file paths */
#define ReadMeTxt "puzzle_data//ReadMe.txt"
#define puzzle_numbers_txt "puzzle_numbers.txt"

/* images */
#define BackgroundScreen "res//images//background.png"
#define MainMenuScreen "res//images//main_menu.png"
#define InstructionsScreen "res//images//instructions.png"
#define ChooseSizeScreen "res//images//choose_size.png"
#define ChooseImageScreen "res//images//choose_image.png"
#define GameBoardScreen3x3 "res//images//game_board_3x3.png"
#define GameBoardScreen4x4 "res//images//game_board_4x4.png"

/* fonts */
#define ConsolaTTF "res//fonts//consola.ttf"

struct Button
{
	int p1_x;
	int p1_y;
	int p2_x;
	int p2_y;
};

typedef unsigned int _IDNum;
typedef vector<_IDNum> _List;
typedef vector<vector<_IDNum> > _UserPlaylist;