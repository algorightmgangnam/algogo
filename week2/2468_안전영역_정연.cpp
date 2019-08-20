#include <iostream>
#include <vector>
#include <cstring>
#define MAX(a,b) (a > b) ? a : b
using namespace std;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int n;

int map[100][100];
bool visited[100][100];
int nosink[100][100];

void calDepth(int depth)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (map[i][j] > depth)
				nosink[i][j] = map[i][j];
		}
	}
}

void DFS(int x, int y)
{
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;

		if (!visited[nx][ny] && nosink[nx][ny])
		{
			visited[nx][ny] = true;
			DFS(nx, ny);
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

	int answer = 1;

	for (int depth = 1; depth <= 100; ++depth)
	{
		memset(visited, false, sizeof(visited));
		memset(nosink, 0, sizeof(nosink));

		calDepth(depth);

		int safearea = 0;

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (!visited[i][j] && nosink[i][j])
				{
					safearea++;

					visited[i][j] = true;
					DFS(i, j);
				}
			}
		}

		answer = MAX(answer, safearea);
	}

	cout << answer;
}