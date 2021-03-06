#define _CRT_SECURE_NO_WARNINGS    // strcpy 보안 경고로 인한 컴파일 에러 방지
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <string>    
#include <string.h>
#include <map>


int N;
char name[110];
using namespace std;
struct cmp {
	bool operator()(string a, string b) {
		return a < b;  // > : 오름차순   < : 내림차순
	}
};
struct cmp2 {
	bool operator()(int a, int b) {  //True(1) 이면 b가 False(0) 이면 a가 우선순위가 높다.
		return a > b;  // > : 오름차순   < : 내림차순
	}
};

priority_queue<string,vector<string>,cmp> pq;

priority_queue<int, vector<int>, cmp2> pq2;

map<string, int, greater<string>> mymap; //내림차순 정리

int main()
{
	freopen("input.txt", "r", stdin);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> name;
		fflush(stdin);
		strtok(name, ".");
		char * extend = strtok(NULL, ".");
		if (mymap.find(extend) == mymap.end()) {//엥 이게되네?
			mymap.insert(make_pair(extend, 1));
		}
		else {
			mymap[extend]++;
		}
	}
	map<string, int>::iterator itr;
	for (itr = mymap.begin(); itr != mymap.end(); itr++) {
		cout << itr->first << " " << itr->second << endl;
	}
	
	return 0;
}