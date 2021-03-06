// 14500.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>
using namespace std;
/*
입력
첫째 줄에 종이의 세로 크기 N과 가로 크기 M이 주어진다. (4 ≤ N, M ≤ 500)

둘째 줄부터 N개의 줄에 종이에 쓰여 있는 수가 주어진다. 
i번째 줄의 j번째 수는 위에서부터 i번째 칸, 왼쪽에서부터 j번째 칸에 쓰여 있는 수이다.
입력으로 주어지는 수는 1,000을 넘지 않는 자연수이다.
*/

int N, M, ret;
int map[502][502];
int visit[502][502];
int dir_x[4] = { -1,0,1,0 };
int dir_y[4] = { 0,1,0,-1 };

void read() {
	memset(map, -1, 502 * 502 * sizeof(int));
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
}

int DFS(int x, int y, int depth) {
	if (depth >= 4) {
		visit[x][y] = 0;
		return map[x][y];
	}
	int mymax = 0;
	for (int i = 0; i < 4; i++) {
		int dx = x + dir_x[i];
		int dy = y + dir_y[i];
		if (map[dx][dy] != -1 && visit[dx][dy]!=1) {
			visit[dx][dy] = 1;
			int tmp=DFS(dx, dy, depth + 1);
			if (mymax < tmp) {
				mymax = tmp;
			}
		}
	}
	visit[x][y] = 0;
	return map[x][y] + mymax;

}
int exShape(int x, int y) {
	int dir[4][4] = { { 1,1,0,1 }, { 1,1,1,0 }, { 0,1,1,1 }, { 1,0,1,1 } };
	int mymax=0;
	for (int i = 0; i < 4; i++) {
		int flag = 1;
		for (int j = 0; j < 4; j++) {
			if (dir[i][j] == 1) {
				if (map[x + dir_x[j]][y + dir_y[j]] != -1) {
					continue;
				}
				else {
					flag = 0;
				}
			}
		}
		if (flag == 1) {
			int tmp = 0;
			for (int j = 0; j < 4; j++) {
				if (dir[i][j] == 1) {
					tmp += map[x + dir_x[j]][y + dir_y[j]];
				}
			}
			if (mymax < tmp) {
				mymax = tmp;
			}
		}
	}
	return mymax+map[x][y];

}
int cal() {
	int mymax = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			visit[i][j] = 1;
			int cmp1 = DFS(i,j,1);
			int cmp2 = exShape(i, j);
			if (cmp1 > cmp2) {
				if (cmp1 > mymax) {
					mymax = cmp1;
				}
			}
			else {
				if (cmp2 > mymax) {
					mymax = cmp2;
				}
			}
			visit[i][j] = 0;
		}
	}
	return mymax;
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	cout << cal();
}
