#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int N, M;
int board[20][20];
bool visited[20][20];
vector<pair<int, int>> enemyDol, emptySpace;
int answer = -1;

// 바뀐 보드를 가지고 죽일 수 있는 상대 돌의 개수를 세는 함수
int KillEnemy()
{
	int killcnt = 0;

	int enemySize = enemyDol.size();
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < enemySize; ++i)
	{
		// 이미 방문했으면 continue
		if (visited[enemyDol[i].first][enemyDol[i].second]) continue;

		queue<pair<int, int>> q;
		q.push({ enemyDol[i].first, enemyDol[i].second });
		visited[enemyDol[i].first][enemyDol[i].second] = true;

		int flag = false;		// 0이 있는지 판단
		int tmpcnt = 0;			// 연결된 그룹의 돌의 갯수

		// bfs
		while (!q.empty())
		{
			int cx = q.front().first;
			int cy = q.front().second;
			q.pop();

			for (int j = 0; j < 4; ++j)
			{
				int nx = cx + dx[j];
				int ny = cy + dy[j];

				if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

				// 방문하지 않았고 상대 돌이면 queue에 push
				// 연결된 그룹을 한번에 구하기 위함
				if (!visited[nx][ny] && board[nx][ny] == 2)
				{
					q.push({ nx, ny });
					visited[nx][ny] = true;
				}
				// 빈 공간이면 flag true
				else if (board[nx][ny] == 0)
				{
					flag = true;
				}
			}

			// 연결된 그룹의 돌의 개수 증가
			tmpcnt++;
		}
		
		// 빈 공간이 없을 때 그룹 돌의 개수를 killcnt에 증가 시켜준다.
		if (!flag) killcnt += tmpcnt;
	}

	return killcnt;
}

// 2개의 돌을 놓는 함수
void PutTwoDol()
{
	int emptySize = emptySpace.size();
	for(int i = 0; i < emptySize; ++i)
	{
		int x1 = emptySpace[i].first, y1 = emptySpace[i].second;
		board[x1][y1] = 1;

		for (int j = i + 1; j < emptySize; ++j)
		{
			int x2 = emptySpace[j].first, y2 = emptySpace[j].second;
			board[x2][y2] = 1;

			answer = max(answer, KillEnemy());

			board[x2][y2] = 0;
		}
		board[x1][y1] = 0;
	}

	cout << answer;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> board[i][j];

			if (board[i][j] == 0) emptySpace.push_back({ i, j });
			else if (board[i][j] == 2) enemyDol.push_back({ i, j });
		}
	}

	PutTwoDol();
}
