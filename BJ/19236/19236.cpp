#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream> //15:30
#include <string.h>

using namespace std;
int map[6][6][2];
int shark_x;
int shark_y;
int shark_dir;
int ret,mymax;
int dir_x[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dir_y[9] = { 0,0,-1,-1,-1,0,1,1,1 };


void map_swap(int x, int y, int dx, int dy) {
	int tmp1 = map[x][y][0];
	int tmp2 = map[x][y][1];
	map[x][y][0] = map[dx][dy][0];
	map[x][y][1] = map[dx][dy][1];
	map[dx][dy][0] = tmp1;
	map[dx][dy][1] = tmp2;
}
void fishmove() {
	int dir_x[9] = { 0,-1,-1,0,1,1,1,0,-1 };
	int dir_y[9] = { 0,0,-1,-1,-1,0,1,1,1 };

	for (int k = 1; k <= 16; k++) {
		int flag = 0;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (map[i][j][0] == k && flag == 0) {
					for (int l = 0; l < 8; l++) {
						int dx = i + dir_x[map[i][j][1] + l > 8 ? map[i][j][1] + l - 8 : map[i][j][1] + l];
						int dy = j + dir_y[map[i][j][1] + l > 8 ? map[i][j][1] + l - 8 : map[i][j][1] + l];
						if (map[dx][dy][0]!=-1 && (shark_x!=dx || shark_y!=dy)) {
							map[i][j][1] = (map[i][j][1] + l > 8 ? map[i][j][1] + l - 8 : map[i][j][1] + l);
							map_swap(i, j, dx, dy);
							flag = 1;
							break;
						}
					}
				}
			}
		}
	}
}

void read() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cin >> map[i][j][0] >> map[i][j][1];
		}
	}
}



void savemap(int map_before[6][6][2]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			map_before[i][j][0] = map[i][j][0];
			map_before[i][j][1] = map[i][j][1];
		}
	}
}

void loadmap(int map_before[6][6][2]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			map[i][j][0] = map_before[i][j][0];
			map[i][j][1] = map_before[i][j][1];
		}
	}
}
void DFS() {
	int dx = dir_x[shark_dir];
	int dy = dir_y[shark_dir];

	for (int i = 1; i < 4; i++) {
		if (1<= shark_x + i * dx && shark_x + i * dx<=4 && 1<= shark_y + i * dy&&shark_y + i * dy<=4) {
			if (map[shark_x + i * dx][shark_y + i * dy][0] > 0) {
				int score = map[shark_x + i * dx][shark_y + i * dy][0];
				int shark_x_before, shark_y_before, shark_dir_before;
				int map_before[6][6][2];

				ret += score;
				shark_x_before = shark_x;
				shark_y_before = shark_y;
				shark_dir_before = shark_dir;

				savemap(map_before);

				map[shark_x + i * dx][shark_y + i * dy][0] = 0;
				shark_dir = map[shark_x + i * dx][shark_y + i * dy][1];

				shark_x = shark_x + i * dx;
				shark_y = shark_y + i * dy;

				fishmove();
				DFS();

				loadmap(map_before);
				shark_x = shark_x_before;
				shark_y = shark_y_before;
				shark_dir = shark_dir_before;
				ret -= score;
			}
		}
		else {
			break;
		}
	}
	if (mymax < ret) {
		mymax = ret;
	}

}
int main() {
	memset(map, -1, 6 * 6 * 2 * sizeof(int));
	freopen("input.txt", "r", stdin);
	read();

	ret += map[1][1][0];
	shark_x = 1;
	shark_y = 1;
	shark_dir = map[1][1][1];
	map[1][1][0] = 0;
	fishmove();

	DFS();
	cout << mymax;
	return 0;
}
