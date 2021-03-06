#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int arr[101];
//no viable overloaded operator[] vector 오류는 a, b의 자료형이 잘못된 것
int giveMax(vector<int>::iterator a, vector<int>::iterator b, vector<int> priorities) {
	int max = -1;
	for (; a != b; a++) {
		if (max < priorities[*a]) {
			max = priorities[*a];
		}
	}
	return max;
}


int solution(vector<int> priorities, int location) {
	int answer;
	int N = priorities.size();
	vector<int> idx(N);
	for (int i = 0; i < N; i++) {
		idx[i] = i;
	}
	int print_idx = 1;
	while (arr[location] == 0) {
		int max_num = *max_element(idx.begin(), idx.end());
		if (priorities[idx[0]] >= max_num) {
			arr[idx[0]] = print_idx++;
			idx.erase(idx.begin());
		}
		else {
			idx.push_back(idx[0]);
			idx.erase(idx.begin());
		}
	}
	return arr[location];
}