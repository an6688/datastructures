#pragma once
#include "stdafx.h"
#include <iostream>

#ifndef CELL_H
#define CELL_H

using std::cout;

class Cell
{
private:
	bool covered_;
	bool bomb_;
	int  num_bombs_;
	bool flag_;

public:
	Cell() : covered_(true), bomb_(false), num_bombs_(0),
		flag_(false) { }; Cell(const Cell & copy) : covered_(copy.covered_),
		bomb_(copy.bomb_), num_bombs_(copy.num_bombs_), flag_(copy.flag_) { }

	Cell & operator=(const Cell & rhs); 

	void Uncover(); 

	bool IsBomb() const; 

	bool IsFlagged() const; 

	bool IsCovered() const; 

	bool Display() const; 

	void SetFlag(char flag); 

	void SetBomb(); 

	void SetNumBombs(int num); 

	int  GetNumBombs() const; 

	~Cell()
	{
	}
};

inline Cell& Cell::operator=(const Cell& rhs)
{
	covered_ = rhs.covered_;
	bomb_ = rhs.bomb_;
	flag_ = rhs.flag_;
	num_bombs_ = rhs.num_bombs_;

	return *this;
}

inline void Cell::Uncover()
{
	covered_ = false;
}

inline bool Cell::IsBomb() const
{
	bool is_bomb = false;

	if (bomb_ == true)
		is_bomb = true;

	return is_bomb;
}

inline bool Cell::IsFlagged() const
{
	bool is_flagged = false;

	if (flag_ == true)
		is_flagged = true;

	return is_flagged;
}

inline bool Cell::IsCovered() const
{
	bool is_covered = false;

	if (covered_ == true)
		is_covered = true;

	return is_covered;
}

inline bool Cell::Display() const
{
	HANDLE handle = 0;
	const int DEFAULT = 7;
	const int RED = 12;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	bool empty = false;

	if (covered_ == false)
	{

		if (bomb_ == true)
		{
			SetConsoleTextAttribute(handle, RED);
			cout << "X ";
			SetConsoleTextAttribute(handle, DEFAULT);

		}
		else if (num_bombs_ > 0)
		{

			cout << num_bombs_ << ' ';

		}
		else
		{

			cout << ". ";

		}
	}
	else if (flag_ == true)
	{

		cout << "F ";

		empty = true;
	}
	else
	{
		cout << "? ";
		empty = true;
	}
	return empty;
}

inline void Cell::SetFlag(char flag)
{
	if (flag == 'T')
		flag_ = true;
	else
		flag_ = false;
}

inline void Cell::SetBomb()
{
	bomb_ = true;
}

inline void Cell::SetNumBombs(int num)
{
	num_bombs_ = num;
}

inline int Cell::GetNumBombs() const
{
	return num_bombs_;
}

#endif
