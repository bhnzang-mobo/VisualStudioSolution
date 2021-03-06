// Keypad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;
int nleft,nright;

int LOR(int a) {
	if (a == 1 || a == 4 || a == 7) {
		return 0; //left
	}
	else if (a == 3 || a == 6 || a == 9) {
		return 1; //right
	}
	else {
		return 2;
	}
}

void calpos(int* x, int* y, int val) {
	*x = (val - 1) / 3;
	*y = (val - 1) % 3;
}

string solution(vector<int> numbers, string hand) {
	nleft = 10;
	nright = 12;
	string answer = "";
	vector<int>::iterator iter;
	for (iter = numbers.begin(); iter != numbers.end(); iter++) {
		int topush = *iter;
		if (topush == 0) {
			topush = 11;
		}

		int lor = LOR(*iter);
		if (lor == 0) {
			nleft = topush;
			answer.push_back('L');
		}

		else if (lor == 1) {
			nright = topush;
			answer.push_back('R');
		}
		else {
			int topush_x, topush_y, left_x, left_y, right_x, right_y;
			calpos(&topush_x, &topush_y, topush);
			calpos(&left_x, &left_y, nleft);
			calpos(&right_x, &right_y, nright);
			if (abs(topush_x - left_x) + abs(topush_y - left_y) > abs(topush_x - right_x) + abs(topush_y - right_y)) {
				nright = topush;
				answer.push_back('R');
			}
			else if (abs(topush_x - left_x) + abs(topush_y - left_y) == abs(topush_x - right_x) + abs(topush_y - right_y)) {
				if (hand.compare("left") == 0) {
					nleft = topush;
					answer.push_back('L');
				}
				else {
					nright = topush;
					answer.push_back('R');
				}
			}
			else {
				nleft = topush;
				answer.push_back('L');
			}
		}
	}
	return answer;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int N;
	cin >> N;
	vector<int> num;
	num.reserve(N);
	for (int i = 0; i < N; i++) {
		int input;
		cin >> input;
		num.push_back(input);
	}
	string myhand("left");
	cout << solution(num, myhand);
}
