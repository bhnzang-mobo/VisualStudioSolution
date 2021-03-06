// 14501.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#pragma warning(disable:4996)
#include <iostream>
using namespace std;
int N;
int arr[16][2];
int dparr[16][16];
void read() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i][0] >> arr[i][1];
	}
}
int max(int a, int b) {
	return (a > b ? a : b);
}
void dp(){
	for (int i = 1; i <= N; i++) {
		if (i >= arr[0][0]) {
			dparr[0][i] = arr[0][1];
		}
	}
	for (int i = 1; i < N; i++) {
		for (int j = 1; j <= N; j++) {
		//i = index , j = num
			if (j >= arr[i][0]+i) {
				dparr[i][j] = max(arr[i][1] + dparr[i-1][i],dparr[i-1][j]);
			}
			else {
				dparr[i][j] = dparr[i - 1][j];
			}
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	dp();
	std::cout << dparr[N - 1][N];
}

