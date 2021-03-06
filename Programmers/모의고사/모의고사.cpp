#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//20.12.29

using namespace std;
/* 다른 사람의 솔루션.

vector<int> one = { 1,2,3,4,5 };
vector<int> two = { 2,1,2,3,2,4,2,5 };
vector<int> thr = { 3,3,1,1,2,2,4,4,5,5 }; 미리 패턴을 배열로 정해두고

vector<int> solution(vector<int> answers) {
	vector<int> answer;
	vector<int> they(3);
	for (int i = 0; i < answers.size(); i++) {
		if (answers[i] == one[i%one.size()]) they[0]++; 이런식으로 순환 반복을 지정해둠.
		if (answers[i] == two[i%two.size()]) they[1]++;
		if (answers[i] == thr[i%thr.size()]) they[2]++;
	}
	int they_max = *max_element(they.begin(), they.end()); // 이 방식의 maxelement를 사용할 수 있음
	for (int i = 0; i < 3; i++) {
		if (they[i] == they_max) answer.push_back(i + 1);
	}
	return answer;
}
*/
//나의 솔루션

int isCorrect1(int ans, int idx) {
	if (idx % 5 == ans - 1) {
		return 1;
	}
	return 0;
}
int isCorrect2(int ans, int idx) {
	if (idx % 2 == 0) {
		if (ans == 2) {
			return 1;
		}
		return 0;
	}
	else {
		if (idx % 8 == 1 && ans == 1) {
			return 1;
		}
		else if (idx % 8 == 3 && ans == 3) {
			return 1;
		}
		else if (idx % 8 == 5 && ans == 4) {
			return 1;
		}
		else if (idx % 8 == 7 && ans == 5) {
			return 1;
		}
		return 0;
	}
}
int isCorrect3(int ans, int idx) {
	if ((idx % 10) / 2 == 0 && ans == 3) {
		return 1;
	}
	else if ((idx % 10) / 2 == 1 && ans == 1) {
		return 1;
	}
	else if ((idx % 10) / 2 == 2 && ans == 2) {
		return 1;
	}
	else if ((idx % 10) / 2 == 3 && ans == 4) {
		return 1;
	}
	else if ((idx % 10) / 2 == 4 && ans == 5) {
		return 1;
	}
	return 0;
}

vector<int> solution(vector<int> answers) {
	vector<int> answer;
	int N = answers.size();
	int score[3] = { 0, };

	for (int i = 0; i < N; i++) {
		score[0] += isCorrect1(answers[i], i);
		score[1] += isCorrect2(answers[i], i);
		score[2] += isCorrect3(answers[i], i);
	}
	int total = max(score[0], score[1]);
	total = max(total, score[2]);

	for (int i = 0; i < 3; i++) {
		if (score[i] == total) {
			answer.push_back(i + 1);
		}
	}
	return answer;
}

int main()
{
    std::cout << "Hello World!\n"; 
}
