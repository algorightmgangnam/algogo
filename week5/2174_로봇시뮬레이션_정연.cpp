#include <iostream>
using namespace std;

const int MAX = 101;

// N부터 시계방향 (북동남서)
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

struct ROBOT {
	int x, y, dir;
};

int A, B, N, M;
ROBOT robot[MAX];
int map[MAX][MAX];

bool Go(int num, int cnt)
{
	int dir = robot[num].dir;

	while(cnt--)
	{
		int nx = robot[num].x + dx[dir];
		int ny = robot[num].y + dy[dir];

		// 벽에 부딪히면
		if (nx < 0 || ny < 0 || nx >= B || ny >= A)
		{
			cout << "Robot " << num << " crashes into the wall\n";
			return true;
		}

		// 로봇이랑 부딪히면
		if (map[nx][ny])
		{
			cout << "Robot " << num << " crashes into robot " << map[nx][ny] << "\n";
			return true;
		}

		// 부딪히지 않으면 로봇 위치 변경
		map[robot[num].x][robot[num].y] = 0;
		robot[num].x = nx;
		robot[num].y = ny;
		map[nx][ny] = num;
	}

	return false;
}

void TurnLeft(int num, int cnt)
{
	// 4로 나누어 떨어지면 제자리니까 return
	if (cnt % 4 == 0) return;

	cnt %= 4;
	robot[num].dir = (4 - cnt + robot[num].dir) % 4;
}

void TurnRight(int num, int cnt)
{
	// 4로 나누어 떨어지면 제자리니까 return
	if (cnt % 4 == 0) return;

	cnt %= 4;
	robot[num].dir = (robot[num].dir + cnt) % 4;
}

int main(void)
{
	cin >> A >> B >> N >> M;

	for (int i = 1; i <= N; ++i)
	{
		char dir;
		cin >> robot[i].y >> robot[i].x >> dir;

		// 0, 0 시작. 좌표계 바꾸기
		robot[i].x = B - robot[i].x;
		robot[i].y = robot[i].y - 1;

		if (dir == 'E') robot[i].dir = 1;
		else if (dir == 'W') robot[i].dir = 3;
		else if (dir == 'S') robot[i].dir = 2;
		else if (dir == 'N') robot[i].dir = 0;

		map[robot[i].x][robot[i].y] = i;
	}

	bool flag = false;
	while (M--)
	{
		int num, cnt;
		char command;
		cin >> num >> command >> cnt;

		if (command == 'F') flag = Go(num, cnt);
		else if (command == 'L') TurnLeft(num, cnt);
		else TurnRight(num, cnt);

		// flag true면 벽에 부딪히거나 로봇이랑 부딪혔으니까 반복문 종료
		if (flag) break;
	}

	// flag false로 빠져나왔다면 부딪히지 않았다는 거니까 OK 출력
	if (!flag) cout << "OK\n";
}