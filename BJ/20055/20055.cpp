#include "pch.h"
#pragma warning(disable:4996)
#include <iostream>
//삼성 코딩테스트 정확하게 풀이하는데 40분걸렸던 문제
using namespace std;
int N, K;
int walk[202];
int onperson[102];
void read() {
	cin >> N >> K;
	for (int i = 1; i <= 2*N; i++) {//순환구조의 무빙워크
		cin >> walk[i];
	}
	walk[0] = walk[2 * N ];
	walk[2 * N + 1] = walk[1];
}

void operate() {
	for (int i = 2 * N; i >= 0; i--) {//무빙워크의 회전입니다.
		walk[i + 1] = walk[i];
	}
	walk[0] = walk[2 * N];
	if (onperson[N] == 1) {
		onperson[N] = 0;//사람은 내립니다.
	}
}
void operate_walk() {//사람의 움직임 입니다. N번째에 사람은 없다고 가정.
	for (int i = N - 1; i >= 0; i--) {
		onperson[i + 1] = onperson[i];
	}
	if (onperson[N] == 1) {
		onperson[N] = 0;//사람은 내립니다.
	}
}

void move_walk() {//사람의 발에의한 움직임 입니다.
	for (int i = N - 1; i >= 1; i--) {//무빙워크의 회전에 의한 사람의 움직임 입니다.
		if (onperson[i] == 1) {
			if (onperson[i + 1] != 1) {//다음에 사람이 없는경우
				if (walk[i + 1] > 0) {//올라설 수 있는경우
					walk[i + 1]--;
					onperson[i + 1] = 1;
					onperson[i] = 0;
				}
			}//사람이 있거나 올라설 수 없는 경우엔 가만히 있는다.
			
		}
	}
	if (onperson[N] == 1) {
		onperson[N] = 0;//마지막 사람은 내립니다.
	}
	if (walk[1] > 0) {//첫번째 자리에 사람을 추가합니다.
		onperson[1] = 1;
		walk[1]--;
	}
}

int howmany() {
	int ret = 0;
	for (int i = 1; i <= 2 * N; i++) {
		if (walk[i] == 0) {
			ret++;
		}
	}
	return ret;
}

int play() {
	int ret = 0;
	while (howmany() < K) {
		ret++;
		operate();
		operate_walk();
		move_walk();
	}
	return ret;
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	cout << play();
	return 0;
}

