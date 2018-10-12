#include "pch.h"
#include "Mine.h"
using namespace std;

Mine::Mine()
{
	Status = 0;
	MineMark = false;
	MineAround = 0;
}

Mine& Mine::PutMine() 
{
	MineMark = true;
	return *this;
}

Mine& Mine::AreaStatusChange(int Choice)
{
	Status = Choice;
	return *this;
}

Mine& Mine::Count(bool Mi) 
{
	if (Mi)
		++MineAround;
	return *this;
}

bool Mine::CheckMine()
{
	if (MineMark)
		return true;
	else
		return false;
}

bool Mine::CheckVoid()
{
	if ((!MineMark) && MineAround == 0)
		return true;
	return false;
}

int Mine::CheckStatus()
{
	return Status;
}

void Mine::Output(bool Ans) {
	if (!Ans) {
		if (Status == 1)
			cout << " ? ";
		else if (Status == 2)
			cout << " " << setw(2) << setiosflags(ios::left) << MineAround;
		else
			cout << " ■";
	}
	else
	{
		if (MineMark)
			cout << " M ";
		else
			cout << " " << setw(2) << setiosflags(ios::left) << MineAround;
	}
}


/*choice:1 open, 2 mark ?, 3 remove mark?*/
int Mine::MineClearance(int Choice)
{
	if (Choice == 0)
	{
		if (MineMark == true) {
			cout << "GAME OVER" << endl;
			cout << "restart?(Y:0)" << endl;
			int Ch;
			cin >> Ch;
			rewind(stdin);
			if (Ch == 0)
				return 0;//restart game
			else
				return 1;//end the game
		}
		else {
			AreaStatusChange(2);
			if(!CheckVoid())
				return 2;//a safe area
			return 3;//need to scan void area nearby
		}
	}
	if (Choice == 1)
	{
		AreaStatusChange(1);
			return 2;
	}
	if (Choice == 2)
	{
		if (Status == 1) 
		{
			AreaStatusChange(0);
			return 2;
		}
	}
	cout << "Input Error,Please Reinput" << endl;
	return 4;//wrong input and need to reinput
}

void StartGame(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High,
	int MineNum) {
	int RanX, RanY;
	int Set = 0;
	while (Set < MineNum) {
		RanX = rand() % Length;
		RanY = rand() % High;
		if (!Map[RanY][RanX].CheckMine()) {
			Map[RanY][RanX].PutMine();
			++Set;
		}
	}
	for (int y = 0; y < High; ++y)
	{
		for (int x = 0; x < Length; ++x)
		{
			if (x - 1 >= 0 && y - 1 >= 0)
				Map[y][x].Count(Map[y - 1][x - 1].CheckMine());
			if (y - 1 >= 0 && x + 1 < Length)
				Map[y][x].Count(Map[y - 1][x + 1].CheckMine());
			if (x - 1 >= 0 && y + 1 < High)
				Map[y][x].Count(Map[y + 1][x - 1].CheckMine());
			if (x + 1 < Length && y + 1 < High)
				Map[y][x].Count(Map[y + 1][x + 1].CheckMine());

			if (x - 1 >= 0)
				Map[y][x].Count(Map[y][x - 1].CheckMine());
			if (y - 1 >= 0)
				Map[y][x].Count(Map[y - 1][x].CheckMine());
			if (y + 1 < High)
				Map[y][x].Count(Map[y + 1][x].CheckMine());
			if (x + 1 < Length)
				Map[y][x].Count(Map[y][x + 1].CheckMine());
		}
	}
}

void DrawMap(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High, bool EndofGame) {
	cout << "   ";
	for (int x = 0; x < Length; ++x) {
		cout << " " << setw(2) << setiosflags(ios::left) << x;
	}
	cout << endl;
	for (int y = 0; y < High; ++y) {
		cout << setw(3) << setiosflags(ios::left) << y;
		for (int x = 0; x < Length; ++x) {
			Map[y][x].Output(EndofGame);
		}
		cout << endl;
	}
}

