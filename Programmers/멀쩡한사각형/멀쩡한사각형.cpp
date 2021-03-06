#include <iostream>
#include <cmath>
using namespace std;
/*
  처음부터 최대공약수 만큼 패턴이 존재한다는 것을 발견하고 최대공약수를 이용해 문제를 풀어내려 한점 (Good)
  놓친점은, 그렇게 만들어진 서로소의 높이와 너비를 가진 단위 직사각형 안에서 대각선이 지나가는 정사각형의 갯수가
  너비+높이-1 이라는 점을 알아내지 못했다

  너비+높이-1 이라는 점은 문제를 많이 푼 사람들 사이에서 널리 알려진 상식인 것 같은데
  처음 문제를 푸는 내 입장에서는 '이게 왜 너비+높이-1이지? 그저 우연이 아닌가?'하는 생각에 쉽게 확신을 하지 못했다.
  규칙을 발견하면 끝까지 규칙을 활용해보자. 브루트포스 방식으로 계산하는 방식은 아닌 듯한 문제다.
*/

long long gcd(int a, int b) {
	int c;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}


long long solution(int w, int h) {
	long long answer = (long long)w*h;
	int wh_gcd = gcd(w, h);
	answer -= ((long long)w + h) - wh_gcd;
	return answer;
}