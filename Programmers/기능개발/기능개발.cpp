#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;
	int N = progresses.size();
	vector<int> days(N + 1);
	days[0] = 0;
	for (int i = 0; i < N; i++) {
		int Q = 0;
		if ((100 - progresses[i]) % speeds[i] != 0) {
			Q = 1;
		}
		days[i + 1] = (100 - progresses[i]) / speeds[i] + Q;
		if (days[i] > days[i + 1]) {
			days[i + 1] = days[i];//앞에있는 기능의 배포를 기다립니다.
		}
	}
	int itr = 1;
	while (itr != N + 1) {
		if (days[itr - 1] != days[itr]) {
			answer.push_back(1);
		}
		else {
			answer[answer.size() - 1]++;//마지막 원소의 1 덧셈. ++answer.back(); 로도 가능하다.
		}
		itr++;
	}
	return answer;
}