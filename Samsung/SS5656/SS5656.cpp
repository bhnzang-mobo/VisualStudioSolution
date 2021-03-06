#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
int T, N, W, H;
int map[17][17];
int minblock;
int dir_x[4] = { -1,0,1,0 };
int dir_y[4] = { 0,1,0,-1 };

void gravity() {
	for (int i = 1; i <= W; i++) {
		for (int j = H; j >= 1; j--) {
			if (map[j][i] == 0) continue;
			int itr = 1;
			while (1) {
				int dx = j + itr;
				if (map[dx][i] == 0) {
					itr++;
					continue;
				}
				else {
					int tmp = map[dx - 1][i];
					map[dx-1][i] = map[j][i];
					map[j][i] = tmp;
					break;
				}
			}
		}
	}
}
void destroy(int x, int y) {//이 x,y는 구슬이 터트릴 x,y 이다. 가능한 x,y만 주어질것.
	queue<pair<int, int> > myqueue;
	myqueue.push(make_pair(x, y));

	int visit[17][17] = { 0, };//초기화 잘해야함

	while (!myqueue.empty()) {
		pair<int, int> node = myqueue.front();
		myqueue.pop();

		int val = map[node.first][node.second];
		visit[node.first][node.second] = 1;
		map[node.first][node.second] = 0;

		for (int i = 1; i <= val - 1; i++) {
			for (int j = 0; j < 4; j++) {
				int dx = node.first + i*dir_x[j];
				int dy = node.second + i*dir_y[j];

				if (1<=dx&& dx<=H && 1<=dy && dy<=W && visit[dx][dy]!=1 && map[dx][dy] > 0) {
					visit[dx][dy] = 1;
					myqueue.push(make_pair(dx, dy));
				}
			}
		}
	}
	gravity();
 }

void read() {
	cin >> N >> W >> H;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cin >> map[i][j];
		}
	}
}
int height(int y) { //구슬을 떨굴 y가 주어지면 해당 y에서 가장 처음 만나는 벽돌의 x값을 반환합니다.
	for (int x = 1; x <= H; x++) {
		if (map[x][y] <= 0)continue;
		return x;
	}
	return -1;
}
int howmany() {
	int ret = 0;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) { //젤나가 맙소사 이게 H로 되어있었다.....그래서 답이 틀렸던것 ㅆㅃㅆㅃㅆㅆㅃㅆㅆㅃㅆㅃㅆㅆㅃㅆㅃ
			if (map[i][j] > 0) {
				ret++;
			}
		}
	}
	return ret;
}

void savemap(int map_before[][17]) {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			map_before[i][j] = map[i][j];
		}
	}
}

void loadmap(int map_before[][17]) {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			map[i][j] = map_before[i][j];
		}
	}
}
void showme() {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}
void brute(int cnt) {//N이 주어진 만큼 모든 경우의 수를 계산합니다.
	if (cnt == N) {//N회 구슬을 던진 경우
		int ret = howmany();
		if (ret < minblock) {
			minblock = ret;

		}
		return;
	}

	for (int i = 1; i <= W; i++) {
		int x = height(i);
		int map_before[17][17] = { 0, };
		if ( x != -1) {
			//맵 저장
			savemap(map_before);
			destroy(x, i);
			brute(cnt + 1);
			//맵 회복
			loadmap(map_before);
		}
		else { //삭제할게 없다면?
			int ret = howmany();
			if (ret < minblock) {
				minblock = ret;
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	cin >> T;
	for (int i = 0; i < T; i++) {
		memset(map, -1, 17 * 17 * sizeof(int));
		read();
		minblock = 987654321;
		brute(0);
		cout << "#" << i + 1 << " " << minblock<<endl;
	}
	
	return 0;
}
