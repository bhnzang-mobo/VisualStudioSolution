#include "pch.h"
#pragma warning(disable:4996)
#include <iostream>
#include <string.h>
#include <queue>

int map[52][52];
int virus[10][2];
int N, M, V,mintime;
int combination[10][2];
int dir_x[4]= { -1,0,1,0 };
int dir_y[4]= { 0,1,0,-1 };

using namespace std;
void read() {
	cin >> N >> M;
	V = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus[V][0] = i;
				virus[V++][1] = j;
			}
		}
	}
}
int mapcheck() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}
int BFS() {

	queue<pair<int, int> > bigqueue;
	queue<pair<int, int> > myqueue;
	for (int i = 0; i < M; i++) {
		bigqueue.push(make_pair(combination[i][0],combination[i][1]));
	}

	int backupmap[52][52];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			backupmap[i][j] = map[i][j];
		}
	}
	//맵 백업
	int  times = 0;
	while (!bigqueue.empty()) {
		if (mapcheck() == 1) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					map[i][j] = backupmap[i][j];
				}
			}
			return times;
		}
		int flag = 0;
		while (!bigqueue.empty()) {
			myqueue.push(bigqueue.front());
			bigqueue.pop();
		}

		while (!myqueue.empty()) {
			pair<int, int> pos = myqueue.front();
			myqueue.pop();
			map[pos.first][pos.second] = 3;//활성
			for (int i = 0; i < 4; i++) {
				int what = map[pos.first + dir_x[i]][pos.second + dir_y[i]];
				if (what != -1 && what != 1 && what != 3) {
					flag = 1;
					map[pos.first + dir_x[i]][pos.second + dir_y[i]] = 3;
					bigqueue.push(make_pair(pos.first + dir_x[i], pos.second + dir_y[i]));
				}
			}
		}
		if (flag == 1) {
			times++;
		}
		
	}
	int ret=987654321;
	if (mapcheck() == 1) {
		ret= times;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = backupmap[i][j];
		}
	}
	return ret;
	//맵 복구
}
int dp[11];
void comb(int from, int num) {//from 부터 num개를 고른다.
	
	if (V-from+1<num) {//남은 바이러스가 골라야하는 개수보다 적다
		return;
	}
	if (num <= 0) {//M회 선택한 후
		int ret = BFS();
		if (mintime > ret) {
			mintime=ret;
		}
		
		return;
	}
	for (int i = from-1; i < V; i++) {
		int idx = M - num;

		combination[idx][0] = virus[i][0];
		combination[idx][1] = virus[i][1];
		dp[idx] = i + 1;
		comb(i + +2, num-1);
	}
}
int main()
{
	memset(map, -1, 52 * 52 * sizeof(int));
	freopen("input.txt", "r", stdin);
	read();
	mintime = 987654321;
	comb(1, M);
	if (mintime == 987654321) {
		cout << -1;
		return 0;
	}
	cout << mintime;
	return 0;
}

