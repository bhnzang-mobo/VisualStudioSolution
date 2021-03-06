#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
int hexarr[30];
unsigned long int num[30];//8~28;
int T, N, K;
int numidx;
void read() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		scanf(" %c",&hexarr[i]);
	}
	hexarr[0] = hexarr[N];
	hexarr[N + 1] = hexarr[1];
}
void rotate() {
	for (int i = N+1; i >= 1; i--) {
		hexarr[i] = hexarr[i-1];
	}
	hexarr[0] = hexarr[N];
	hexarr[N + 1] = hexarr[1];
}
int hextodec(int a) {
	if (a >= 65) {
		return a - 55;
	}
	return a-48;
}
void retrieve() {//현재 hexarr을 기준으로 숫자를 얻어낸다.
	for (int i = 0; i < 4; i++) {
		unsigned long int ret = 0;
		int buf = i * N / 4;
		for (int j = 1; j <= N / 4; j++) {
			ret += hextodec(hexarr[buf+j])*pow(16,N/4-j) ;
		}
		num[numidx++] = ret;
	}
}
int roll() {//돌려서 나올수 있는 모든 수준 K번째 로 큰수
	for (int i = 0; i < N / 4; i++) {
		rotate();
		retrieve();
	}
	sort(num, num + N);
	int now = -1;
	for (int i = N - 1; i >= 0; i--) {
		K--;
		if (K == 0) {
			return num[i];
		}
		if (now == num[i]) {
			K += 1;
			continue;
		}
		now = num[i];
	}
	return 0;
}
int main()
{
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int i = 0; i < T; i++) {
		read();
		numidx = 0;
		cout << "#"<<i+1<<" "<<roll();
		cout << endl;
	}
	return 0;

}
