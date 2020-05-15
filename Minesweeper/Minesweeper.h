#pragma once

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include "board.h"
#include <string>

using std::cout;
using std::endl;
using std::cin;

enum MENU { EASY = 1, MEDIUM, HARD, QUIT };

class Minesweeper
{
public:
	Minesweeper() = default;

	static void DisplayMenu();

	static void ProcessMenuChoice(int choice);

	static void ProcessGame(int row, int col, int num_bombs);

	static bool PlayGame(Board & difficulty);

	static void SelectRow(char & row, Board & difficulty);

	static void SelectCol(char & col, int & convert_col, Board & difficulty);

	static void SelectAction(char & action);

	~Minesweeper()
	{
	}
};

#endif