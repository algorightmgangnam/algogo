#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int N;
int load[100][100];
int check[100][100];

void BFS() 
{
	queue<pair<int, int>> q;
	q.push({ 0, 0 });

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			
			if (check[nx][ny] > check[x][y] + load[nx][ny])
			{
				check[nx][ny] = check[x][y] + load[nx][ny];
				q.push({ nx, ny });
			}
		}
	}
}

int main() 
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	int tc;
	cin >> tc;

	for (int test_case = 1; test_case <= tc; test_case++)
	{
		memset(check, 9999, sizeof(check));
		check[0][0] = 0;

		cin >> N;

		char input[101];

		for (int i = 0; i < N; i++)
		{
			cin >> input;

			for (int j = 0; j < N; j++)
			{
				load[i][j] = input[j] - '0';
			}
		}

		BFS();

		cout << "#" << test_case << " " << check[N-1][N-1] << "\n";
	}
}
