#문제
	주어진 조건 x,y,d1,d2에 맞춰 선거구를 적절히 나누고
	각 지역구별 인원수 최대와 최소의 차가 최소가 되는 경우를 찾는다.

	x,y,d1,d2 에
	선거구를 나눈다.
	
	선거구별 인원수를 구한다

	차를 구한다

#설계
	모든 경우의 수를 구하는 브루트 포스 문제이다.

	우선 주어진 x,y,d1,d2에 따라 선거구를 나누는 함수를 구현하자
	그리고서 x,y,d1,d2를 모든 조합에 따라 변경시킨다.
	x,y가 다르면 맵이 달라진다.
	d1,d2역시 서로 다른 조합이면 맵이 달라진다
	모든 경우에 대해 조사하자.


#난관
	테스트케이스는 모두 돌아갔는데
	런타임 에러가 떴다...대체왜
	아..N의 범위 문제였다
	N이 20 이하인데
	12이 이하라고 가정했다
	왜 12라고 생각했지?
	숫자 범위 설정 조심하자.