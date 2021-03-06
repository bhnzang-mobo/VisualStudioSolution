#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
int N, M, F;
int map[22][22];
int cust[401][4];
int taxi_x, taxi_y;
int dir_x[4] = { -1,0,1,0 };
int dir_y[4] = { 0,1,0,-1 };
typedef struct pos {
	int x;
	int y;
	int f;
}pos;
void read() {
	memset(map, -1, 22 * 22 * sizeof(int));//-1은 갈 수 없음.
	cin >> N >> M >> F;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				map[i][j] = -1;
			}
		}
	}
	cin >> taxi_x >> taxi_y;
	for (int i = 0; i < M; i++) {
		cin >> cust[i + 1][0] >> cust[i + 1][1] >> cust[i + 1][2] >> cust[i + 1][3];
		map[cust[i + 1][0]][cust[i + 1][1]] = i + 1;
	}
}

pair<int,int> howFarBFS() {
	int visit[22][22] = { 0, };
	pos node;
	queue<pos> myqueue;
	node.x = taxi_x;
	node.y = taxi_y;
	node.f = 0;
	
	visit[taxi_x][taxi_y] = 1;
	myqueue.push(node);
	int flag = 0;
	int conX = 0;
	int conY = 0;
	int conF = 0;
	while (!myqueue.empty()) {
		pos tmpnode = myqueue.front();
		myqueue.pop();
		if (flag == 1) {

			if (tmpnode.f == conF && map[tmpnode.x][tmpnode.y] > 0) {//거리가같은 또다른 손님
				if (tmpnode.x < conX) {
					conX = tmpnode.x;
					conY = tmpnode.y;
					conF = tmpnode.f;
				}
				else if (tmpnode.x == conX) {
					if (tmpnode.y < conY) {
						conX = tmpnode.x;
						conY = tmpnode.y;
						conF = tmpnode.f;
					}
				}
			}
			continue;
		}
		if (map[tmpnode.x][tmpnode.y] > 0) {//처음 손님을 만났을 때
			flag = 1;
			conX = tmpnode.x;
			conY = tmpnode.y;
			conF = tmpnode.f;
		}

		for (int i = 0; i < 4; i++) {
			int dx = tmpnode.x + dir_x[i];
			int dy = tmpnode.y + dir_y[i];
			int df = tmpnode.f + 1;
			if (visit[dx][dy] != 1 && map[dx][dy] >=0) {
				visit[dx][dy] = 1;
				pos newnode = {dx,dy,df};
				myqueue.push(newnode);
			}
		}
	}
	if (flag == 1) {
		return make_pair(map[conX][conY],conF);
	}
	return make_pair(-1, -1);//손님을 만날 수 없다 : 길이 막혔음!
}

int dstCost(int x,int y) {
	int visit[22][22] = { 0, };
	pos node;
	queue<pos> myqueue;
	node.x = taxi_x;
	node.y = taxi_y;
	node.f = 0;

	visit[taxi_x][taxi_y] = 1;
	myqueue.push(node);

	while (!myqueue.empty()) {
		pos tmpnode = myqueue.front();
		myqueue.pop();
		if (tmpnode.x==x && tmpnode.y==y) {
			return tmpnode.f;
		}
		for (int i = 0; i < 4; i++) {
			int dx = tmpnode.x + dir_x[i];
			int dy = tmpnode.y + dir_y[i];
			int df = tmpnode.f + 1;
			if (visit[dx][dy] != 1 && map[dx][dy] >= 0) {
				visit[dx][dy] = 1;
				pos newnode = { dx,dy,df };
				myqueue.push(newnode);
			}
		}
	}
	return -1;
}

int taxi() {

	pair<int, int> navi;
	for (int i = 0; i < M; i++) {
		navi = howFarBFS();
		if (navi.first == -1 || F<=navi.second) { //길이 막히거나, 연료가 부족한 경우
			return -1;
		}
		F -= navi.second;
		taxi_x = cust[navi.first][0];
		taxi_y = cust[navi.first][1];
		map[taxi_x][taxi_y] = 0;
		int cost = dstCost(cust[navi.first][2], cust[navi.first][3]);
		if (cost!=-1 && F >= cost) {//도착지까지 연료 충분!
			F += cost;
			taxi_x = cust[navi.first][2];
			taxi_y = cust[navi.first][3];
		}
		else {//도착지까지 연료가 부족 or 도착지가 없는 경우
			return -1;
		}
	}
	return F;
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	cout << taxi();

	return 0;
}