bool MarkHereWhenSurronded(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High,
	int Xinput, int Yinput) {
	if (Map[Yinput][Xinput].CheckMine()) {
		if (Xinput - 1 >= 0 && Yinput - 1 >= 0)
		{

			if (!(Map[Yinput - 1][Xinput - 1].CheckStatus() == 2 ||
				Map[Yinput - 1][Xinput - 1].CheckStatus() == 1))
				return false;

		}
		if (Yinput - 1 >= 0 && Xinput + 1 < Length)
		{
			if (!(Map[Yinput - 1][Xinput + 1].CheckStatus() == 2 ||
				Map[Yinput - 1][Xinput + 1].CheckStatus() == 1))
				return false;
 
		}
		if (Xinput - 1 >= 0 && Yinput + 1 < High)
		{
			if (!(Map[Yinput + 1][Xinput - 1].CheckStatus() == 2 ||
				Map[Yinput + 1][Xinput - 1].CheckStatus() == 1))
				return false;

		}
		if (Xinput + 1 < Length && Yinput + 1 < High)
		{
			if (!(Map[Yinput + 1][Xinput + 1].CheckStatus() == 2 ||
				Map[Yinput + 1][Xinput + 1].CheckStatus() == 1))
				return false;

		}

		if (Xinput - 1 >= 0)
		{
			if (Map[Yinput][Xinput - 1].CheckMine() &&
				Map[Yinput][Xinput - 1].CheckStatus() != 3)
				if (!MarkHereWhenSurronded(Map, Length, High, Xinput - 1, Yinput))
					return false;
			if (!(Map[Yinput][Xinput - 1].CheckStatus() == 2 ||
				Map[Yinput][Xinput - 1].CheckStatus() == 1))
				return false;

		}
		if (Yinput - 1 >= 0)
		{
			if (Map[Yinput - 1][Xinput].CheckMine() &&
				Map[Yinput - 1][Xinput].CheckStatus() != 3)
				if (!MarkHereWhenSurronded(Map, Length, High, Xinput, Yinput - 1))
					return false;
			if (!(Map[Yinput - 1][Xinput].CheckStatus() == 2 ||
				Map[Yinput - 1][Xinput].CheckStatus() == 1))
				return false;

		}
		if (Yinput + 1 < High)
		{
			if (Map[Yinput + 1][Xinput].CheckMine() &&
				Map[Yinput + 1][Xinput].CheckStatus() != 3)
				if (!MarkHereWhenSurronded(Map, Length, High, Xinput, Yinput + 1))
					return false;
			if (!(Map[Yinput + 1][Xinput].CheckStatus() == 2 ||
				Map[Yinput + 1][Xinput].CheckStatus() == 1))
				return false;
		}
		if (Xinput + 1 < Length)
		{
			if (Map[Yinput][Xinput + 1].CheckMine() &&
				Map[Yinput][Xinput + 1].CheckStatus() != 3)
				if (!MarkHereWhenSurronded(Map, Length, High, Xinput + 1, Yinput))
					return false;
			if (!(Map[Yinput][Xinput + 1].CheckStatus() == 2 ||
				Map[Yinput][Xinput + 1].CheckStatus() == 1))
				return false;
		}
		Map[Yinput][Xinput].AreaStatusChange(3);
		return true;
	}
	return false;
}

void MarkVoid(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High,
	int Xinput, int Yinput) {
	Map[Yinput][Xinput].AreaStatusChange(2);
	if (!Map[Yinput][Xinput].CheckMine()) {
		if (Xinput - 1 >= 0 &&
			Map[Yinput][Xinput-1].CheckStatus() == 0)
		{
			if (Map[Yinput][Xinput - 1].CheckVoid())
				MarkVoid(Map, Length, High, Xinput - 1, Yinput);
			if (!Map[Yinput][Xinput - 1].CheckMine())
			{
				Map[Yinput][Xinput-1].AreaStatusChange(2);
			}
		}
		if (Yinput - 1 >= 0 &&
			Map[Yinput - 1][Xinput].CheckStatus() == 0)
		{
			if (Map[Yinput - 1][Xinput].CheckVoid())
				MarkVoid(Map, Length, High, Xinput, Yinput - 1);
			if (!Map[Yinput - 1][Xinput].CheckMine())
			{
				Map[Yinput - 1][Xinput].AreaStatusChange(2);
			}
		}
		if (Yinput + 1 < High &&
			Map[Yinput + 1][Xinput].CheckStatus() == 0)
		{
			if (Map[Yinput + 1][Xinput].CheckVoid())
				MarkVoid(Map, Length, High, Xinput, Yinput + 1);
			if (!Map[Yinput + 1][Xinput].CheckMine())
			{
				Map[Yinput + 1][Xinput].AreaStatusChange(2);
			}
		}
		if (Xinput + 1 < Length &&
			Map[Yinput][Xinput +1].CheckStatus() == 0)
		{
			if (Map[Yinput][Xinput + 1].CheckVoid())
				MarkVoid(Map, Length, High, Xinput + 1, Yinput);
			if (!Map[Yinput][Xinput + 1].CheckMine())
			{
				Map[Yinput][Xinput+1].AreaStatusChange(2);
			}
		}
	}
	return;
}

int Scan(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High)
{
	int Count = 0;
	for (int y = 0; y < High; ++y)
	{
		for (int x = 0; x < Length; ++x)
		{
			MarkHereWhenSurronded(Map, Length, High, x, y);
			if (Map[y][x].CheckMine() && (Map[y][x].CheckStatus() == 1 ||
				Map[y][x].CheckStatus() == 3))
				++Count;
		}
	}
	return Count;
}

void Inif(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High)
{
	int Count = 0;
	for (int y = 0; y < High; ++y)
	{
		for (int x = 0; x < Length; ++x)
		{
			Map[y][x].Mine::Mine();
		}
	}
}
