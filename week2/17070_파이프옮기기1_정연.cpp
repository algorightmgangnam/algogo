#include <iostream>
#include <queue>
using namespace std;

const int MAX = 16;

struct info {
	int x, y;
	int dir;
};

int dx[3] = { 0, 1, 1 };
int dy[3] = { 1, 0, 1 };

int n;
int map[MAX][MAX] = { 0, };

queue<info> q;

int answer = 0;

bool inRange(int x1, int y1, int x2, int y2)
{
	if (x1 < 0 || y1 < 0 || x2 >= n || y2 >= n) return false;
	return true;
}

void BFS()
{
	while (!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int pipeDir = q.front().dir;
		q.pop();

		if (x == n - 1 && y == n - 1)
		{
			answer++;
			continue;
		}

		// 가로
		if (pipeDir == 0)
		{
			// 가로
			int nx = x + dx[pipeDir];
			int ny = y + dy[pipeDir];
			if (inRange(x, y, nx, ny) && !map[nx][ny]) q.push({ nx, ny, pipeDir });

			// 대각선
			nx = x + dx[2];
			ny = y + dy[2];
			if (inRange(x, y, nx, ny) && !map[nx][ny] && !map[x + 1][y] && !map[x][y + 1]) q.push({ nx, ny, 2 });
		}
		// 세로
		else if (pipeDir == 1)
		{
			// 세로
			int nx = x + dx[pipeDir];
			int ny = y + dy[pipeDir];
			if (inRange(x, y, nx, ny) && !map[nx][ny]) q.push({ nx, ny, pipeDir });

			// 대각선
			nx = x + dx[2];
			ny = y + dy[2];
			if (inRange(x, y, nx, ny) && !map[nx][ny] && !map[x + 1][y] && !map[x][y + 1]) q.push({ nx, ny, 2 });
		}
		// 대각선
		else if (pipeDir == 2)
		{
			// 대각선
			int nx = x + dx[pipeDir];
			int ny = y + dy[pipeDir];
			if (inRange(x, y, nx, ny) && !map[nx][ny] && !map[x + 1][y] && !map[x][y + 1]) q.push({ nx, ny, pipeDir });

			// 가로세로
			for (int i = 0; i < 2; ++i)
			{
				nx = x + dx[i];
				ny = y + dy[i];
				if (inRange(x, y, nx, ny) && !map[nx][ny]) q.push({ nx, ny, i });
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> map[i][j];
		}
	}

	q.push({0, 1, 0});

	BFS();

	cout << answer;
}