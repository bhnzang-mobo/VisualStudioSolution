#include <iostream>
#include <stdio.h>
#include <queue>
#include "pch.h"
#include <vector>
#pragma warning(disable:4996)
using namespace std;
/*
문제
N×N크기의 땅이 있고, 땅은 1×1개의 칸으로 나누어져 있다. 각각의 땅에는 나라가 하나씩 존재하며, r행 c열에 있는 나라에는 A[r][c]명이 살고 있다. 인접한 나라 사이에는 국경선이 존재한다. 모든 나라는 1×1 크기이기 때문에, 모든 국경선은 정사각형 형태이다.

오늘부터 인구 이동이 시작되는 날이다.

인구 이동은 다음과 같이 진행되고, 더 이상 아래 방법에 의해 인구 이동이 없을 때까지 지속된다.

국경선을 공유하는 두 나라의 인구 차이가 L명 이상, R명 이하라면, 두 나라가 공유하는 국경선을 오늘 하루동안 연다.
위의 조건에 의해 열어야하는 국경선이 모두 열렸다면, 인구 이동을 시작한다.
국경선이 열려있어 인접한 칸만을 이용해 이동할 수 있으면, 그 나라를 오늘 하루 동안은 연합이라고 한다.
연합을 이루고 있는 각 칸의 인구수는 (연합의 인구수) / (연합을 이루고 있는 칸의 개수)가 된다. 편의상 소수점은 버린다.
연합을 해체하고, 모든 국경선을 닫는다.
각 나라의 인구수가 주어졌을 때, 인구 이동이 몇 번 발생하는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N, L, R이 주어진다. (1 ≤ N ≤ 50, 1 ≤ L ≤ R ≤ 100)

둘째 줄부터 N개의 줄에 각 나라의 인구수가 주어진다. r행 c열에 주어지는 정수는 A[r][c]의 값이다. (0 ≤ A[r][c] ≤ 100)

인구 이동이 발생하는 횟수가 2,000번 보다 작거나 같은 입력만 주어진다.

출력
인구 이동이 몇 번 발생하는지 첫째 줄에 출력한다.
*/
typedef struct country {
	int _union;
	int _r;
	int _c;
}country;

queue<country> myqueue;
int world[50][50];//각 나라의 인구 수를 저장
int world_isunion[50][50];//각 나라가 어느 연합에 포함 되었는지 저장.
int N, L, R;//Left Right..?
country myunion[1250][2500];//각 유니온의 정보. 0부터 최대 1250까지(2500개의 나라가 2개씩짝지어 1250개)
int numOfUnion[1250];//각 유니온별 구성유니온의 개수(사실 필요한지모르겠음)


void read() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> world[i][j];
		}
	}
}

bool surroundCheck(int row, int col) {
	vector<pair<int, int>> v1;
	v1.push_back(make_pair(-1, 0));
	v1.push_back(make_pair(0, 1));
	v1.push_back(make_pair(1, 0));
	v1.push_back(make_pair(0, -1));
	vector<pair<int, int>> ::iterator itr;
	for (itr = v1.begin(); itr != v1.end(); itr++) {
		int d_row = ((row + (*itr).first >= 0 && row + (*itr).first < N) ? row + (*itr).first : row);
		int d_col = ((col + (*itr).second >= 0 && col + (*itr).second < N) ? col + (*itr).second : col);
		int delta = abs(world[d_row][d_col] - world[row][col]);
		if (world_isunion[d_row][d_col] != 1 && delta >= L && delta <= R && (d_row != row || d_col != col)) {
			return true;
		}
	}
	return false;
}

void Arrange(int total) {
	for (int i = 0; i < total; i++) {
		int citizen = 0;
		for (int j = 0; j < numOfUnion[i]; j++) {
			citizen += world[myunion[i][j]._r][myunion[i][j]._c];
		}
		citizen /= numOfUnion[i];
		for (int j = 0; j < numOfUnion[i]; j++) {
			 world[myunion[i][j]._r][myunion[i][j]._c]=citizen;
		}
	}
}

int createUnion() {
	int totalUnion;
	int times = 0;
	do {
		totalUnion = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (world_isunion[i][j] == 0) {
					if (surroundCheck(i, j)) {
						int union_idx = 0;
						world_isunion[i][j] = 1;
						country cont;
						cont._c = j;
						cont._r = i;
						cont._union = totalUnion;
						myqueue.push(cont);
						myunion[totalUnion][union_idx]._r = cont._r;
						myunion[totalUnion][union_idx]._c = cont._c;
						myunion[totalUnion][union_idx++]._union = totalUnion;

						vector<pair<int, int>> v1;
						v1.push_back(make_pair(-1, 0));
						v1.push_back(make_pair(0, 1));
						v1.push_back(make_pair(1, 0));
						v1.push_back(make_pair(0, -1));

						while (!myqueue.empty()) {
							cont = myqueue.front();
							myqueue.pop();
							int row = cont._r;
							int col = cont._c;
							vector<pair<int, int>> ::iterator itr;
							for (itr = v1.begin(); itr != v1.end(); itr++) {
								int d_row = ((row + (*itr).first >= 0 && row + (*itr).first < N) ? row + (*itr).first : row);
								int d_col = ((col + (*itr).second >= 0 && col + (*itr).second < N) ? col + (*itr).second : col);
								int delta = abs(world[d_row][d_col] - world[row][col]);
								if (world_isunion[d_row][d_col] != 1 && delta >= L && delta <= R && (d_row != row || d_col != col)) {
									cont._r = row + (*itr).first;
									cont._c = col + (*itr).second;
									cont._union = totalUnion;
									myqueue.push(cont);
									myunion[totalUnion][union_idx]._r = cont._r;
									myunion[totalUnion][union_idx]._c = cont._c;
									myunion[totalUnion][union_idx++]._union = totalUnion;

									world_isunion[cont._r][cont._c] = 1;
								}
							}
						}
						numOfUnion[totalUnion] = union_idx;
						totalUnion++;
					}
				}
				else {
					continue;
				}
			}
		}
		//국민 arrange
		if (totalUnion > 0) {
			Arrange(totalUnion);
			times++;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					world_isunion[i][j] = 0;
				}
			}
		}

	} while (totalUnion > 0);
	return times;
}

int main() {
	freopen("input.txt","r",stdin);
	read();
	cout << createUnion();
	return 0;
}