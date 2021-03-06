#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

int map[400][400][2];//0은 생명력, 1은 복제된 시각
int T, N, M, K;

typedef struct _pos {
	int s;
	int x;
	int y;
	int t;
}qnode;

queue<qnode> myqueue;

int dir_x[4] = { -1,0,1,0 };
int dir_y[4] = { 0,1,0,-1 };

void read() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[175 + i][175 + j][0];
			map[175 + i][175 + j][1] = 0;
			if (map[175 + i][175 + j][0] > 0 ) {
				qnode node = { map[175 + i][175 + j][0],175 + i ,175 + j,0 };
				myqueue.push(node);
			}
		}
	}
}

int BFS() {
	int time=0;
	queue<qnode> bigqueue;

	while (!myqueue.empty()) {
		bigqueue.push(myqueue.front());
		myqueue.pop();
	}

	while (!bigqueue.empty()) {

		while (!bigqueue.empty()) {
			myqueue.push(bigqueue.front());
			bigqueue.pop();
		}
		time += 1;

		while (!myqueue.empty()) {
			qnode node = myqueue.front();
			myqueue.pop();
			if (map[node.x][node.y][0] > node.s)continue; // 덮어 씌워진경우
			
			if (time == node.s + node.t + 1) {//복제
				for (int i = 0; i < 4; i++) {
					int dx = node.x + dir_x[i];
					int dy = node.y + dir_y[i];
					if (map[dx][dy][0] == 0) {
						map[dx][dy][0] = node.s;
						map[dx][dy][1] = time;
						qnode newnode = { node.s,dx,dy,time };
						bigqueue.push(newnode);
					}
					else {
						if (map[dx][dy][1] == time) {
							if (map[dx][dy][0] < node.s) {
								map[dx][dy][0] = node.s;
								map[dx][dy][1] = time;

								qnode newnode = { node.s,dx,dy,time };
								bigqueue.push(newnode);
							}
						}
					}
				}
			}
			if (time != 2*node.s + node.t) {//죽는 노드는 아님
				bigqueue.push(node);
			}

		}
		if (time == K) {//동시에 겹친 노드는 두개가 들어가있다.
			int ret = 0;
			while (!bigqueue.empty()) {
				qnode newnode = bigqueue.front();
				bigqueue.pop();
				if (map[newnode.x][newnode.y][0] == newnode.s) {
					ret++;
				}
			}
			return ret;
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int i = 0; i < T; i++) {
		queue<qnode> someting;
		swap(someting, myqueue);
		memset(map,0, 400 * 400 * 2 * sizeof(int));
		read();
		cout << "#"<<i+1<<" "<<BFS();
		cout << endl;
	}
	return 0;
}
