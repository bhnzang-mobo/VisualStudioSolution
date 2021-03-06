#include "pch.h"
#pragma	 warning(disable : 4996)
#include <iostream>
#include <queue>
#include <string.h>

using namespace std;
typedef struct pos {
	int x;
	int y;
	int idx;
}pos;
typedef struct qnode {
	int x;
	int y;
	int level;
}qnode;
int N, M, F,m_count;
pos bj;
int map[22][22];
pos ori[401];
pos dst[401];

void read() {
	cin >> N >> M >> F;
	memset(map, -1, 22 * 22 * sizeof(int));
	for (int i = 1 ; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	cin >> bj.x >> bj.y;
	for (int i = 0; i < M; i++) {
		cin >> ori[i].x >> ori[i].y >> dst[i].x >> dst[i].y;
		
	}
}
int isCustomer(int x, int y) {
	for (int i = 0; i < M; i++) {
		if(ori[i].x == x && ori[i].y==y){
			return i;
		}
	}
	return -1;
}

int isDestinate(int x, int y, int dx, int dy) {
	if (x == dx && y == dy) {
		return 1;
	}
	else { 
		return 0; 
	}
}
int cal() {
	queue<qnode> myqueue;
	queue<qnode>emptyqueue;
	qnode node;
	int dir_x[4] = { -1,0,1,0 };
	int dir_y[4] = { 0,1,0,-1 };
	int success = 1;
	int flag = 0;
	while (success) {
		swap(myqueue, emptyqueue);
		success = 0;
		int suc_lev = 99999;
		int visit[22][22] = { 0, };
		node.x = bj.x;
		node.y = bj.y;
		node.level = 0;
		visit[node.x][node.y] = 1;
		myqueue.push(node);
		while (!myqueue.empty()&&m_count <M) {
			qnode tmp = myqueue.front();
			myqueue.pop();
			int cur_level;
			node.x = tmp.x;
			node.y = tmp.y;
			node.level = tmp.level;
			cur_level = tmp.level;
			if (success == 1 && cur_level >= suc_lev) continue;
			for (int i = 0; i < 4; i++) {
				int cu = isCustomer(node.x, node.y);
				if (cu > -1) {
					success = 1;
					flag = 1;
					suc_lev = 0;
					cout << "손님을 받았습니다. 출발지 : " << bj.x << " " << bj.y << "목적지 : " << dst[cu].x << " " << dst[cu].y << endl;
					cout << "연료가 소모되지 않았습니다.." << endl;
					cout << "사용후.." << F << endl;
					bj.idx = cu;
					break;
				}
				int dx = node.x + dir_x[i];
				int dy = node.y + dir_y[i];
				if (map[dx][dy] != -1 && map[dx][dy] != 1 && visit[dx][dy]!=1) {
					if (success== 0 && F <= cur_level) {
						success = 0;
						F = -1;
						return -1;
					}
					int custom = isCustomer(dx, dy);
					if (success == 0) {
						if (custom> -1) {
							success = 1;
							flag = 1;
							suc_lev = cur_level + 1;
							cout << "손님을 받았습니다. 출발지 : " << bj.x << " " << bj.y << "목적지 : " << dx <<" "<< dy<<endl;
							bj.x = dx;
							bj.y = dy;
							visit[dx][dy] = 1;
							cout << "연료가 소모되었습니다 : " << F <<"에서" <<suc_lev <<"만큼 사용했습니다.";
							F -= suc_lev;
							cout << "사용후.." << F << endl;
							bj.idx = custom;
						}
						else {
							qnode newnode;
							newnode.x = dx;
							newnode.y = dy;
							newnode.level = cur_level + 1;
							visit[dx][dy] = 1;
							myqueue.push(newnode);
						}
					}
					else {
						if (custom > -1 && suc_lev>=cur_level+1) {
							if (bj.x > dx) {
								bj.x = dx;
								bj.y = dy;
								visit[dx][dy] = 1;
								bj.idx = custom;
							}
							else if (bj.x == dx) {
								if (bj.y > dy) {
									bj.x = dx;
									bj.y = dy;
									visit[dx][dy] = 1;
									bj.idx = custom;
								}
							}
						}
					}
					
				}
				else {
					continue;
				}
			}
		}
		if (success == 1) {
			int flag_dest=0;
			ori[bj.idx].x = -1;
			ori[bj.idx].y = -1;
			queue<qnode> destqueue;
			int dest_x = dst[bj.idx].x;
			int dest_y = dst[bj.idx].y;
			int dstvisit[22][22] = { 0, };
			qnode dest = {bj.x,bj.y,0};
			qnode dstnode;
			dstvisit[bj.x][bj.y] = 1;
			destqueue.push(dest);
			while (!destqueue.empty()) {
				qnode tmp = destqueue.front();
				destqueue.pop();
				int cur_level;
				dstnode.x = tmp.x;
				dstnode.y = tmp.y;
				dstnode.level = tmp.level;
				cur_level = tmp.level;
				for (int i = 0; i < 4; i++) {
					int dx = dstnode.x + dir_x[i];
					int dy = dstnode.y + dir_y[i];
					if (map[dx][dy] != -1 && map[dx][dy] != 1 && dstvisit[dx][dy] != 1 ) {
						if (F <= cur_level) {
							continue;
						}
						int custom = isDestinate(dx, dy, dest_x, dest_y);
						if (custom > 0) {
							flag_dest = 1;
							m_count++;
							cout << "목적지에 도착했습니다. 출발지 : " << bj.x << " " << bj.y << "도착지 " << dx << " " << dy << endl;
							bj.x = dx;
							bj.y = dy;
							cout << "연료를 충전했습니다 : " << F << "에서" << cur_level+1<< "만큼 충전했습니다.";
							F += (cur_level + 1);
							cout << "충전후.." << F << endl;
							dstvisit[dx][dy] = 1;
							break;
						}
						else {
							qnode newnode;
							newnode.x = dx;
							newnode.y = dy;
							newnode.level = cur_level + 1;
							dstvisit[dx][dy] = 1;
							destqueue.push(newnode);
						}
					}
					else {
						continue;
					}
				}
			}
			if (flag_dest == 0) {
				cout << -1;
				return -1;
			}
		}
	}
	if (flag == 0) {
		cout << -1;
		return 0;
	}
	cout << F;
	return F;
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	cal();
}

