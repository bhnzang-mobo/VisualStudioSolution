#include <iostream>
#include <vector>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

int main()
{
	//string 가지고 놀기
	string s = "qwer";
	string s2 = "Hi";
	//string은 서로 더할 수 있다. s+s2 가능!

	//string의 push_back, pop_back 기능!
	s.push_back('L');

	//s.substr(size_t index, size_t len) : index부터 증가하면서 len개 반환    string answer = s[1] + s[2]; 이렇게 하면 안됨
	cout << s.substr(s.length()/2 -1,2) <<endl;

	//s.compare(const string& str) 단순 비교 s가 사전순 앞서면 -1 str가 사전순 앞서면 1
	//s.compare(size_t index, size_t len, const string& str) s의 index 부터 길이 len 가 비교대상. 이하 똑같음
	//s.compare(size_t index, size_t len, const string& str,size_t index2, size_t len2) 두 문자열의 부분 부분을 비교하는 것. index2 와 len2는 str에 대한 변수.



	//s.replace(size_t index, size_t len, const string& str) : index 부터 len개의 문자열을 str로 변경
	cout << s.replace(s.length() / 2 - 1, 2, s2)<<endl;

	//string 타입 vector
	vector<string> my;
	my.push_back("Hello");
	my.push_back("World!");
	vector<string>::iterator itr;
	for (itr = my.begin(); itr != my.end(); itr++) {
		cout << *itr <<" ";
	}
	cout << endl;
	int A = 1000;
	if (A & 1) {
		cout << "Hi" << endl;
	}
	return 0;
}
