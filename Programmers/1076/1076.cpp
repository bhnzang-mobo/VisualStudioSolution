#pragma warning(disable:4996)
#include <iostream>
#include <map>
#include <math.h>
#include <string>

using namespace std;
int main()
{
	map<string, int> resis;
	resis.insert(make_pair("black", 0));
	resis.insert(make_pair("brown", 1));
	resis.insert(make_pair("red", 2));
	resis.insert(make_pair("orange", 3));
	resis.insert(make_pair("yellow", 4));
	resis.insert(make_pair("green", 5));
	resis.insert(make_pair("blue", 6));
	resis.insert(make_pair("violet", 7));
	resis.insert(make_pair("grey", 8));
	resis.insert(make_pair("white", 9));

	freopen("input.txt", "r", stdin);
	string inp1, inp2, inp3;
	cin >> inp1;
	cin >> inp2;
	cin >> inp3;
	long long ans = (10*resis.find(inp1)->second + resis.find(inp2)->second)*(long long)pow(10,resis.find(inp3)->second);
	cout << ans;
}
