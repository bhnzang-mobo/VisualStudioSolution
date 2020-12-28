#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>
using namespace std;

int N;
int map[501][501];//모래 정보
int arr[501][501];//방문정보
int dir_now;
int dir_next;

pair<int, int> pos_now;
int out;

int dir_x[4] = { 0, 1, 0, -1 };//좌하우상 순서
int dir_y[4] = { -1, 0, 1, 0 };

double spread_pos[5][5] = {
	0,0,0.02,0,0,
	0,0.1,0.07,0.01,0,
	0.05,-1,0,0,0,
	0,0.1,0.07,0.01,0,
	0,0,0.02,0,0
};
pair<int, int> nextpos() {
	int dx = pos_now.first + dir_x[dir_now];
	int dy = pos_now.second + dir_y[dir_now];
	if (map[dx][dy]==-1) {//내가 가고자 하는 방향이 격자 밖인 경우
		dx = pos_now.first + dir_x[dir_next];
		dy = pos_now.second + dir_y[dir_next];

		arr[dx][dy] = 1;
		return make_pair(dx, dy);
	}
	else if (arr[dx][dy] == 0) {
		arr[dx][dy] = 1;
		return make_pair(dx, dy);
	}
	if (arr[pos_now.first + dir_x[dir_next]][pos_now.second + dir_y[dir_next]] == 0) {//내 다음 방향으로 움직일 수 있는 경우
		dx = pos_now.first + dir_x[dir_next];
		dy = pos_now.second + dir_y[dir_next];
		arr[dx][dy] = 1;
		return make_pair(dx, dy);
	}
	arr[dx][dy] = 1;
	return make_pair(dx, dy);
}

void read() {
	cin >> N;
	for (int i = 1; i <=N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
}
void spread() {
	if (map[pos_now.first][pos_now.second] == 0) {
		return;
	}

	int dust = map[pos_now.first][pos_now.second];
	int dx, dy;
	int sum = 0;
	int alpha_x=0, alpha_y=0;
	switch (dir_now)
	{
	case 0://좌표 그대로 이용
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (spread_pos[i][j] == -1) {
					alpha_x = i - 2;
					alpha_y = j - 2;
					continue;
				}
				if (spread_pos[i][j] != 0) {
					dx = pos_now.first + i-2;
					dy = pos_now.second + j-2;
					sum += spread_pos[i][j] * dust;
					if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
						map[dx][dy] += spread_pos[i][j] * dust;
					}
					else {
						out+= spread_pos[i][j] * dust;
					}
				}
			}
		}
		dx = pos_now.first + alpha_x;
		dy = pos_now.second + alpha_y;
		if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
			map[dx][dy] += (dust-sum);
		}
		else {
			out += (dust - sum);
		}
		break;
	case 1://y=x대칭 후 x=2대칭
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (spread_pos[i][j] == -1) {
					alpha_x = 2 - j;
					alpha_y = i - 2;
					continue;
				}
				if (spread_pos[i][j] != 0) {
					dx = pos_now.first + 4-j - 2;
					dy = pos_now.second + i -2;
					sum += spread_pos[i][j] * dust;
					if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
						map[dx][dy] += spread_pos[i][j] * dust;
					}
					else {
						out += spread_pos[i][j] * dust;
					}
				}
			}
		}
		dx = pos_now.first + alpha_x;
		dy = pos_now.second + alpha_y;
		if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
			map[dx][dy] += (dust - sum);
		}
		else {
			out += (dust - sum);
		}
		break;
	case 2://y=2대칭
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (spread_pos[i][j] == -1) {
					alpha_x = i - 2;
					alpha_y = 2 - j;
					continue;
				}
				if (spread_pos[i][j] != 0) {
					dx = pos_now.first + i - 2;
					dy = pos_now.second + 4-j - 2;
					sum += spread_pos[i][j] * dust;
					if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
						map[dx][dy] += spread_pos[i][j] * dust;
					}
					else {
						out += spread_pos[i][j] * dust;
					}
				}
			}
		}
		dx = pos_now.first + alpha_x;
		dy = pos_now.second + alpha_y;
		if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
			map[dx][dy] += (dust - sum);
		}
		else {
			out += (dust - sum);
		}
		break;
	case 3://y=x대칭
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (spread_pos[i][j] == -1) {
					alpha_x = j - 2;
					alpha_y = i - 2;
					continue;
				}
				if (spread_pos[i][j] != 0) {
					dx = pos_now.first + j - 2;
					dy = pos_now.second + i - 2;
					sum += spread_pos[i][j] * dust;
					if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
						map[dx][dy] += spread_pos[i][j] * dust;
					}
					else {
						out += spread_pos[i][j] * dust;
					}
				}
			}
		}
		dx = pos_now.first + alpha_x;
		dy = pos_now.second + alpha_y;
		if (1 <= dx && dx <= N && 1 <= dy && dy <= N) {
			map[dx][dy] += (dust - sum);
		}
		else {
			out += (dust - sum);
		}
		break;
	default:
		break;
	}
	map[pos_now.first][pos_now.second] = 0;
}
void changedir() {
	int dx = pos_now.first + dir_x[dir_now];
	int dy = pos_now.second + dir_y[dir_now];
	if (map[dx][dy] == -1 ||arr[pos_now.first + dir_x[dir_next]][pos_now.second + dir_y[dir_next]] == 0) {//내 다음 방향으로 움직일 수 있는 경우
		dir_now = dir_next;
		dir_next = (dir_next + 1) % 4;
	}
}
void play() {
	pos_now.first = N / 2 + 1;
	pos_now.second = N / 2 + 1;
	arr[pos_now.first][pos_now.second] = 1;
	do {
		pos_now = nextpos();
		spread();
		changedir();
	} while (pos_now.first!=1 || pos_now.second!=1);

}
int main() {
	memset(map, -1, sizeof(int) * 501 * 501);
	freopen("input.txt", "r", stdin);
	dir_now = 0;
	dir_next = 1;
	read();
	play();
	cout << out;
	return 0;
}