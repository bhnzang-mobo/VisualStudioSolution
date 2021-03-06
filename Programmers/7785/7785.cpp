#pragma warning(disable : 4996)
#include <list>
#include <string>
#include <iostream>
using namespace std;
int N;

typedef struct __HASH_TABLE {
	list<string> arr[300];
	int(*giveHash)(string);
}__HASH_TABLE;

int __giveHash(string name) {
	int ans = 0;
	int prime[3] = { 2,3,5 };
	for (int i = 0; i < 3; i++) {
		if (65 <= name[i] <= 90) {
			ans += (name[i] - 17) * prime[i];
		}
		else {
			ans += (name[i] - 41) * prime[i];
		}
	}
	return ans%300;
}

void __HASH_INIT(__HASH_TABLE* ht,int(*func)(string)) {
	ht->giveHash = func;
}

bool __HASH_isIN(__HASH_TABLE* ht, string name) {
	list<string>::iterator itr = ht->arr[__giveHash(name)].begin();
	for (; itr != ht->arr[__giveHash(name)].end(); itr++) {
		if (*itr == name) {
			return true;
		}
	}
	return false;
}
void __HASH_DELETE(__HASH_TABLE* ht, string name) {
	list<string>::iterator itr = ht->arr[__giveHash(name)].begin();
	for (; itr != ht->arr[__giveHash(name)].end(); itr++) {
		if (*itr == name) {
			ht->arr[__giveHash(name)].erase(itr);
			return;
		}
	}
}

void __HASH_INSERT(__HASH_TABLE* ht, string name) {
		ht->arr[__giveHash(name)].push_back(name);
}

int main()
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	__HASH_TABLE ht;
	__HASH_INIT(&ht, __giveHash);
	cin >> N;
	string name;
	string status;
	for (int i = 0; i < N; i++) {
		cin >> name;
		cin >> status;
		if (status == "enter") {
			__HASH_INSERT(&ht, name);
		}
		else {
			__HASH_DELETE(&ht, name);
		}
	}
	list<string> cont;

	for (int i = 0; i < 300; i++) {
		list<string>::iterator itr = ht.arr[i].begin();
		for (; itr != ht.arr[i].end(); itr++) {
			cont.push_back(*itr);
		}
	}
	cont.sort(greater<string>());
	list<string>::iterator itr = cont.begin();
	for (; itr != cont.end(); itr++) {
		cout << *itr;
		printf("\n");//endl을 \n로만 바꿔줘도 시간이 줄어듬;;;;;;;;;;;;
	}
}