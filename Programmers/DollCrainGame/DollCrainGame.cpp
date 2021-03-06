#include <string>
#include <vector>
#include <stack>
int N;

using namespace std;
stack<int> my_board[31];
stack<int> basket;

int solution(vector<vector<int>> board, vector<int> moves) {
	int answer = 0;
	N = board.size();
	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] > 0) {//input이 내가 생각한거랑 전혀 달랐음. input만 재조정 후 만점.
				my_board[j + 1].push(board[i][j]);
			}
		}
	}
	vector<int>::iterator iter;
	for (iter = moves.begin(); iter != moves.end(); iter++) {//Basket이 비어있을 수도 있다! Basket도 stack, empty라는 속성을 가질 수 있다.
		if (my_board[*iter].empty()) continue;
		if (basket.empty()) {
			basket.push(my_board[*iter].top());//인형을 뽑아낸다는 생각에 인형을 stack으로 옮겼음. 배열을 이용해 0이아닌 값(인형)이 올때까지
			my_board[*iter].pop();  // 다음을 찾는 방법도 있음
		}
		else {
			if (basket.top() == my_board[*iter].top()) {
				answer += 2;
				basket.pop();
				my_board[*iter].pop();
			}
			else {
				basket.push(my_board[*iter].top());
				my_board[*iter].pop();
			}
		}
	}
	return answer;
}