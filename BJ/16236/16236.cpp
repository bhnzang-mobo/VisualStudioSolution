#include <iostream>
#include <array>
#include <algorithm>
#include <math.h>
#include <queue>
#pragma warning(disable : 4996)
using namespace std;
int map[20][20];
int N,ret,total_array_idx, array_idx,babe_size;
typedef struct __node {
	int first;
	int second;
	int dis;
}node;
pair<int, int> babe_pos;
node arr[400];
pair<int, int> totalarr[400];
queue<node> path;
int canBite(node);
int distance(node a ) {
	return canBite(a);
}

bool comp(node a,node b) {
	int dis_a = a.dis;
	int dis_b = b.dis;
	if (dis_a < dis_b) {
		return true;
	}
	else if (dis_a == dis_b) {
		if (a.first < b.first) {
			return true;
		}
		else if (a.first == b.first) {
			if (a.second < b.second) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void read() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int mob;
			cin >> mob;
			map[i][j] = mob;
			if (mob != 0) {
				if (mob == 9) {
					babe_pos = make_pair(i, j);
				}
				else {
					totalarr[total_array_idx++] = make_pair(i, j);
				}
			}
		}
	}
}
void findnewfish() {
	for (int i = 0; i < total_array_idx; ) {
		if (babe_size > map[totalarr[i].first][totalarr[i].second]) {
			node tmp;
			tmp.first = totalarr[i].first;
			tmp.second = totalarr[i].second;
			int can = canBite(tmp);
			if (can >0) {
				tmp.dis = can;
				arr[array_idx++] = tmp;
				swap(totalarr[i], totalarr[total_array_idx - 1]);
				total_array_idx--;
			}
			else {
				i++;
			}
		}
		else {
			i++;
		}
	}
	for (int i = 0; i < array_idx; i++) {
		arr[i].dis = canBite(arr[i]);
	}
	sort(arr, arr+ array_idx,comp);
	reverse(arr, arr + array_idx);
}
int canBite(node a) {
	queue<node> somequeue;
	swap(path, somequeue);
	//물고기의 위치에서 아기상어 위치를 역으로 탐색
	int tmparr[20][20] = { 0, };
	pair<int, int> dir[4] = { make_pair(-1,0),make_pair(0,1),make_pair(1,0),make_pair(0,-1) };
	tmparr[a.first][a.second] = 1;
	node tmp;
	tmp.first = a.first;
	tmp.second = a.second;
	tmp.dis = 0;
	path.push(tmp);
	int dis_idx;
	while (!path.empty()) {
		tmp = path.front();
		path.pop();
		dis_idx = tmp.dis + 1;
		for (int i = 0; i < 4; i++) {//이 방향 지나갈수 있어?
			int x = tmp.first + dir[i].first;
			int y = tmp.second + dir[i].second;
			if (0 <= x && x < N && 0 <= y && y < N) {
				if (map[x][y] == 9) {
					return dis_idx;
				}
				if (tmparr[x][y] == 0) {//갈수있는경우
					if (map[x][y] == 0) {//갈수있는 빈공간
						node newnode;
						newnode.first = x;
						newnode.second = y;
						newnode.dis = dis_idx;
						path.push(newnode);
						tmparr[x][y] = 1;
					}
					else if (map[x][y] <= babe_size) {//갈수있는 물고기 공간
						node newnode;
						newnode.first = x;
						newnode.second = y;
						newnode.dis = dis_idx;
						path.push(newnode);
						tmparr[x][y] = 1;
					}
					else {
						continue;
					}
				}
				else {
					continue;
				}

			}
		}
	}
	return -1;
}

void cal() {
	int fish_count = 0;
	while (array_idx > 0) {
		node tmp = arr[array_idx - 1];
		fish_count++;
		if (fish_count == babe_size) {
			fish_count = 0;
			ret += canBite(tmp);
			babe_size += 1;
			map[tmp.first][tmp.second] = 9;
			map[babe_pos.first][babe_pos.second] = 0;
			babe_pos.first = tmp.first;
			babe_pos.second = tmp.second;
			array_idx--;
			findnewfish();
			sort(arr, arr + array_idx, comp);
			reverse(arr, arr + array_idx);
		}
		else {
			ret += canBite(tmp);
			map[tmp.first][tmp.second] = 9;
			map[babe_pos.first][babe_pos.second] = 0;
			babe_pos.first = tmp.first;
			babe_pos.second = tmp.second;
			array_idx--;
			for (int i = 0; i < array_idx; i++) {
				arr[i].dis = canBite(arr[i]);
			}
			sort(arr, arr + array_idx, comp);
			reverse(arr, arr + array_idx);
		}
		// 먹고, 배열에 맨 마지막 원소와 swap한뒤 재정렬
		// 포식 불가능
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	babe_size = 2;
	findnewfish();
	cal();
    std::cout << ret; 
}
