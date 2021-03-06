
#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <queue>
using namespace std;

int N;
int t, x, y,idx,score;

int paneR[5][5];
int paneG[6][4];
int paneB[4][6];

int blocks[10001];


typedef struct __myblock{
	int type;
	int x1,y1;
	int x2,y2;
}myblock;
void showmeG() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << paneG[i][j];
		}
		cout << endl;
	}
}
void showmeB() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			cout << paneB[i][j];
		}
		cout << endl;
	}
}
struct compG {
	bool operator()(myblock b, myblock a) {
		int a_x, a_y, b_x, b_y;
		a_x = (a.x1 > a.x2 ? a.x1 : a.x2);
		a_y = (a.y1 < a.y2 ? a.y1 : a.y2);
		b_x = (b.x1 > b.x2 ? b.x1 : b.x2);
		b_y = (b.y1 < b.y2 ? b.y1 : b.y2);
		if (a_x > b_x) {
			return true;
		}
		else if (a_x == b_x) {
			if (a_y < b_y) {
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
};
struct compB {
	bool operator()(myblock a, myblock b) {
		int a_x, a_y, b_x, b_y;
		a_x = (a.x1 < a.x2 ? a.x1 : a.x2);
		a_y = (a.y1 > a.y2 ? a.y1 : a.y2);
		b_x = (b.x1 < b.x2 ? b.x1 : b.x2);
		b_y = (b.y1 > b.y2 ? b.y1 : b.y2);
		if (a_y < b_y) {
			return true;
		}
		else if (a_y == b_y) {
			if (a_x > b_x) {
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
};

priority_queue<myblock, vector<myblock>, compG> G_Block;
priority_queue<myblock, vector<myblock>, compB> B_Block;
int cangoG(myblock qnode) {
	if (0 <= qnode.x1 && qnode.x1 < 50) {
		if (0 <= qnode.x2 && qnode.x2 < 50) {
			if (qnode.x1 >= 5 || qnode.x2 >= 5) {
				return 0;
			}
			if (qnode.y1 == qnode.y2) {
				if (paneG[qnode.x2 + 1][qnode.y2] == 0) {
					return 1;
				}
			}
			if (paneG[qnode.x1 + 1][qnode.y1] == 0 && paneG[qnode.x2 + 1][qnode.y2] == 0) {
				return 1;
			}
		}
		else {
			if (qnode.x1 >= 5) {
				return 0;
			}
			if (paneG[qnode.x1 + 1][qnode.y1] == 0) {
				return 1;
			}
		}
	}
	else {
		if (qnode.x2 >= 5) {
			return 0;
		}
		if (paneG[qnode.x2 + 1][qnode.y2] == 0) {
			return 1;
		}
	}
	return 0;

}
int cangoB(myblock qnode) {
	if (0 <= qnode.x1 && qnode.x1 < 50) {
		if (0 <= qnode.x2 && qnode.x2 < 50) {
			if (qnode.y1 >= 5 || qnode.y2 >= 5) {
				return 0;
			}
			if (qnode.x1 == qnode.x2) {
				if (paneB[qnode.x2][qnode.y2+1] == 0) {
					return 1;
				}
			}
			if (paneB[qnode.x1][qnode.y1+1] == 0 && paneB[qnode.x2][qnode.y2+1] == 0) {
				return 1;
			}
		}
		else {
			if (qnode.y1 >= 5) {
				return 0;
			}
			if (paneB[qnode.x1][qnode.y1+1] == 0) {
				return 1;
			}
		}
	}
	else {
		if (qnode.y2 >= 5) {
			return 0;
		}
		if (paneB[qnode.x2][qnode.y2+1] == 0) {
			return 1;
		}
	}
	return 0;

}

void moveG() {
	queue<myblock> tmp;
	for (int i = 0; i < G_Block.size();) {
		tmp.push(G_Block.top());
		G_Block.pop();
	}

	int dirx = 1;
	int diry = 0;
	
	//꺼낸 노드의 움직임이 완료되면 넣는걸로.
	for(int i = 0 ; i < tmp.size() ;) {
		myblock qnode, qnode_before;
		qnode = tmp.front();
		qnode_before = qnode;
		tmp.pop();

		int success = 0;
		do {
			if (cangoG(qnode)) {
				success = 1;
				if (0 <= qnode.x1 && qnode.x1 < 50) {
					if (0 <= qnode.x2 && qnode.x2 < 50) {
						qnode.x1 += 1;
						qnode.x2 += 1;
					}
					else {
						qnode.x1 += 1;
					}
				}
				else {
					qnode.x2 += 1;
				}
			}
			else {
				success = 0;
			}
		} while (success == 1);
		if (0 <= qnode.x1 && qnode.x1 < 50) {
			if (0 <= qnode.x2 && qnode.x2 < 50) {
				paneG[qnode_before.x1][qnode_before.y1] = 0;
				paneG[qnode_before.x2][qnode_before.y2] = 0;
				paneG[qnode.x1][qnode.y1] = 1;
				paneG[qnode.x2][qnode.y2] = 1;
			}
			else {
				paneG[qnode_before.x1][qnode_before.y1] = 0;
				paneG[qnode.x1][qnode.y1] = 1;
			}
		}
		else {
			paneG[qnode_before.x2][qnode_before.y2] = 0;
			paneG[qnode.x2][qnode.y2] = 1;
		}
		G_Block.push(qnode);
	}
	showmeG();
	cout << endl;
	return;
}
void moveB() {
	queue<myblock> tmp;
	for (int i = 0; i < B_Block.size();) {
		tmp.push(B_Block.top());
		B_Block.pop();
	}

	int dirx = 0;
	int diry = 1;

	//꺼낸 노드의 움직임이 완료되면 넣는걸로.
	for (int i = 0; i < tmp.size();) {
		myblock qnode, qnode_before;
		qnode = tmp.front();
		qnode_before = qnode;
		tmp.pop();

		int success = 0;
		do {
			if (cangoB(qnode)) {
				success = 1;
				if (0 <= qnode.x1 && qnode.x1 < 50) {
					if (0 <= qnode.x2 && qnode.x2 < 50) {
						qnode.y1 += 1;
						qnode.y2 += 1;
					}
					else {
						qnode.y1 += 1;
					}
				}
				else {
					qnode.y2 += 1;
				}
			}
			else {
				success = 0;
			}
		} while (success == 1);
		if (0 <= qnode.x1 && qnode.x1 < 50) {
			if (0 <= qnode.x2 && qnode.x2 < 50) {
				paneB[qnode_before.x1][qnode_before.y1] = 0;
				paneB[qnode_before.x2][qnode_before.y2] = 0;
				paneB[qnode.x1][qnode.y1] = 1;
				paneB[qnode.x2][qnode.y2] = 1;
			}
			else {
				paneB[qnode_before.x1][qnode_before.y1] = 0;
				paneB[qnode.x1][qnode.y1] = 1;
			}
		}
		else {
			paneB[qnode_before.x2][qnode_before.y2] = 0;
			paneB[qnode.x2][qnode.y2] = 1;
		}
		B_Block.push(qnode);
	}
	showmeB();
	cout << endl;
	return;
}

int lineCheck_G() {
	queue<myblock> tmp;
	myblock qnode;
	int size = G_Block.size();
	for (int i = 0; i < G_Block.size();) {
		tmp.push(G_Block.top());
		G_Block.pop();
	}

	for (int i = 2; i <= 5; i++) {
		int flag = 1;
		for (int j = 0; j < 4; j++) {
			if (paneG[i][j] == 0) {
				flag = 0;
			}
		}
		if (flag == 1) {
			score++;
			for (int k = 0; k < size; k++) {
				qnode = tmp.front();
				tmp.pop();
				if (qnode.x1 == i) {
					if (qnode.x2 == i) {
						paneG[qnode.x2][qnode.y2] = 0;
						qnode.x2 = -100;
						qnode.y2 = 100;
						paneG[qnode.x1][qnode.y1] = 0;
						qnode.x1 = -100;
						qnode.y1 = 100;
					}
					else {
						paneG[qnode.x1][qnode.y1] = 0;
						qnode.x1 = -100;
						qnode.y1 = 100;
					}
				}
				else if (qnode.x2 == i) {
					paneG[qnode.x2][qnode.y2] = 0;
					qnode.x2 = -100;
					qnode.y2 = 100;
				}
				else {
					G_Block.push(qnode);
					continue;
				}
				if (qnode.x1 >= 0 || qnode.x2 >= 0) {
					G_Block.push(qnode);
				}
			}
			return 1;
		}
	}
	for (int k = 0; k < size; k++) {
		G_Block.push(tmp.front());
		tmp.pop();
	}
	return 0;
}
int brightCheck_G() {
	queue<myblock> tmp;
	myblock qnode;
	int size = G_Block.size();
	for (int i = 0; i < G_Block.size();) {
		tmp.push(G_Block.top());
		G_Block.pop();
	}
	int flag = 0;
	for (int i = 0; i < 4; i++) {
		if (paneG[0][i] == 1) {
			flag++;
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (paneG[1][i] == 1) {
			flag++;
			break;
		}
	}
	for (int i = 0; i < flag; i++) {
		for (int k = 0; k < size; k++) {
			qnode = tmp.front();
			tmp.pop();
			if (qnode.x1 == 5 - i) {
				if (qnode.x2 == 5 - i) {
					paneG[qnode.x2][qnode.y2] = 0;
					qnode.x2 = -100;
					qnode.y2 = 100;
					paneG[qnode.x1][qnode.y1] = 0;
					qnode.x1 = -100;
					qnode.y1 = 100;
				}
				else {
					paneG[qnode.x1][qnode.y1] = 0;
					qnode.x1 = -100;
					qnode.y1 = 100;
				}
			}
			else if (qnode.x2 == 5 - i) {
				paneG[qnode.x2][qnode.y2] = 0;
				qnode.x2 = -100;
				qnode.y2 = 100;
			}
			else {
				G_Block.push(qnode);
				continue;
			}
			if (qnode.x1 >= 0 || qnode.x2 >= 0) {
				G_Block.push(qnode);
			}
		}
		if (i != flag - 1) {
			for (int i = 0; i < G_Block.size();) {
				tmp.push(G_Block.top());
				G_Block.pop();
			}

			size = tmp.size();
		}
	}
	if (flag == 0) {
		for (int i = 0; i < tmp.size();) {
			G_Block.push(tmp.front());
			tmp.pop();
		}
	}
	return 0;
}

int lineCheck_B() {
	queue<myblock> tmp;
	myblock qnode;
	int size = B_Block.size();
	for (int i = 0; i < B_Block.size();) {
		tmp.push(B_Block.top());
		B_Block.pop();
	}

	for (int j = 2; j <= 5; j++) {
		int flag = 1;
		for (int i = 0; i < 4; i++) {
			if (paneB[i][j] == 0) {
				flag = 0;
			}
		}
		if (flag == 1) {
			score++;
			for (int k = 0; k < size; k++) {
				qnode = tmp.front();
				tmp.pop();
				if (qnode.y1 == j) {//해당하지 않는 원소는 그냥 바로 push
					if (qnode.y2 == j) {
						paneB[qnode.x2][qnode.y2] = 0;
						qnode.x2 = 100;
						qnode.y2 = -100;
						paneB[qnode.x1][qnode.y1] = 0;
						qnode.x1 = 100;
						qnode.y1 = -100;
					}
					else {
						paneB[qnode.x1][qnode.y1] = 0;
						qnode.x1 = 100;
						qnode.y1 = -100;
					}
				}
				else if (qnode.y2 == j) {
					paneB[qnode.x2][qnode.y2] = 0;
					qnode.x2 = 100;
					qnode.y2 = -100;
				}
				else {
					B_Block.push(qnode);
					continue;
				}
				
				if (qnode.y1 >= 0 || qnode.y2 >= 0) {
					B_Block.push(qnode);
				}
			}
			return 1;
		}
	}
	for (int k = 0; k < size; k++) {
		B_Block.push(tmp.front());
		tmp.pop();
	}
	return 0;
}
int brightCheck_B() {
	queue<myblock> tmp;
	myblock qnode;
	int size = B_Block.size();
	for (int i = 0; i < B_Block.size();) {
		tmp.push(B_Block.top());
		B_Block.pop();
	}
	int flag = 0;
	for (int i = 0; i < 4; i++) {
		if (paneB[i][0] == 1) {
			flag++;
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (paneB[i][1] == 1) {
			flag++;
			break;
		}
	}
	for (int i = 0; i < flag; i++) {
		for (int k = 0; k < size; k++) {
			qnode = tmp.front();
			tmp.pop();
			if (qnode.y1 == 5 - i) {
				if (qnode.y2 == 5 - i) {
					paneB[qnode.x2][qnode.y2] = 0;
					qnode.x2 = 100;
					qnode.y2 = -100;
					paneB[qnode.x1][qnode.y1] = 0;
					qnode.x1 = 100;
					qnode.y1 = -100;
				}
				else {
					paneB[qnode.x1][qnode.y1] = 0;
					qnode.x1 = 100;
					qnode.y1 = -100;
				}
			}
			else if (qnode.y2 == 5 - i) {
				paneB[qnode.x2][qnode.y2] = 0;
				qnode.x2 = 100;
				qnode.y2 = -100;
			}
			else {
				B_Block.push(qnode);
				continue;
			}
			if (qnode.y1 >= 0 || qnode.y2 >= 0) {
				B_Block.push(qnode);
			}
		}
		if (i != flag - 1) {
			for (int i = 0; i < B_Block.size();) {
				tmp.push(B_Block.top());
				B_Block.pop();
			}
			size = tmp.size();
		}
	}
	if (flag == 0) {
		for (int i = 0; i < tmp.size();) {
			B_Block.push(tmp.front());
				tmp.pop();
		}
	}
	return 0;
}

void play(int t, int x, int y) {
	
	myblock qnode;
	//get block G
	switch (t)
	{
	case 1:
		qnode.type = 1;
		qnode.x1 = 1;
		qnode.y1 = y;
		qnode.x2 = -100;
		qnode.y2 = 100;
		paneG[1][y] = 1;
		break;
	case 2:
		qnode.type = 2;
		qnode.x1 = 1;
		qnode.y1 = y;
		qnode.x2 = 1;
		qnode.y2 = y+1;
		paneG[1][y] = 1;
		paneG[1][y+1] = 1;
		break;
	case 3:
		qnode.type = 3;
		qnode.x1 = 0;
		qnode.y1 = y;
		qnode.x2 = 1;
		qnode.y2 = y;
		paneG[0][y] = 1;
		paneG[1][y] = 1;
		break;
	default:
		break;
	}
	G_Block.push(qnode);
	cout << endl;
	//get block B
	switch (t)
	{
	case 1:
		qnode.type = 1;
		qnode.x1 = x;
		qnode.y1 = 1;
		qnode.x2 = 100;
		qnode.y2 = -100;
		paneB[x][1] = 1;
		break;
	case 2:
		qnode.type = 2;
		qnode.x1 = x;
		qnode.y1 = 0;
		qnode.x2 = x;
		qnode.y2 = 1;
		paneB[x][0] = 1;
		paneB[x][1] = 1;
		break;
	case 3:
		qnode.type = 3;
		qnode.x1 = x;
		qnode.y1 = 1;
		qnode.x2 = x + 1;
		qnode.y2 = 1;
		paneB[x][1] = 1;
		paneB[x+1][1] = 1;
		break;
		
	default:
		break;
	}
	B_Block.push(qnode);
	showmeG();
	cout << endl;
	showmeB();
	cout << endl;
	
	moveG();
	while (lineCheck_G()>0) {
		moveG();
	}
	brightCheck_G();
	moveG();

	moveB();
	while (lineCheck_B()>0) {
		moveB();
	}
	brightCheck_B();
	moveB();
	
}
void read() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> t >> x >> y;
		play(t, x, y);
		cout << endl;
		idx++;
	}

}
int main()
{
	freopen("input.txt", "r", stdin);
	read();
	int remain = 0;
	for (int i = 2; i <= 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (paneG[i][j] == 1) {
				remain++;
			}
			if (paneB[j][i] == 1) {
				remain++;
			}
		}
	}
	cout << score << endl << remain;
	return 0;
}
