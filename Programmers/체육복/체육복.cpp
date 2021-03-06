#include <string>
#include <vector>
//21_01_06
//그리디에 대해 처음부터 공부하고 다시 돌아와 문제를 보니 답이 보였다.
//다이나믹과 그리디의 차이점, 그리고 그리디를 이용한 여러 알고리즘에 대해 다시 공부해보았다.
//공부한 알고리즘을 복습하자
using namespace std;
int stud[31];
int solution(int n, vector<int> lost, vector<int> reserve) {
	int n_lost = lost.size();
	int n_resv = reserve.size();
	for (int i = 0; i < n_lost; i++) {
		stud[lost[i]] -= 1;
	}
	for (int i = 0; i < n_resv; i++) {
		stud[reserve[i]] += 1;
	}
	//stud 에서 값이 1 이상인 경우에만 빌려줄 수 있다. 제한사항 5번 소거
	//만약 양 옆에 잃어버린 학생이 있다면, 앞선 번호의 학생에게 먼저 준다.
	//뒷번호의 학생에게 빌려주는 경우는 최적 선택이 아니다. 뒤에 누군가가 있다면 빌려줄 수 있기 때문.
	for (int i = 1; i <= n; i++) {
		if (stud[i] == 1) {
			if (stud[i - 1] == -1) {
				stud[i - 1] += 1;
				stud[i] -= 1;
			}
			else if (stud[i + 1] == -1) {
				stud[i + 1] += 1;
				stud[i] -= 1;
			}
		}
	}

	int answer = 0;
	for (int i = 1; i <= n; i++) {
		if (stud[i] >= 0) {
			answer++;
		}
	}
	return answer;
}