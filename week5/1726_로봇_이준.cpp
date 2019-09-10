#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX = 100;
typedef struct

{

	int y, x;

}dir;

dir moveDir[5] = { { 0, 0 },{ 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 } };

int M, N;
pair<pair<int, int>, int> start, finish;
int arr[MAX][MAX];
bool visited[MAX][MAX][5];

int BFS(void)
{

	queue<pair<pair<int, int>, pair<int, int>>> q;

	q.push({ { start.first.first, start.first.second },{ start.second, 0 } });

	visited[start.first.first][start.first.second][start.second] = true;



	while (!q.empty())

	{

		int y = q.front().first.first;

		int x = q.front().first.second;

		int dir = q.front().second.first;

		int cnt = q.front().second.second;

		q.pop();



		//cout << y << " " << x << " " << dir << " " << cnt<<"\n";

		if (y == finish.first.first && x == finish.first.second && dir == finish.second)

			return cnt;



		//해당 방향으로 1, 2, 3칸

		for (int i = 1; i <= 3; i++)

		{

			int nextY = y + moveDir[dir].y * i;

			int nextX = x + moveDir[dir].x * i;



			//이미 방문한 지점

			if (visited[nextY][nextX][dir])

				continue;



			if (0 <= nextY && nextY < M && 0 <= nextX && nextX < N && !arr[nextY][nextX])

			{

				visited[nextY][nextX][dir] = true;

				q.push({ { nextY, nextX },{ dir, cnt + 1 } });

			}

			//뚫고 못 간다

			else

				break;

		}



		//방향 전환

		for (int i = 1; i <= 4; i++)

		{

			if (dir != i && !visited[y][x][i])

			{

				visited[y][x][i] = true;

				if ((dir == 1 && i == 2) || (dir == 2 && i == 1) || (dir == 3 && i == 4) || (dir == 4 && i == 3))

					q.push({ { y, x },{ i, cnt + 2 } });

				else

					q.push({ { y, x },{ i, cnt + 1 } });

			}

		}

	}

	return -1;

}



int main(void)

{

	ios_base::sync_with_stdio(0);

	cin.tie(0);

	cin >> M >> N;



	for (int i = 0; i < M; i++)

		for (int j = 0; j < N; j++)

			cin >> arr[i][j];



	cin >> start.first.first >> start.first.second >> start.second;

	cin >> finish.first.first >> finish.first.second >> finish.second;



	start.first.first -= 1;

	start.first.second -= 1;

	finish.first.first -= 1;

	finish.first.second -= 1;

	cout << BFS() << "\n";

	return 0;

}
