// 17825.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
using namespace std;

int horse[4][2];//0: 길의 종류 1:눈의 idx 초기값 = 1,0;
int works[10];
int way[4][25]={ { 0,2,4,6,8,
				10,12,14,16,18,
				20,22,24,26,28,
				30,32,34,36,38,
				40,0 } ,//1~20 21
				{ 0,2,4,6,8,
				10,13,16,19,25,
				30,35,40,0 },//1~12 13
				{ 0,2,4,6,8,
				10,12,14,16,18,
				20,22,24,25,30,
				35,40,0 },//1~16, 17
				{ 0,2,4,6,8,10,
				12,14,16,18,20,
				22,24,26,28,30,
				28,27,26,25,30,
				35,40,0 }//1~22 23
};

int dicego(int i, int eye) {
	int num = horse[i][1];
	switch (horse[i][0]) { //현재 위치가 도착지점 인경우.
	case 0:
		if (num == 21) {
			return 0;
		}
		break;
	case 1:
		if (num ==13) {
			return 0;
		}
		break;
	case 2:
		if (num ==17) {
			return 0;
		}
		break;
	case 3:
		if (num == 23) {
			return 0;
		}
		break;
	default:
		break;
	}
	num += eye;
	switch (horse[i][0]) { //나아갔는데 도착지점 이상인경우
	case 0:
		if (num >= 21) {
			return 1;
		}
		break;
	case 1:
		if (num >= 13) {
			return 1;
		}
		break;
	case 2:
		if (num >= 17) {
			return 1;
		}
		break;
	case 3:
		if (num >= 23) {
			return 1;
		}
		break;
	default:
		break;
	}
	for (int j = 0; j < 4; j++) {
		if (i != j && way[horse[j][0]][horse[j][1]] == way[horse[i][0]][num]) {
			if (horse[j][0]!=horse[i][0]) {
				if (way[horse[j][0]][horse[j][1]] == 25) {
					return 0;
				}
				else if (way[horse[j][0]][horse[j][1]] == 30) {
					if (horse[j][1] == 15 && num == 15) {
						return 0;
					}
					else if (horse[j][1] == 15 || num == 15) {
						return 1;
					}
					return 0;
				}
				else if (way[horse[j][0]][horse[j][1]] == 40) {
					return 0;
				}
				else {
					return 1;
				}
			}
			else {
				if (way[horse[j][0]][horse[j][1]] == 30) {
					if (horse[j][1] == 15 && num == 15) {
						return 0;
					}
					else if (horse[j][1] == num) {
						return 0;
					}
					return 1;
				}
				else {
					return 0;
				}
			}
			return 0;
		}
	}
	return 1;
}
int ret, mymax;
int dp[10];
void DFS(int depth) {
	if (depth == 10) {
		if (ret > mymax) {
			mymax = ret;/*
			for (int i = 0; i < 10; i++) {
				cout << dp[i] << "    ";
			}
			cout << endl << "total : " << mymax <<endl;
			*/
		}
		return;
	}
	for (int i = 0; i < 4; i ++) {
		if (dicego(i,works[depth])) {
			int num = horse[i][1] + works[depth];
			switch (horse[i][0]) { //i길위에 도착지점 이상을 놓을 경우.
			case 0:
				if (num > 20) {
					num=21;
				}
				break;
			case 1:
				if (num > 12) {
					num=13;
				}
				break;
			case 2:
				if (num > 16) {
					num = 17;
				}
				break;
			case 3:
				if (num > 22) {
					num = 23;
				}
				break;
			default:
				break;
			}
			int horse0_before = horse[i][0];
			if (way[horse[i][0]][num] == 10) {
				horse[i][0] = 1;
			}
			else if (way[horse[i][0]][num] == 20) {
				horse[i][0] = 2;
			}
			else if (way[horse[i][0]][num] == 30 && num >11) {
				horse[i][0] = 3;
			}
			
			int score = way[horse[i][0]][num];
			int horse1_before = horse[i][1];
			ret += score;
			horse[i][1] = num;
			dp[depth] = score;
			DFS(depth+1);
			ret -= score;
			horse[i][0] = horse0_before;
			horse[i][1] = horse1_before;
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	for (int i = 0; i < 10; i++) {
		cin >> works[i];
	}
	DFS(0);

	cout << mymax;

	return 0;
}
