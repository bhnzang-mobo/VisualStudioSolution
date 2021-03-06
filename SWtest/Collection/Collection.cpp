#pragma warning(disable:4996)
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
map<string, int> map_sample1;//char*를 KEY로 쓰면 안된다.
map<string, int, cmp> map_sample2;
void map_test() {
	//원소 삽입 1
	//map. insert, erase;
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
	//Priority Queue push, pop

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
	//vector는 함수의 전달인자로 사용될 경우, call by reference 는 void function(vector<template> & vec)이라고 씀
	//Vector push_back, erase;
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

	//Copy를 이용한 복사.
	//copy(vector_sample1.begin(), vector_sample1.end(), destVect.begin());

	//입출력 가능가능!
	char  test1[10];
	string test2;

	scanf("%s", test1);
	cout << test1 << endl;
	cin >> test1;
	printf("%s", test1);
}
//set의 선언
set<int> set_sample1;

void set_test() {
	//insert, erase
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



//string 의 활용
void string_test() {
	cout << endl << endl << "문자열 활용 방법"<<endl;
	//strtok 메소드
	char mystring[] = "Hello World! This is MOBO!";
	string mystring2 = "0123456789";
	char* token = strtok(mystring, " ");
	cout << "strtok 사용 예시 입니다." << endl;
	while (token!=NULL) {
		cout << token << " ";
		token = strtok(NULL, " ");
	}
	//substr(int idx, int count) idx에서 count개 만큼 자르기. 리턴은 string [연습문제 : 가운데글자가져오기]
	cout << endl << "substr 메소드 테스트" << endl;
	cout << mystring2.substr(0, 3);
	cout << endl << endl;

	//string == 연산 -> != 연산도 가능하다. > < 는 사전상 우선순위를 나타낸다.
	string a = "MOBO";
	string b = "MOBO";
	if (a == b) {
		cout << "두 문자열은 같습니다!!" <<endl;
	}
	//str.find : 문자열 찾기
	printf("4는 문자열에 %d번째 입니다.\n\n", mystring2.find('4') + 1);

	printf("7는 문자열에 %d번째 입니다.\n\n", mystring2.find("7") + 1);

	//string 을 매개변수로 쓰고싶다면, 선언 : void fun(string & s); 호출 : fun(s); 하면 된다.

}

typedef struct mytype {
	int a;
	int b;
}mytype;


bool compare(mytype a, mytype b) {
	if (a.a == b.a) {
		return a.b < b.b;
	}
	else {
		return a.a < b.a;
	}
}


void sort_test() {
	cout << endl << "Sort 테스트" << endl;
	vector<int> myvector = { 0,1,2,3,4,5,6,7,8,9 };
	sort(myvector.begin(), myvector.end(), greater<int>());

	cout << "vector<int> 의 정렬입니다." << endl;
	vector<int>::iterator itr;
	itr = myvector.begin();
	while (itr != myvector.end()) {
		cout << *itr << " ";
		itr++;
	}

	cout << endl << "vector<string>의 정렬입니다." << endl;
	vector<string> strarr = { "MOBO","MAPLE","Story","Pain" };
	vector<string>::iterator itr2;
	itr2 = strarr.begin();
	cout << "정렬 전...." << endl;
	while (itr2 != strarr.end()) {
		cout << *itr2 << " ";
		itr2++;
	}
	sort(strarr.begin(), strarr.end());
	itr2 = strarr.begin();
	cout << endl << "정렬 후...." << endl;
	while (itr2 != strarr.end()) {
		cout << *itr2 << " ";
		itr2++;
	}
	//정렬함수를 만들어서 사용한 방법 compare함수는 global하게 정의됨.
	cout << endl << "vector<mytype>의 정렬입니다." << endl;
	
	vector<mytype> mtvec = { {1,2},{3,4},{-1,3},{4,2},{4,5},{-7,10} };
	
	
	sort(mtvec.begin(), mtvec.end(), compare);
	vector<mytype>::iterator itr3;
	itr3 = mtvec.begin();
	cout << endl << "정렬 후..." << endl;
	while (itr3 != mtvec.end()) {
		cout << itr3->a << ", " << itr3->b <<"||";
		itr3++;
	}
}
int main()
{
	map_test();
	pq_test();
	set_test();
	vector_test();
	string_test();
	sort_test();
	return 0;
}
