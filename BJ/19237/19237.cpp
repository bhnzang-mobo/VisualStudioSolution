#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
using namespace std;
int N, M, k;

int map[2][20][20][3];
int dir[400][4][4];
/*
0:상어 번호
1:냄시 카운트
2:상어 방향
*/
typedef struct _pos {
	int x;
	int y;
	int dir;
}pos;
int showme() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[0][i][j][1] == k) {
				ret++;
			}
		}
	}
	return ret;
}
void read() {
	cin >> N >> M >> k;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[0][i][j][0];
			if (map[0][i][j][0] != 0) {
				map[0][i][j][1] = k;
				map[1][i][j][0] = map[0][i][j][0];
				map[1][i][j][1] = k;
			}
		}
	}
	for (int l = 1; l <= M; l++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[0][i][j][0] == l) {
					cin >> map[0][i][j][2];
					map[1][i][j][2] = map[0][i][j][2];
				}
			}
		}
	}
	//dir[상어번호][현재방향][우선순위순서];
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < 4; j++) {
			for (int l = 0; l < 4; l++) {
				cin >> dir[i][j][l];
			}
		}
	}
}
//1 : 위 2: 아래 3: 왼쪽 4 :오른쪽 대체 왜??????
pos nextPos(int i, int j, int nowdir) {
	int * dir_s = dir[map[0][i][j][0]-1][nowdir-1];
	int dirx[4] = {-1,1,0,0};
	int diry[4] = {0,0,-1,1};
	pos node;
	for (int idx = 0; idx < 4; idx++) {
		int dx, dy;
		dx = i + dirx[dir_s[idx]-1];
		dy = j + diry[dir_s[idx]-1];
		if (dx<0 || dx >N - 1 || dy<0 || dy >N - 1) continue;
		if (map[0][dx][dy][1] == 0) {//빈칸판정
			node.x = dx;
			node.y = dy;
			node.dir = dir_s[idx];
			return node;
		}
	}
	
	for (int idx = 0; idx < 4; idx++) {
		int dx, dy;
		dx = i + dirx[dir_s[idx]-1];
		dy = j + diry[dir_s[idx]-1];
		if (dx<0 || dx >N - 1 || dy<0 || dy >N - 1) continue;
		if (map[0][dx][dy][0] == map[0][i][j][0]) {//자기자신판정
			node.x = dx;
			node.y = dy;
			node.dir = dir_s[idx];
			return node;
		}
	}
}
void play() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[0][i][j][1] == k) {
				pos mypos = nextPos(i, j, map[0][i][j][2]);
				if (map[1][mypos.x][mypos.y][1] == 0 || map[1][mypos.x][mypos.y][0]== map[0][i][j][0]) {
					map[1][mypos.x][mypos.y][0] = map[0][i][j][0];
					map[1][mypos.x][mypos.y][1] = map[0][i][j][1];
					map[1][mypos.x][mypos.y][2] = mypos.dir;
					map[1][i][j][1]--;
				}
				else if(map[1][mypos.x][mypos.y][0]> map[0][i][j][0]) {
					map[1][mypos.x][mypos.y][0] = map[0][i][j][0];
					map[1][mypos.x][mypos.y][1] = map[0][i][j][1];
					map[1][mypos.x][mypos.y][2] = mypos.dir;
					map[1][i][j][1]--;
				}
				else {
					map[1][i][j][1]--;
				}
			}
			else if(map[0][i][j][1]>0){//자기자신으로 덮어씌워진 경우
				if (map[0][i][j][1] >= map[1][i][j][1]) {
					map[1][i][j][1]--;
				}
			}
			else {
				if (map[1][i][j][1] == 0) {
					map[1][i][j][0] = 0;
					map[1][i][j][1] = 0;
					map[1][i][j][2] = 0;
				}
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[0][i][j][0] = map[1][i][j][0];
			map[0][i][j][1] = map[1][i][j][1];
			map[0][i][j][2] = map[1][i][j][2];
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	int ret = 0;
	while (1) {
		if (ret > 1000) {
			cout << -1;
			break;
		}
		if (showme() == 1) {//이거 순서 주의 만약 상어가 한마리라면 어떡할껀데?
			cout << ret;
			break;
		}
		ret++;
		play();
		
	}
	return 0;
}
