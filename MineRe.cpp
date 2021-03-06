// MineRe.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include<time.h>
#include"Mine.h"
#include<stdlib.h>
using namespace std;

int main()
{
	Mine Map[MAX_HIGH][MAX_LENGTH];
	int High=20;
	int Length=30;
	int MineNum=20;
	int MineFind=0;
	int Ans;
	int Choice;
	int InputX, InputY;
	srand((unsigned)time(NULL));
	
	while (1)
	{
		while (1) {
			cout << "Please input Length and High" << endl;
			cin >> Length >> High;
			if (Length >= 3 && Length <= MAX_LENGTH)
				if (High >= 3 && High <= MAX_HIGH)
					break;
			cout << "Error" << endl;
		}
		while (1) {
			cout << "Please input MineMount" << endl;
			cin >> MineNum;
			if (Length >= 1 && Length <= (High*Length) - 1)
					break;
			cout << "Error" << endl;
		}
		Inif(Map, Length, High);
		StartGame(Map, Length, High, MineNum);
		while (1)
		{
			system("cls");
			DrawMap(Map,Length,High,false);
			while (1)
			{
				cout << "Please input X and Y" << endl;
				cin >> InputX >> InputY;
				rewind(stdin);
				if (InputX<0 || InputX>Length || InputY<0 || InputY>High) {
					cout << "Error" << endl;
					continue;
				}
				cout << "Clearane(0) Mark(1) RemoveMark(2)" << endl;
				cin >> Choice;
				rewind(stdin);
				Ans = Map[InputY][InputX].MineClearance(Choice);
				if (Ans != 4)
					break;
				cout << "Error" << endl;
			}
			if (Ans != 0 || Ans != 1) {
				if (Ans == 3)
					MarkVoid(Map, Length, High, InputX, InputY);
			}
			if (Ans == 0 || Ans == 1)
			{
				system("cls");
				DrawMap(Map, Length, High, true);
			}
			if (Ans == 0)
				break;
			if (Ans == 1)
				exit(1);
			MineFind=Scan(Map, Length, High);
			if (MineFind == MineNum)
			{
				system("cls");
				DrawMap(Map, Length, High, true);
				cout << "Win" << endl;
				cout << "Retry?(Y:0)" << endl;
				cin >> InputX;
				rewind(stdin);
				if (InputX != 0)
					exit(1);
			}
		}
		getchar();
		system("cls");
	}
	return 0;
}
