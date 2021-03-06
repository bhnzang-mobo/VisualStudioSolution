#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <queue>

int N;
int population[21][21];
int map[21][21];
using namespace std;
void makemap(int a,int b,int d1, int d2) {
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			if (x<=a+d2 && y>b && y - x > b - a) {//1
				map[x][y] = 2;
			}
			else if (x < a+d1 && y <= b && y + x < a+b) {//3
				map[x][y] = 1;
			}
			else if (x >= a+d1 && y < b-d1+d2 && y - x < b - a -2*d1) {//4
				map[x][y] = 3;
			}
			else if(x>a+d2 && y >= b+d2-d1 && y + x > a+b+2*d2){
				map[x][y] = 4;
			}
			else {
				map[x][y] = 5;
			}
		}
	}
}

pair<int,int> cal() {
	int ret_max = 0;
	int ret_min=987654321;
	int total;
	for (int i = 1; i <= 5; i++) {
		total = 0;
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= N; k++) {
				if (map[j][k] == i) {
					total+=population[j][k];
				}
			}
		}
		if (ret_max < total) {
			ret_max = total;
		}
		if (ret_min > total) {
			ret_min = total;
		}
	}
	return make_pair(ret_max, ret_min);
}

int brute() {
	int ret_min = 987654321;
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			for (int d1 = 1; d1 <= N; d1++) {
				for (int d2 = 1; d2 <= N; d2++) {
					if (x + d1 + d2 > N || y - d1<1 || y + d2>N) continue;
					makemap(x, y, d1, d2);
					pair<int, int> ret = cal();
					if (ret_min > ret.first - ret.second) {
						ret_min = ret.first - ret.second;
					}
				}
			}
		}
	}
	return ret_min;
}

void read() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> population[i][j];
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	cout << brute();
	return 0;
}

