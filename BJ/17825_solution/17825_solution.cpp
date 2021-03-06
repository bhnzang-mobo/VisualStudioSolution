#include "pch.h"
#pragma warning(disable : 4996)
#include <iostream>

using namespace std;

int pos[4] = { 0, };// 현재 말들의 위치
int blue[4] = { 0, };//blue 영역에 들어갔는지 체크
int map[41] = { 0, };

int mv[10];
int MAX = 0;


bool move(int len, int idx)
{	//눈의 이동 정의를 이렇게 간단하게 할 수 있던가.,
	//len은 이동 길이.
	//idx는 말의 번호

	int start = pos[idx];
	int next = start;//말의 현재 위치 입니다.

	if (start == 10 || start == 20 || start == 30 || blue[idx]) { //현재 위치가 파란점이 있는 경우

		if (start == 30 && blue[idx] == 0) {//현재 말의 위치가 파란점을 밟은 적없는 데, 30인경우엔 맨 왼쪽 코너 30이다
			next = 28;//코너 30인 경우,  28로 옮기고 눈수를 1칸 줄인다.
			len--;
		}
		//이다음부터는 모두 동일한 원리를 적용한다.
		blue[idx] = 1; //파란색을 밟았음
		for (int i = 0; i < len; i++) {
			if (next > 40)  break;
			next = map[next];//맵에 저장한 다음 노드를 반환하는 map을 이용해 다음 노드 번호를 찾는다.
		}
	}
	else    next = start + 2 * len; // 명령의 두배만큼을 진행? 아! 코너를 진행하지 않은경우엔 주사위눈의 두배를 더하면 그게 눈이된다.


	for (int i = 0; i < 4; i++) {
		if (pos[i] == next && next <= 40) {//도착지점이 아닌 데서 두 숫자가 같으면?
			if (idx == i)  continue;//알고보니 나 자산이랑 비교했네 ㅋ ㅈㅅ
			if (blue[idx] == blue[i] || next == 40) return false;//코너를 돌아서 온곳이야 ㅜㅜ 40은 코너를 안돌아도 돌아서 올수 있어서 40은 무조건 충돌이다.
		}
	}

	pos[idx] = next;
	return true;
}
int dp[10];
void DFS(int cnt, int sum)
{ //depth가 10일때
	if (cnt == 10) {
		if (sum > MAX) {
			MAX = sum;
			for (int i = 0; i < 10; i++) {
				printf("%d ", dp[i]);
			}
			cout <<endl <<"total : "<< sum << endl;
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		//i는 주사위 번호
		//주사위가 현재 40이상 (도착지점)일경우
		if (pos[i] > 40) { 
			dp[cnt] = sum;
			DFS(cnt + 1, sum); 
		}
		//도착지점이 아니네?
		else {
			//현재 위치, 파란색을 거친경우
			int idx = pos[i];
			int tmp = blue[i];

			bool res = move(mv[cnt], i);

			// 이미 해당 칸에 다른 말이 존재하는 경우 , 해당 조합은 무효화, 움직이지 않음
			if (res == 0) {
				pos[i] = idx;
				blue[i] = tmp;
				continue;
			}
			//이동한 칸이 도착지점 인경우
			if (res && pos[i] > 40) {
				dp[cnt] = sum;
				DFS(cnt + 1, sum);
			}
			//이동한 칸이 도착지점이 아닌 경우
			else if (res && pos[i] <= 40) {
				dp[cnt] = sum + pos[i];
				DFS(cnt + 1, sum + pos[i]);
			}

			pos[i] = idx;
			blue[i] = tmp;

		}
	}
}

int main(void)
{

	for (int i = 0; i < 10; i++)   cin >> mv[i];
	//맵 하나에 윷놀이 길을 표현하는게 중요. 인덱스가 다르면 무조건 위치가 다름을 알 수 있음
	for (int i = 0; i < 3; i++)    map[10 + 3 * i] = 10 + 3 * (i + 1);
	for (int i = 0; i < 2; i++)    map[20 + 2 * i] = 20 + 2 * (i + 1);
	for (int i = 0; i < 3; i++)    map[28 - i] = 28 - (i + 1);
	for (int i = 0; i < 4; i++)    map[25 + 5 * i] = 25 + 5 * (i + 1);
	//next=map[next]; 이 원리이다.
	map[24] = 25;
	map[19] = 25;

	DFS(0, 0);

	cout << MAX;

	return 0;
}