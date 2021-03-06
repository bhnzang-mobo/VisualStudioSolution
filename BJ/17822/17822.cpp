#include "pch.h"
#pragma warning (disable : 4996)
#include <iostream>
#include <queue>
using namespace std;
int circle[51][52];
int N, M, T;
int tasks[50][3];

void read() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> circle[i][j];
		}
		circle[i][0] = circle[i][M]; 
		circle[i][M + 1] = circle[i][1];
	}
	for (int i = 0; i < T; i++) {
		cin >> tasks[i][0] >> tasks[i][1] >> tasks[i][2];
	}
}
void rotate(int idx, int t) {
	if (t == 0) {
		return;
	}
	if (t > 0) {
		for (int i = 0; i < t; i++) {
			for (int j = M; j >= 1; j--) {
				circle[idx][j] = circle[idx][j - 1];
			}
			circle[idx][0] = circle[idx][M];
			circle[idx][M + 1] = circle[idx][1];
		}
	}
	else {
		for (int i = 0; i > t; i--) {
			for (int j = 1; j <= M; j++) {
				circle[idx][j] = circle[idx][j + 1];
			}
			circle[idx][0] = circle[idx][M];
			circle[idx][M + 1] = circle[idx][1];
		}
	}
}

void delnode(int x, int y) {
	if (y == 1) circle[x][M + 1] = 0;
	if (y == M) circle[x][0]=0;
	circle[x][y] = 0;
}

void del() {
	float total = 0;
	int quo = 0;
	for (int i = 1; i <= N; i++) {
		for (int k = 1; k <= M; k++) {
			if (circle[i][k] == 0) continue;
			total += circle[i][k];
			quo++;
		}
	}
	
	if (quo != 0) {
		total /= quo;
		for (int i = 1; i <= N; i++) {
			for (int k = 1; k <= M; k++) {
				if (circle[i][k] == 0) continue;
				if (total > circle[i][k]) {
					circle[i][k]++;
					circle[i][0] = circle[i][M];
					circle[i][M + 1] = circle[i][1];
				}
				else if (total < circle[i][k]) {
					circle[i][k]--;
					circle[i][0] = circle[i][M];
					circle[i][M + 1] = circle[i][1];
				}
			}
		}
	}

}

int BFS() {
	int flag = 0;
	for (int i = N; i >=1; i--) {
		for (int j = 1; j <= M; j++) {
			int now = circle[i][j];
			if (now == 0) continue;
			queue<pair<int, int> > circle_idx;
			
			if (now == circle[i][j - 1]) {
				flag = 1;
				delnode(i, j);
				if (j - 1 == 0) {
					delnode(i, M);
					circle_idx.push(make_pair(i, M));
				}
				else {
					circle_idx.push(make_pair(i, j-1));
				}
			}

			if (now == circle[i][j + 1]) {
				flag = 1;
				delnode(i, j);
				if (j + 1 == M+1) {
					delnode(i, 1);
					circle_idx.push(make_pair(i, 1));
				}
				else {
					delnode(i, j+1);
					circle_idx.push(make_pair(i, j+1));
				}
			}
			if (i<N && now == circle[i + 1][j]) {
				flag = 1;
				delnode(i, j);
				delnode(i+1, j);
				circle_idx.push(make_pair(i + 1, j));
			}
			if (i>1 && now == circle[i - 1][j]) {
				flag = 1;
				delnode(i, j);
				delnode(i-1, j);
				circle_idx.push(make_pair(i-1, j));
			}


			while (!circle_idx.empty()) {//flag 가 0이면 실행되지 않는다.
				pair<int, int> pos = circle_idx.front();
				circle_idx.pop();


				if (now == circle[pos.first][pos.second - 1]) {
					if (pos.second - 1 == 0) {
						delnode(pos.first, M);
						circle_idx.push(make_pair(pos.first, M));
					}
					else {
						delnode(pos.first, pos.second-1);
						circle_idx.push(make_pair(pos.first, pos.second - 1));
					}
				}

				if (now == circle[pos.first][pos.second + 1]) {
	
					if (pos.second + 1 == M+1) {
						delnode(pos.first, 1);
						circle_idx.push(make_pair(pos.first, 1));
					}
					else {
						delnode(pos.first, pos.second+1);
						circle_idx.push(make_pair(pos.first, pos.second+1));
					}
				}

				if (pos.first < N && now == circle[pos.first + 1][pos.second]) {
					delnode(pos.first+1, pos.second);
					circle_idx.push(make_pair(pos.first + 1, pos.second));
				}
				if (pos.first > 1 && now == circle[pos.first - 1][pos.second]) {
					delnode(pos.first-1, pos.second);
					circle_idx.push(make_pair(pos.first - 1, pos.second));
				}
			}

		}
	}
	return flag;
}

int main()
{
	freopen("input.txt", "r", stdin);
	read();
	for (int i = 0; i < T; i++) {
		for (int j = 1; j <= N; j++) {
			if (j%tasks[i][0] == 0) {
				if (tasks[i][1] == 0) {//시계
					rotate(j, tasks[i][2]);
				}
				else {//반시계
					rotate(j, -1 * (tasks[i][2]));
				}
				
			}
		}
		if (BFS() == 0) {
			del();
		}
		
	}
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (circle[i][j] > 0) {
				ret += circle[i][j];
			}
		}
	}
	cout << ret;
	return 0;
}

