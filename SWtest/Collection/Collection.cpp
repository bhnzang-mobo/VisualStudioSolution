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
	bool operator()(string a, string b) { //a,b가 원래 순서. True이면 b,a가 된다. b가 우선순위를 가지는 경우는 True이다.
		return a > b; // > : 내림차순   < : 오름차순 . 문자열의 경우 순서가 다름
	}
};


//map의 선언
map<string, int> map_sample1;
map<string, int, cmp> map_sample2;
void map_test() {
	//원소 삽입 1
	for (int i = 1; i <= 10; i++) {
		string key = "MOBO";
		key.push_back(' ');
		key.push_back('0'-1+i);
		map_sample1.insert(make_pair(key, i));
	}

	cout << "Iterator를 사용한 map 순회" << endl;
	cout << "map_sample 1" << endl;
	map<string, int>::iterator iter; // iterator 사용
	for (iter = map_sample1.begin(); iter != map_sample1.end(); iter++) {
		cout << iter->second << "번째 원소는 " << iter->first << "입니다" << endl;
	}

	//원소 삽입 2
	for (int i = 1; i <= 10; i++) {
		string key = "MOBO";
		key.push_back(' ');
		key.push_back('0' - 1 + i);
		map_sample2.insert(make_pair(key, i));
	}


	cout << endl;
	cout << "map_sample 2(정렬)" << endl;
	map<string, int>::iterator iter2; // iterator 사용
	for (iter2 = map_sample2.begin(); iter2 != map_sample2.end(); iter2++) {
		cout << iter2->second << "번째 원소는 " << iter2->first << "입니다" << endl;
	}

	//원소 삭제
	iter = map_sample1.begin();
	for (; iter != map_sample1.end();) { 
		map_sample1.erase(iter++);//.erase(iter) 는 안됨. iter에 해당하는 원소를 삭제하므로 훗날 for문에서 iter++이 안먹힘.
	}
}

//pqueue의 선언
struct cmp_int {
	bool operator()(int a, int b) {
		return a > b; // > 오름차순, < 내림차순
	}
};
priority_queue<int, vector<int>, cmp_int> pq_sample1;

void pq_test() {
	cout << endl << "우선순위 큐" << endl;
	for (int i = 0; i < 10; i++) {
		pq_sample1.push(i);
	}
	while (!pq_sample1.empty()){
		cout <<"현재 TOP은 " << pq_sample1.top()<<"입니다." << endl;
		pq_sample1.pop();
	}
}

//vecotr의 선언
vector<string> vector_sample1;
void vector_test() {
	//Vector 삽입
	vector_sample1.push_back("Hi");
	vector_sample1.push_back("My");
	vector_sample1.push_back("Name");
	vector_sample1.push_back("Is");
	vector_sample1.push_back("Mobo");
	//Vector 일부 원소 삭제
	vector<string> ::iterator erase_itr;
	erase_itr = vector_sample1.begin();

	vector_sample1.erase(erase_itr, erase_itr+1); //.erase(A,B) 반복자 A이상 반복자 B미만의 원소를 삭제함. 하나만 두면 그 반복자에 해당하는 원소 삭제
	cout << endl << endl;
	cout << "Vector 예시" << endl;
	vector<string>::iterator itr;
	for (itr = vector_sample1.begin(); itr != vector_sample1.end(); itr++) {
		cout <<" "<<*itr;
	}
}
//set의 선언
set<int> set_sample1;

void set_test() {
	cout << "set의 예제" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = i ; j < 10; j++) {
			set_sample1.insert(i + j);
		}
	}
	cout << "set의 원소는..." << endl;
	set<int>::iterator itr = set_sample1.begin();
	while (itr!=set_sample1.end()) {
		cout << *itr << ", ";
		itr++;
	}
}

int main()
{
	map_test();
	pq_test();
	set_test();
	vector_test();
	return 0;
}
