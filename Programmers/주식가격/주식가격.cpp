#include <string>
#include <stack>
#include <vector>
/*
시간 복잡도 : O(N);
원래는 하나의 원소에 대해 어느 지점까지 감소하지 않는지 탐색하는 방식으로
O(N^2)의 방법을 차용하려 했으나,
스택과 큐를 이용한 문제(힌트)라는 점에서,  자료구조를 이용하면 Linear하게 구성할 수 있다는 점을 깨닳음.
또한, 굳이 스택에 pair를 이용할 필요가 없으며, 인덱스만 저장하면 값은 알 수 있다는 점을 이용해
스택 자료구조를 pair가 아닌 다른 값으로 변경할 수 있다.
*/
using namespace std;

vector<int> solution(vector<int> prices) {
	vector<int> answer;//vector<int> answer(size_t size);
	stack<pair<int, int> > mystack;
	int N = prices.size();
	answer.resize(N);
	mystack.push(make_pair(prices[0], 0));

	for (int i = 1; i < N; i++) {
		if (mystack.top().first <= prices[i]) {
			mystack.push(make_pair(prices[i], i));
			continue;
		}

		else {
			do {
				pair<int, int> top = mystack.top();
				mystack.pop();
				answer[top.second] = i - top.second;
				if (mystack.empty()) {
					break;
				}
			} while (mystack.top().first > prices[i]);
			mystack.push(make_pair(prices[i], i));
			continue;
		}
	}
	while (!mystack.empty()) {
		pair<int, int> top = mystack.top();
		mystack.pop();
		answer[top.second] = N - top.second - 1;
	}
	return answer;
}