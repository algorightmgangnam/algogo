#include <iostream>
#include <queue>
#include <cstring>
#define MIN(a, b) (a < b) ? a : b
using namespace std;

// 좌표, 방향, 명령 횟수 저장 구조체
struct info {
	int x, y;
	int dir;
	int cnt;
};

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int M, N;
int factory[101][101];
int visited[101][101][5];	// 최소 방문 횟수 저장

queue<info> robot;

// 1: Go / 2: turn left / 3: turn right
// x, y, dir, command idx, visit count
void command(int x, int y, int dir, int idx, int cnt)
{	
	if (idx == 1)
	{
		// Go 1, 2, 3
		// 이렇게 하면 벽을 통과하지 못하는 케이스도 체크할 수 있음
		for (int i = 1; i <= 3; ++i)
		{
			int nx = x + dx[dir - 1] * i;
			int ny = y + dy[dir - 1] * i;

			// 범위가 넘지 않을 때, 현재 visit cnt가 이미 저장된 방문 횟수보다 클 때, 벽일 때 return
			if (nx <= 0 || ny <= 0 || nx > M || ny > N) return;
			if (visited[nx][ny][dir] <= cnt) return;
			if (factory[nx][ny]) return;

			// push & visited[nx][ny][dir]에 cnt + 1 저장
			robot.push({ nx, ny, dir, cnt + 1 });
			visited[nx][ny][dir] = cnt + 1;
		}
	}
	else if (idx == 2)
	{
		// 방향 전환
		if (dir == 1) dir = 4;
		else if (dir == 2) dir = 3;
		else if (dir == 3) dir = 1;
		else if (dir == 4) dir = 2;

		// 현재 visit cnt가 이미 저장된 방문 횟수보다 클 때 return
		if (visited[x][y][dir] <= cnt) return;
		
		// push & visited[nx][ny][dir]에 cnt + 1 저장
		robot.push({ x, y, dir, cnt + 1 });
		visited[x][y][dir] = cnt + 1;
	}
	else if (idx == 3)
	{
		// 방향 전환
		if (dir == 1) dir = 3;
		else if (dir == 2) dir = 4;
		else if (dir == 3) dir = 2;
		else if (dir == 4) dir = 1;

		// 현재 visit cnt가 이미 저장된 방문 횟수보다 클 때 return
		if (visited[x][y][dir] <= cnt) return;
		
		// push & visited[nx][ny][dir]에 cnt + 1 저장
		robot.push({ x, y, dir, cnt + 1 });
		visited[x][y][dir] = cnt + 1;
	}
}

int main(void)
{
	int startX, startY, startDir, endX, endY, endDir;

	cin >> M >> N;
	for (int i = 1; i <= M; ++i) for (int j = 1; j <= N; ++j) cin >> factory[i][j];
	cin >> startX >> startY >> startDir;
	cin >> endX >> endY >> endDir;

	// 큰 숫자 넣어줌..
	memset(visited, 10000, sizeof(visited));

	robot.push({ startX, startY, startDir, 0 });
	visited[startX][startY][startDir] = 0;

	int answer = 1e9;

	// BFS
	while (!robot.empty())
	{
		int x = robot.front().x;
		int y = robot.front().y;
		int d = robot.front().dir;
		int cnt = robot.front().cnt;
		robot.pop();

		// go, turn left, turn right
		for (int i = 1; i <= 3; ++i) command(x, y, d, i, cnt);
	}

	// 도착지점 좌표와 방향이 일치하는 visited를 출력해준다.
	// 최소 명령 횟수 값이 들어있음
	cout << visited[endX][endY][endDir];
}