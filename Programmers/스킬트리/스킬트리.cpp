#include <string>
#include <iostream>
#include <vector>

using namespace std;

int mysolution(string skill, vector<string> skill_trees) {
	int answer = 0;
	int N = skill_trees.size();
	for (int i = 0; i < N; i++) {
		int skill_tree = skill_trees[i].size();
		int skill_idx = 0;
		int pos = 1;
		for (int j = 0; j < skill_tree; j++) {
			int tmp = skill.find(skill_trees[i][j]);
			if (tmp == string::npos) {
				continue;
			}
			else if (tmp == skill_idx) {
				skill_idx++;
			}
			else {
				pos = 0;
				break;
			}
		}
		if (pos == 1) {
			answer++;
		}
	}
	return answer;
}