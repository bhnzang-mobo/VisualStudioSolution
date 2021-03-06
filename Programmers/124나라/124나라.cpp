#include <string>
#include <vector>
#include <stack>
using namespace std;
/*
	3진법을 활용한 문제.
	3진법은 3진법인데 1, 2, 4를 활용하고 시작이 0 이 아니라 1인점, 0 이 없고 4가 나타난 점.
	즉 1, 2, 4(4인척 하는 3)을 사용하는 3진법을 만들면 된다.
	즉 3이 되면 올림을 하지말고 그대로 3을 쓰고, 3을 넘으면 그때 올림하는 방식.
	1->2->3->11->12->13->21->22->23->31->32->33->111...
	
	평범한 진법 변환 알고리즘을 활용한다 -> @@새로운 방식이 아닌 기존에 사용된 알고리즘을 활용

	3으로 나눈 나머지라는것은 3^0 항을 가져오는 것. 그것이 0인 경우, 즉 3으로 나누어 떨어지는 경우
	0으로 기입하는 것이 아닌 3을 기입하며, 올림을 하지 않으므로 몫에서 1을 빼는 원리.
	
	3^0 * 1 = 1
	3^0 * 2 = 2;
	3^0 * 3 -> 3^1 * 1 + 3^0 * 0 = 3
	여기서 역순으로 3^1*1 을 3^0 * 3 으로 바꾸기 위해 %3값이 0인 경우 나머지를 3으로 표기하고
	몫을 1 빼주는 이유가 저 과정을 되돌리는 과정이다.
	*/
string solution(int n) {
	string answer = "";
	stack<char> mystack;
	int Q = n;
	while (Q != 0) {
		int rem = Q % 3;
		if (rem == 0) {
			mystack.push('4');

			Q -= 1;
		}
		else {
			mystack.push('0' + rem);
		}
		Q /= 3;
	}
	while (!mystack.empty()) {
		answer.push_back(mystack.top());
		mystack.pop();
	}
	return answer;
}