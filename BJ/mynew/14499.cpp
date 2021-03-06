// mynew.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "pch.h"
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
/*
크기가 N×M인 지도가 존재한다. 지도의 오른쪽은 동쪽, 위쪽은 북쪽이다. 
이 지도의 위에 주사위가 하나 놓여져 있으며, 주사위의 전개도는 아래와 같다. 
지도의 좌표는 (r, c)로 나타내며, r는 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로부터 떨어진 칸의 개수이다. ->row col 개념

  2
4 1 3
  5
  6

주사위는 지도 위에 윗 면이 1이고, 동쪽을 바라보는 방향이 3인 상태로 놓여져 있으며, 놓여져 있는 곳의 좌표는 (x, y) 이다. 
가장 처음에 주사위에는 모든 면에 0이 적혀져 있다.

지도의 각 칸에는 정수가 하나씩 쓰여져 있다. 주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다.
0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.

주사위를 놓은 곳의 좌표와 이동시키는 명령이 주어졌을 때, 주사위가 이동했을 때 마다 상단에 쓰여 있는 값을 구하는 프로그램을 작성하시오.

주사위는 지도의 바깥으로 이동시킬 수 없다. 만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.

입력
첫째 줄에 지도의 세로 크기 N, 가로 크기 M (1 ≤ N, M ≤ 20), 주사위를 놓은 곳의 좌표 x y(0 ≤ x ≤ N-1, 0 ≤ y ≤ M-1),
그리고 명령의 개수 K (1 ≤ K ≤ 1,000)가 주어진다.

둘째 줄부터 N개의 줄에 지도에 쓰여 있는 수가 북쪽부터 남쪽으로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다.
주사위를 놓은 칸에 쓰여 있는 수는 항상 0이다. 지도의 각 칸에 쓰여 있는 수는 10을 넘지 않는 자연수 또는 0이다.

마지막 줄에는 이동하는 명령이 순서대로 주어진다. 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4로 주어진다.

출력
이동할 때마다 주사위의 윗 면에 쓰여 있는 수를 출력한다. 만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.
*/
int map[22][22];
int x, y, K,N,M;
int dice[2][4];
int *bottom, *up;
void rolldice(int a) {
	int tmp;
	switch (a)
	{
	case 1:
		tmp = dice[0][3];
		for (int i = 3; i >0; i--) {
			dice[0][i] = dice[0][i-1];
		}
		dice[0][0] = tmp;
		dice[1][0] = *up;
		dice[1][2] = *bottom;
		break;
	case 2:
		tmp = *up;
		for (int i = 0; i < 3; i++) {
			dice[0][i] = dice[0][i + 1];
		}
		dice[0][3] = tmp;
		dice[1][0] = *up;
		dice[1][2] = *bottom;
		break;
	case 3:
		tmp = dice[1][3];
		for (int i = 3; i >0; i--) {
			dice[1][i] = dice[1][i-1];
		}
		dice[1][0] = tmp;
		dice[0][0] = dice[1][0];
		dice[0][2] = dice[1][2];
		break;
	case 4:
		tmp = dice[1][0];
		for (int i = 0; i < 3; i++) {
			dice[1][i] = dice[1][i + 1];
		}
		dice[1][3] = tmp;
		dice[0][0] = dice[1][0];
		dice[0][2] = dice[1][2];
		break;

	default:	
		break;
	}
	cout << *up <<endl;
}
void read() {
	cin >> N >> M >> x >> y >> K;
	x++;
	y++;
	memset(map, -1, 22 * 22 * sizeof(int));
	for (int i = 1; i <= N; i++) {
		for(int j = 1; j <= M ; j ++){
			cin >> map[i][j];
		}
	}
}

void play() {
	int dirx[4] = { 0,0,-1,1 };
	int diry[4] = { 1,-1,0,0 };
	for (int i = 0; i < K; i++) {
		int task,dx,dy;
		cin >> task;
		dx = x  + dirx[task - 1];
		dy = y  + diry[task - 1];
		int dst = map[dx][dy];
		if (dst != -1) {
			x = dx;
			y = dy;
			rolldice(task);
			if (dst == 0) {
				map[dx][dy] = *bottom;
			}
			else {
				map[dx][dy] = 0;
				*bottom = dst;
				dice[1][2] = dst;
				dice[0][2] = dst;
			}
		}
		else {
			continue;
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	bottom = &(dice[0][2]);
	up = &(dice[0][0]);
	*bottom = map[x][y];
	play();
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
