#define _CRT_NO_SECURE_WARNINGS_
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>

int N;
char name[110];
using namespace std;

struct cmp {
	bool operator()(string a, string b) { //True이면 b가 우선순위가 높다
		return a < b; // > : 오름차순   < : 내림차순
	}
};


//map의 선언
map<string, int> map_sample1;
map<string, int, cmp> map_sample2;
void map_test() {

}

priority_queue<string, vector<string>, cmp> pq;


int main()
{
	return 0;
}
