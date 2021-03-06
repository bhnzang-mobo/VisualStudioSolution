#include "pch.h"
#pragma warning(disable:4996)
#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
using namespace std;
//map_horse 번호로 바꿈
//map 번호임
//0 : 행번호 1 열번호 2 방향
queue<pair<int, int> > map_horse[13][13];
int horse[11][3];
int map[14][14];

int dir_x[5] = { 0,0,0,-1,1 };
int dir_y[5] = { 0,1,-1,0,0 };
int N, K;
void read() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				map[i][j]=-1;
			}
		}
	}
	for (int i = 1; i <= K; i++) {
		cin >> horse[i][0] >> horse[i][1] >> horse[i][2];
		map_horse[horse[i][0]][horse[i][1]].push(make_pair(i, horse[i][2]));
	}
}

int comcheck() {//현재 맵에 겹쳐진 말의 최대값을 반환
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (ret < map_horse[i][j].size()) {
				ret = map_horse[i][j].size();
			}
		}
	}
	return ret;
}
void move(int idx) {
	int x = horse[idx][0];
	int y = horse[idx][1];
	int dir= horse[idx][2];

	int dx = x + dir_x[dir];
	int dy = y + dir_y[dir];
	
	int dst_x, dst_y;
	if (map[dx][dy] == -1) {
		dx = x - dir_x[dir];
		dy = y - dir_y[dir];
		if (horse[idx][2] <3) {
			horse[idx][2] = 3 - horse[idx][2];
		}
		else {
			horse[idx][2] = 7 - horse[idx][2];
		}

		if (map[dx][dy] == -1) {
			dst_x = x;
			dst_y = y;
		}
		else {
			dst_x = dx;
			dst_y = dy;
		}
	}

	else {
		dst_x = dx;
		dst_y = dy;
	}
	if (x == dst_x && y == dst_y)return;//제자리입니다

	queue<pair<int, int> > dst_que;
	stack<pair<int, int> > dst_stack;

	switch (map[dst_x][dst_y])
	{

	case 0://도착점은 흰색입니다!
		
		swap(map_horse[x][y], dst_que);

		while (dst_que.front().first != idx) {
			map_horse[x][y].push(dst_que.front());
			dst_que.pop();
		}

		while (!dst_que.empty()) {
			map_horse[dst_x][dst_y].push(dst_que.front());
			horse[dst_que.front().first][0]=dst_x;
			horse[dst_que.front().first][1]=dst_y;
			dst_que.pop();
		}


		break;
	case 1://도착점은 빨간색입니다!
		swap(map_horse[x][y], dst_que);
		while (dst_que.front().first != idx) {
			map_horse[x][y].push(dst_que.front());
			dst_que.pop();
		}

		while (!dst_que.empty()) {
			dst_stack.push(dst_que.front());
			dst_que.pop();
		}

		while (!dst_stack.empty()) {
			map_horse[dst_x][dst_y].push(dst_stack.top());
			horse[dst_stack.top().first][0] = dst_x;
			horse[dst_stack.top().first][1] = dst_y;
			dst_stack.pop();
		}

		break;

	default:
		break;
	}
	
	
}
int ret;
void play() {
	while (ret<=1000) {
		ret++;
		for (int i = 1; i <= K; i++) {
			move(i);
			if (comcheck() >= 4) {
				return;
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	memset(map,-1, 14 * 14 * sizeof(int));

	read();
	play();
	cout << (ret>1000?-1:ret);
	return 0;
}

