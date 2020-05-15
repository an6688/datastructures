// minesweeptest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <crtdbg.h> 
#define  _CRTDBG_MAP_ALLOC
#include "Minesweeper.h"

int main()
{
	Minesweeper game;

	game.DisplayMenu();
	_CrtDumpMemoryLeaks();
	return 0;
}

void Minesweeper::DisplayMenu()
{
	HANDLE handle = 0;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	const int DEFAULT = 7;
	const int YELLOW = 14;
	const int GREEN = 10;

	Board game;
	int choice = 0;

	do
	{
		system("cls");
		SetConsoleTextAttribute(handle, GREEN);

		cout << "*****WELCOME TO MINESWEEPER*****" << endl;
		SetConsoleTextAttribute(handle, DEFAULT);

		cout << "\nPlease choose a difficulty:"
			<< "\n\n1) Child's play (10x10, 10 mines)"
			<< "\n2) Mediocre (16x16, 40 mines)"
			<< "\n3) Brutal (16x30, 100 mines)"
			<< "\n4) Quit game";

		SetConsoleTextAttribute(handle, YELLOW);
		cout << "\n\nPlease select an option: ";
		SetConsoleTextAttribute(handle, DEFAULT);
		cin >> choice;
		cin.ignore();
		cin.clear();

		ProcessMenuChoice(choice);

	} while (choice != 4);
}

void Minesweeper::ProcessMenuChoice(int choice)
{
	switch (choice)
	{
	case EASY:
	{
		ProcessGame(10, 10, 10);
		break;
	}
	case MEDIUM:
	{
		ProcessGame(16, 16, 40);
		break;
	}
	case HARD:
	{
		ProcessGame(16, 30, 100);
		break;
	}
	case QUIT:
	{
		break;
	}
	default:
	{
		cout << "Invalid entry, please try again!\n";
		system("pause");
	}
	}
}

void Minesweeper::ProcessGame(int row, int col, int num_bombs)
{

	bool loss = false;
	int  num_covered = 0;

	Board game(row, col, num_bombs);
	game.PlaceBombs();
	game.DisplayBoard();

	while (loss == false && num_covered != num_bombs)
	{
		loss = PlayGame(game);
		num_covered = game.DisplayBoard();
	}

	if (loss == true)
		cout << "\n\nOuch! you've hit a bomb.\n" << endl;

	if (num_covered == num_bombs)
		cout << "\n\nCongratulations! You won!\n" << endl;

	system("pause");
}

bool Minesweeper::PlayGame(Board& difficulty)
{
	char row = '\0';
	char col = '\0';
	char action = '\0';
	int  convert_col = 0;

	SelectRow(row, difficulty);
	SelectCol(col, convert_col, difficulty);
	SelectAction(action);

	return difficulty.ProcessCells(row, col, action);
}

void Minesweeper::SelectRow(char& row, Board& difficulty)
{
	do
	{
		cout << "Select row: ";
		cin >> row;
		cin.ignore();
		cin.clear();

		if ((static_cast<int>(toupper(row)) - 65) < 0 ||
			(static_cast<int>(toupper(row)) - 65) > difficulty.GetRows())
		{
			cout << "Invalid entry, please enter row!\n" << endl;
		}

	} while ((static_cast<int>(toupper(row)) - 65) < 0 ||
		(toupper(static_cast<int>(toupper(row)) - 65)) > difficulty.GetRows());
}

void Minesweeper::SelectCol(char& col, int& convert_col, Board& difficulty)
{
	do
	{
		cout << "Select column: ";
		cin >> col;
		cin.ignore();
		cin.clear();

		if (isalpha(col))
			convert_col = static_cast<int>(toupper(col)) - 65;
		else
			convert_col = static_cast<int>(toupper(col)) - 23;

		if (convert_col < 0 || convert_col > difficulty.GetCols())
			cout << "\nInvalid entry, please enter column!\n" << endl;

	} while (convert_col < 0 || convert_col > difficulty.GetCols());
}

void Minesweeper::SelectAction(char& action)
{
	do
	{
		cout << "\nWhat do you want to do?"
			<< "\nU) Uncover square"
			<< "\nF) Place Flag"
			<< "\n\nPlease pick: ";
		cin >> action;
		cin.ignore();
		cin.clear();

		if (toupper(action) != 'U' &&
			toupper(action) != 'F')
		{
			cout << "\nInvalid entry, please input U or F\n" << endl;
		}

	} while (toupper(action) != 'U' &&
		toupper(action) != 'F');
}
