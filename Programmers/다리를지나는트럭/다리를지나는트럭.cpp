#include <string>
#include <iostream>
#include <queue>
#include <vector>

//큐를 이용해야한다. 트럭이 도로위에 오르고 내리는 과정은 자료구조상
//큐와 유사하다. 큐를 사용해야겠다는 자연스러운 사고과정이 필요함.

using namespace std;

queue< pair<int, int> > myque;
int B, W, time_s;

void load_truck(vector<int>& truck_weights) {
	if (truck_weights.size() == 0) return;
	vector<int>::iterator itr;
	itr = truck_weights.begin();
	if (W >= *itr) {//트럭을 싣을수 있는 경우
		W -= *itr;
		myque.push(make_pair(*itr, time_s)); //이 두줄이 바뀌면 안된다!
		truck_weights.erase(itr);
	}
}
void unload_truck() {//트럭이 내려야하는 경우
	if (myque.empty())  return;

	if (myque.front().second + B <= time_s) {
		W += myque.front().first;
		myque.pop();
	}
}

int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 0;
	B = bridge_length;
	W = weight;
	time_s = 0;
	while (1) {
		time_s++;
		unload_truck();
		load_truck(truck_weights);
		if (myque.empty()) {
			break;
		}
	}
	return time_s;
}