#문제
	게임을 구현하는 기능이다
	구현되야할 기능들, 기능들의 순서가 필요하다

#문제 설계
	4x4 크기의 빨간 판
	6x4,4x6 크기의 초록, 파란판이 있어야한다

	우선 빨간 판에 블록이 놓였다는 것을 가정.
	주어진 블록을 순서대로 하나씩 놓을것이다.
	블록 각각은 개체로 나타낸다.
	1,2,3블록 각각 struct로 표현하며,

	빨간색이 블록을 놓는다.
	초록판과 파란판에 밝은 영역에 올바르게
	블록을 갖다 놓는 함수
	getGreen, getBlue

	끝까지 움직임을 나타내는 함수:
	1 moveG moveB (움직였다면 1,안움직였다면 0)
	2 	line check를 move가 0을 반환할 때 까지

	밝은 부분 체크 - 있으면?
	출을 1~2개만큼 없애고 다시 1.


	각각의 블록은 어떻게 할것인가?

	2번 3번 블록은 서로 같이 붙어다녀야 한다.
	밝은 부분 체크나 라인 체크로 줄이 사라진 경우
	이 붙었다는 결합이 깨지게 된다.
	이경우엔 어떻게 해야할까?
	블록의 좌표중에 -1이 있다면,
	해당 블록은 없거나 사라진 것으로 간주하자.
	따라서 체크로 인해 사라지거나 삭제된 블록은
	맵상에 표시되지 않으며,
	충돌또한 일으키지 않고 없는것으로 간주된다

	그럼 블록을 어떻게 저장할 것인가?
	블록들의 위치 정보를 맵상에 어떻게 표시할 것인가?
	우선순위 큐를 이용하자
	1. 입력된 블록을 리스트에 저장.
	2. 새 연산자를 이용해 우선순위를 저장하자.
	사라진 블록은 Green의 경우 오른쪽 위 공간
	Blue의 경우 왼쪽 아래 공간에 위치한것으로 가정하자.




