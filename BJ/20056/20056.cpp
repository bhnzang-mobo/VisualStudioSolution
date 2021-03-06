#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <queue>
using namespace std;
int N, M, K;
typedef struct _pos {
	int x;
	int y;
	int mass;
	int speed;
	int direct;
}planet;
queue<planet> myqueue[52][52];

int dir_x[8] = { -1,-1,0,1,1,1,0,-1 };
int dir_y[8] = { 0,1,1,1,0,-1,-1,-1 };

int isCollide() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (myqueue[i][j].size() > 1) {
				return 1;
			}
		}
	}
	return 0;
}
void boom(int x, int y, int totalmass, int totalspeed, int dir, int quan) {
	int mass = totalmass / 5;
	int speed = totalspeed / quan;
	if (mass == 0 || speed == 0) return;

	if (dir == 0) {
		for (int i = 0; i < 7; i += 2) {
			planet node = { x,y,mass,speed,i };
			myqueue[x][y].push(node);
		}
	}
	else {
		for (int i = 1; i <= 7; i += 2) {
			planet node = { x,y,mass,speed,i };
			myqueue[x][y].push(node);
		}
	}
}

void collision() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (myqueue[i][j].size() >= 2) {
				int totalmass = 0;
				int totalspeed = 0;
				int numOfEven = 0;
				int numOfOdd = 0;
				int quan = 0;
				while (!myqueue[i][j].empty()) {
					planet node = myqueue[i][j].front();
					myqueue[i][j].pop();
					totalmass += node.mass;
					totalspeed += node.speed;
					quan++;
					if (node.direct % 2 == 0) {
						numOfEven++;
					}
					else {
						numOfOdd++;
					}	
				}
				if (numOfEven == quan || numOfOdd == quan) {
					boom(i, j, totalmass, totalspeed, 0, quan);

				}
				else {
					boom(i, j, totalmass, totalspeed, 1, quan);
				}
			}
		}
	}
}

void moveplanet() {

	queue<planet> bigqueue;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (myqueue[i][j].size() > 0) {
				while (!myqueue[i][j].empty()) {
					bigqueue.push(myqueue[i][j].front());
					myqueue[i][j].pop();
				}
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			while (!bigqueue.empty()) {
				planet node = bigqueue.front();
				bigqueue.pop();
				int dx = node.x + node.speed*dir_x[node.direct];
				int dy = node.y + node.speed*dir_y[node.direct];
				while (dx < 0) {
					dx += N;
				}
				while (dx >= N) {
					dx -= N;
				}
				while (dy < 0) {
					dy += N;
				}
				while (dy >= N) {
					dy -= N;
				}
				planet newnode = { dx,dy,node.mass,node.speed,node.direct };
				myqueue[dx][dy].push(newnode);
			}
		}
	}
}

void read() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		planet node;
		cin >> node.x >> node.y >> node.mass >> node.speed >> node.direct;
		node.x--;
		node.y--;
		myqueue[node.x][node.y].push(node);
	}
}

int howmany() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (myqueue[i][j].size() > 0) {
				while (!myqueue[i][j].empty()) {
					ret += myqueue[i][j].front().mass;
					myqueue[i][j].pop();
				}
			}
		}
	}
	return ret;
}
void play() {
	int times = 0;
	while (times<K) {
		times++;
		if (isCollide() == 1) {
			collision();
		}
		moveplanet();
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	read();

	play();
	collision();
	cout << howmany();
	return 0;
}
