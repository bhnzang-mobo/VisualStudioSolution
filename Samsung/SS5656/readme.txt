#문제
	벽돌깨기.
	벽돌은 맨 위에 있는 벽돌만 제거가 가능하며
	총 N회 쏠 수 있으며
	맵의 크기는 WxH이다.
	W는 2~12
	H는 2~15를 가지며,
	N회의 모든 경우의 수 최대 12^4가지를 계산한다.


#설계
	BFS식 설계()
	우선 큐에 x,y를 넣는다.
	pop을 하며 나온 위치를 0으로 변환
	크기만큼 방향에 있는 가능한 모든 좌표를 enqueue;
	다시 반복.

	모든 경우의 수를 DFS로 탐색하는 방법
	

	삭제할게 없는 경우.

	으유 시발 병신
	변수 초기화 visit같은거 못해서 틀리고
	load save 변수 범위가 W,H 제대로 안써서 틀리고
	으유시발시발시발시발시발 병신새끼 