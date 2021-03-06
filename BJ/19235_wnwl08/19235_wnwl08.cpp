#include "pch.h"
#pragma warning(disable : 4996)
#include <stdio.h>


int blocks[2][8][5];
int score;

void pull(int st) {
	bool flg = false;
	int idx = 1;
	for (int i = 0; i < 4; i++) {
		if (blocks[st][1][i] != 0) {
			flg = true;
			if (blocks[st][0][i] != 0)idx = 2; // 즉 , 두 행에 블록이 모두 존재해 2줄을 지워야 하는경우
			break;
		}
	}
	if (flg) {
		for (int i = 5; i >= 2; i--) {
			for (int j = 0; j < 4; j++) {
				blocks[st][i][j] = blocks[st][i - idx][j];//위에 있는것 가져오면 그만. 물론 맨 믿에서부터!
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++)blocks[st][i][j] = 0;//밝은 부분 초기화
	}
}
void drop1(int st, int xx, int yy) {
	// (xx, yy)
	while (1) {
		if (xx == 5)break;
		if (blocks[st][xx + 1][yy] != 0)break;
		xx++;
	}
	blocks[st][xx][yy] = 1;
}
void drop2(int st, int xx, int yy) {//garo
	// (xx, yy), (xx, yy+1)
	while (1) {
		if (xx == 5)break;
		if ((blocks[st][xx + 1][yy] != 0) || (blocks[st][xx + 1][yy + 1]))break;
		xx++;
	}
	blocks[st][xx][yy] = 2;
	blocks[st][xx][yy + 1] = 2;
}
void gravity(int st) {
	for (int i = 5; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (blocks[st][i][j] == 1) {
				blocks[st][i][j] = 0;
				drop1(st, i, j); //drop함수를 주어진 위치에서 떨구는걸로 구현한 이유
			}
			else if (blocks[st][i][j] == 2) {
				blocks[st][i][j] = 0;
				blocks[st][i][j + 1] = 0;
				drop2(st, i, j);
				j++;
			}
		}
	}
}
bool get_score(int st) {
	bool inc = false;
	for (int i = 5; i >= 0; i--) {
		bool comp = true;
		for (int j = 0; j < 4; j++) {
			if (blocks[st][i][j] == 0) { 
				comp = false;
				break;
			}
		}
		if (comp) {
			inc = true;
			score++;
			for (int j = 0; j < 4; j++) {
				blocks[st][i][j] = 0;
			}
		}
	}
	return inc;
}

int main() {
	int N, pos, xx, yy;
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &pos, &xx, &yy);
		if (pos == 1) {
			drop1(0, 0, yy);
			drop1(1, 0, 3 - xx);
		}
		else if (pos == 2) {
			drop2(0, 0, yy);;//가로로 떨궈짐. 직접 계산해야함.
			drop1(1, 0, 3 - xx);//세로로 떨궈짐. 연속으로 1짜리 두개를 떨구는것과 같다
			drop1(1, 0, 3 - xx);
		}
		else {
			drop1(0, 0, yy);
			drop1(0, 0, yy);
			drop2(1, 0, 2 - xx);
		}
		while (get_score(0))gravity(0);
		while (get_score(1))gravity(1);
		pull(0);
		pull(1);

	}

	while (get_score(0))gravity(0);
	while (get_score(1))gravity(1);

	printf("%d\n", score);
	int cnt = 0;
	for (int k = 0; k < 2; k++) {
		for (int i = 2; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[k][i][j] != 0)cnt++;
			}
		}
	}
	printf("%d\n", cnt);
}