#pragma once
#include<iostream>
#include<iomanip>
#define MAX_LENGTH 30
#define MAX_HIGH 20
class Mine
{
public:
	Mine();
	bool CheckMine();
	int CheckStatus();
	bool CheckVoid();
	int MineClearance(int Choice);
	void Output(bool Ans);

	Mine& PutMine();
	Mine& AreaStatusChange(int Choice);//change the visualbe status
	Mine& Count(bool Mi);

private:
	int Status;//0-unchecked 1-?mark 2-open 3-unmarked but surrounded
	bool MineMark;
	int MineAround;
};
void StartGame(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High,
	int MineNum);
void DrawMap(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High, bool EndofGame);
bool MarkHereWhenSurronded(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High,
	int Xinput, int Yinput);
void MarkVoid(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High,
	int Xinput, int Yinput);
int Scan(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High);
void Inif(Mine Map[MAX_HIGH][MAX_LENGTH], int Length, int High);