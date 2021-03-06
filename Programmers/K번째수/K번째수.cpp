#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> Best_solution(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer;
	vector<int> temp;

	for (int i = 0; i < commands.size(); i++) {
		temp = array;//??대박이네
		sort(temp.begin() + commands[i][0] - 1, temp.begin() + commands[i][1]); // 주어진 구간을 바로 정렬
		answer.push_back(temp[commands[i][0] + commands[i][2] - 2]);//원하는 인덱스 추출
	}

	return answer;
}


vector<int> My_solution(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer;
	int N = commands.size();
	for (int i = 0; i < N; i++) {
		vector<int> tmp;
		int M = commands[i][1] - commands[i][0];
		vector<int>::iterator itr;
		itr = array.begin() + commands[i][0] - 1;
		for (int j = 0; j <= M; j++) {
			tmp.push_back(*itr);//굳이 이렇게 하나씩 push_back한 원소를 정렬할 필요가 없다.
			itr++;
		}
		sort(tmp.begin(), tmp.end());
		answer.push_back(tmp[commands[i][2] - 1]);
	}
	return answer;
}