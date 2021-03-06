#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

//20.12.29

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";
	map<string, int> comp_map;
	vector<string>::iterator itr = completion.begin();
	for (; itr != completion.end(); itr++) {
		if (comp_map.count(*itr) == 0) {
			comp_map.insert(make_pair(*itr, 1));
		}
		else {
			comp_map.find(*itr)->second++;
		}
	}

	for (itr = participant.begin(); itr != participant.end(); itr++) {
		if (comp_map.find(*itr) != comp_map.end()) {
			map<string, int>::iterator tmp = comp_map.find(*itr);//이거 중요 .find의 반환형은 iterator로 지정해야한다.
			tmp->second--;
			if (tmp->second == 0) {
				comp_map.erase(tmp);
			}
		}
		else {
			answer += *itr;
			break;
		}
	}

	return answer;
}

int main()
{
    std::cout << "Hello World!\n"; 
}
