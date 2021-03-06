#include <iostream>
#include <queue>
using namespace std;
int A[70][70];
int B[70][70];
int N, Q, L;
int mypow[] = { 1,2,4,8,16,32,64,128 };
void read() {//input 획득
	cin >> N >> Q;
	for (int i = 1; i <= mypow[N]; i++) {
		for (int j = 1; j <= mypow[N]; j++) {
			cin >> A[i][j];
		}
	}
}

void rotate(int x, int y, int len) {//얼음 회전
	double mid_y;
	mid_y = (2 * y + len - 1) / 2.0;
	for (int i = 0; i < len; i++) {//y=x대칭
		for (int j = 0; j < i; j++) {
			int tmp = A[i + x][j + y];
			A[i + x][j + y] = A[j + x][i + y];
			A[j + x][i + y] = tmp;
		}
	}

	for (int i = 0; i < len; i++) {//y=mid_y대칭
		for (int j = 0; j < len/2; j++) {
			int tmp = A[i + x][j + y];
			A[i + x][j + y] = A[i + x][(int)(2 * mid_y) - (j + y)];
			A[i + x][(int)(2 * mid_y) - (j + y)] = tmp;
		}
	}
}


int howmany(int x, int y) {
	int dir_x[4] = { -1,0,1,0 };
	int dir_y[4] = { 0,1,0,-1 };
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (A[x + dir_x[i]][y + dir_y[i]] > 0) {
			count++;
		}
	}
	return count;
}

void reduce() { //인접얼음갯수 2개 이하 얼음에 대한 처리
	queue< pair<int, int>> myqueue;
	for (int i = 1; i <= mypow[N]; i++) {
		for (int j = 1; j <= mypow[N]; j++) {
			if (A[i][j] == 0) continue;
			if (howmany(i, j) <= 2) {
				myqueue.push(make_pair(i, j));
			}
		}
	}

	pair<int, int> mypair;
	while (!myqueue.empty()){
		mypair = myqueue.front();
		myqueue.pop();
		A[mypair.first][mypair.second]--;
	}

	int total = 0;
	for (int i = 1; i <= mypow[N]; i++) {
		for (int j = 1; j <= mypow[N]; j++) {
			total += A[i][j];
		}
	}
}


void result() {
	int total = 0;
	int hasVisit[70][70] = { 0, };
	int dir_x[4] = { -1,0,1,0 };
	int dir_y[4] = { 0,1,0,-1 };

	queue< pair<int, int>> bfs;
	int max = 1;
	for (int i = 1; i <= mypow[N]; i ++) {
		for (int j = 1; j <= mypow[N]; j ++) {
			total += A[i][j];
		}
	}
	for (int i = 1; i <= mypow[N]; i++) {
		for (int j = 1; j <= mypow[N]; j++) {
			int count = 0;

			if (A[i][j] != 0 && hasVisit[i][j] == 0) {
				hasVisit[i][j] = 1;
				bfs.push(make_pair(i, j));
				count++;
				while (!bfs.empty()) {
					pair<int, int> cur = bfs.front();
					bfs.pop();

					int dx, dy;
					for (int k = 0; k < 4; k++) {
						dx = cur.first + dir_x[k];
						dy = cur.second + dir_y[k];
						if (A[dx][dy] != 0 && hasVisit[dx][dy]==0) {
							hasVisit[dx][dy] = 1;
							bfs.push(make_pair(dx, dy));
							count++;
						}
					}
				}
				if (max < count) {
					max = count;
				}
			}
		}
	}
	if (max == 1) {
		max = 0;
	}
	cout << total << endl << max;

}


int main()
{
	freopen("input.txt","r",stdin);
	read();
	for (int i = 0; i < Q; i++) {
		cin >> L;
		int len = mypow[L];
		for (int j = 1; j < mypow[N]; j+=len) {
			for (int k = 1; k < mypow[N]; k += len) {
				rotate(j, k, len);
			}
		}
		reduce();
	}
	result();
	return 0;
}
