#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int MAX = 1500;

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

// 가로, 세로
int R, C;

// 공간 저장 배열
char space[MAX][MAX];

queue<pair<int, int>> swan, newSwan, water, newWater;
pair<int, int> swan_Pos;

bool visited[MAX][MAX];
bool Find = false;

void FindSwan()
{
	while (!swan.empty() && !Find)
	{
		int x = swan.front().first;
		int y = swan.front().second;
		swan.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;

			if (!visited[nx][ny])
			{
				visited[nx][ny] = true;

				if (space[nx][ny] == '.') swan.push(make_pair(nx, ny));
				else if (space[nx][ny] == 'X') newSwan.push(make_pair(nx, ny));
				else if (space[nx][ny] == 'L')
				{
					Find = true;
					break;
				}
			}
		}
	}
}

void Melt()
{
	while (!water.empty())
	{
		int x = water.front().first;
		int y = water.front().second;
		water.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;

			if (space[nx][ny] == 'X')
			{
				space[nx][ny] = '.';
				newWater.push(make_pair(nx, ny));
			}
		}
	}
}

void Solve()
{
	int Day = 0;
	swan.push(make_pair(swan_Pos.first, swan_Pos.second));
	visited[swan_Pos.first][swan_Pos.second] = true;

	while (!Find)
	{
		FindSwan();

		if (!Find)
		{
			Melt();

			water = newWater;
			swan = newSwan;

			while (!newWater.empty()) newWater.pop();
			while (!newSwan.empty()) newSwan.pop();
			Day++;
		}
	}

	cout << Day << endl;
}

int main(void)
{
	cin >> R >> C;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> space[i][j];

			if (space[i][j] != 'X') water.push(make_pair(i, j));
			if (space[i][j] == 'L')
			{
				swan_Pos.first = i;
				swan_Pos.second = j;
			}
		}
	}

	Solve();
}
