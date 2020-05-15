#ifndef BOARD_H
#define BOARD_H

#include "Array2D.h"
#include "Cell.h"


using std::cout;
using std::endl;
using std::cin;

class Board
{
private:
	Array2D <Cell> cells_;
	int bombs_;
public:
	Board() : cells_(0, 0), bombs_(0) {};

	Board(int rows, int cols, int bombs) : cells_(rows, cols), bombs_(bombs)
	{ };

	Board(const Board & copy) : cells_(copy.cells_),
		bombs_(copy.bombs_) { };

	Board & operator=(const Board & rhs);
	void SetRows(int rows);

	void SetCols(int cols);

	void SetBombs(int bombs);

	int  GetRows() const;

	int  GetCols() const;

	void SetNumber(int r, int c);

	void PlaceBombs();

	int  DisplayBoard();

	bool ProcessCells(const char r, const char c, char action);

	static int  ConvertCoords(char x);

	void Cascade(int row, int col);

	void UncoverAllCells();

	static bool IsLoss(Cell cell);

	~Board()
	{
	}
};

inline Board& Board::operator=(const Board& rhs)
{

	if (this != &rhs)
	{
		cells_ = rhs.cells_;
		bombs_ = rhs.bombs_;
	}
	return *this;
}

inline void Board::SetRows(int rows)
{
	cells_.SetRow(rows);
}

inline void Board::SetCols(int cols)
{
	cells_.SetColumn(cols);
}

inline void Board::SetBombs(int bombs)
{
	bombs_ = bombs;
}

inline int Board::GetRows() const
{
	return cells_.GetRow();
}

inline int Board::GetCols() const
{
	return cells_.GetColumn();
}

inline void Board::SetNumber(int r, int c)
{
	try
	{
		if (c < (cells_.GetColumn() - 1) &&
			cells_[r][c + 1].IsBomb() == false)
		{
			cells_[r][c + 1].SetNumBombs(cells_[r][c + 1].GetNumBombs() + 1);
		}

		if (r > 0 && c < (cells_.GetColumn() - 1) &&
			cells_[r - 1][c + 1].IsBomb() == false)
		{
			cells_[r - 1][c + 1].SetNumBombs(cells_[r - 1][c + 1].GetNumBombs() + 1);
		}

		if (r > 0 && cells_[r - 1][c].IsBomb() == false)
			cells_[r - 1][c].SetNumBombs(cells_[r - 1][c].GetNumBombs() + 1);


		if (r > 0 && c > 0 && cells_[r - 1][c - 1].IsBomb() == false)
			cells_[r - 1][c - 1].SetNumBombs(cells_[r - 1][c - 1].GetNumBombs() + 1);

		if (c > 0 && cells_[r][c - 1].IsBomb() == false)
			cells_[r][c - 1].SetNumBombs(cells_[r][c - 1].GetNumBombs() + 1);


		if (r < (cells_.GetRow() - 1) && c > 0 &&
			cells_[r + 1][c - 1].IsBomb() == false)
		{
			cells_[r + 1][c - 1].SetNumBombs(cells_[r + 1][c - 1].GetNumBombs() + 1);
		}

		if (r < (cells_.GetRow() - 1) &&
			cells_[r + 1][c].IsBomb() == false)
		{
			cells_[r + 1][c].SetNumBombs(cells_[r + 1][c].GetNumBombs() + 1);
		}

		if (r < (cells_.GetRow() - 1) && c < (cells_.GetColumn() - 1) &&
			cells_[r + 1][c + 1].IsBomb() == false)
		{
			cells_[r + 1][c + 1].SetNumBombs(cells_[r + 1][c + 1].GetNumBombs() + 1);
		}
	}
	catch (std::out_of_range e)
	{
		throw AdtException(e.what());
	}
}

inline void Board::PlaceBombs()
{
	srand((NULL));

	int row_bomb = 0;
	int col_bomb = 0;
	int num = 0;

	try
	{
		for (int i = 0; i < bombs_; ++i)
		{
			row_bomb = rand() % cells_.GetRow();
			col_bomb = rand() % cells_.GetColumn();

			if (cells_[row_bomb][col_bomb].IsBomb() == false)
			{
				cells_[row_bomb][col_bomb].SetBomb();
				SetNumber(row_bomb, col_bomb);
			}
			else
				i--;
		}
	}
	catch (std::out_of_range e)
	{
		throw AdtException(e.what());
	}
}

inline int Board::DisplayBoard()
{
	system("cls");

	int  num_covered = 0;

	cout << "   ";

	for (int i = 0; i < cells_.GetColumn(); i++)
	{
		if ((65 + i) < 91)
		{

			cout << static_cast<char>(65 + i) << ' ';

		}
		else
		{
			cout << (i - 25) << ' ';

		}
	}

	cout << endl;

	for (int r = 0; r < cells_.GetRow(); r++)
	{
		cout << '\n' << static_cast<char>(65 + r) << "  ";

		for (int c = 0; c < cells_.GetColumn(); c++)
		{
			if (cells_[r][c].Display())
				num_covered++;
		}
	}

	cout << "\n\nNumber still covered: " << num_covered << endl;

	return num_covered;
}

inline bool Board::ProcessCells(const char r, const char c, char action)
{
	int rows = 0;
	int cols = 0;

	rows = ConvertCoords(toupper(r));
	cols = ConvertCoords(toupper(c));

	try
	{
		if (toupper(action) == 'U')
			Cascade(rows, cols);
		else
		{
			if (cells_[rows][cols].IsFlagged())
				cells_[rows][cols].SetFlag('F');
			else
				cells_[rows][cols].SetFlag('T');
		}
	}
	catch (std::out_of_range e)
	{
		throw AdtException(e.what());
	}

	if (IsLoss(cells_[rows][cols]))
		UncoverAllCells();

	return IsLoss(cells_[rows][cols]);
}

inline int Board::ConvertCoords(char x)
{
	int num = 0;

	if (isalpha(x))
		num = static_cast<int>(x) - 65;
	else
		num = static_cast<int>(x) - 23;

	return num;
}

inline void Board::Cascade(int row, int col)
{
	if (cells_[row][col].IsCovered())
	{
		if (cells_[row][col].GetNumBombs() > 0)
			cells_[row][col].Uncover();
		else if (cells_[row][col].GetNumBombs() == 0)
		{
			cells_[row][col].Uncover();

			if (row > 0)
				Cascade(row - 1, col);

			if (row > 0 && col < (cells_.GetColumn() - 1))
				Cascade(row - 1, col + 1);

			if (col < (cells_.GetColumn()) - 1)
				Cascade(row, col + 1);

			if (row < (cells_.GetRow() - 1) && col < (cells_.GetColumn() - 1))
				Cascade(row + 1, col + 1);

			if (row < (cells_.GetRow() - 1))
				Cascade(row + 1, col);

			if (row < (cells_.GetRow() - 1) && col > 0)
				Cascade(row + 1, col - 1);

			if (col > 0)
				Cascade(row, col - 1);

			if (col > 0 && row > 0)
				Cascade(row - 1, col - 1);
		}
	}
}

inline void Board::UncoverAllCells()
{
	for (int i = 0; i < cells_.GetRow(); i++)
	{
		for (int j = 0; j < cells_.GetColumn(); j++)
		{
			cells_[i][j].Uncover();
		}
	}
}

inline bool Board::IsLoss(Cell cell)
{
	bool lose = false;

	if (cell.IsBomb() && cell.IsCovered() == false)
		lose = true;

	return lose;
}

#endif
