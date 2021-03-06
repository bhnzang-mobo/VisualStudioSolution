#include <string>
#include <vector>
#include <stack>
using namespace std;

//21_01_08
//자료구조를 잘 활용
int solution(int n) {
	int Q = n;
	int R = 0;
	int answer = 0;
	stack<int> comp3;
	while (Q != 0) {
		comp3.push(Q % 3);
		Q /= 3;
	}
	Q = 1;
	while (!comp3.empty()) {
		answer += Q * comp3.top();
		comp3.pop();
		Q *= 3;
	}
	return answer;
}