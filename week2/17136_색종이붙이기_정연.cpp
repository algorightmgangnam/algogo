#include <iostream>
#include <cstring>
using namespace std;

int map[10][10];
int cnt, answer = 1e9;
int paper[6] = { 0, 5, 5, 5, 5, 5 };

void DFS(int x, int y)
{
	// 열을 다 본 것
	if (y == 10)
	{
		DFS(x + 1, 0);
		return;
	}

	// 끝까지 다 본 것
	if (x == 10)
	{
		if (answer > cnt) answer = cnt;
		return;
	}

	// 덮어져야할 부위가 아닌 것
	if (map[x][y] == 0)
	{
		DFS(x, y + 1);
		return;
	}

	for (int i = 5; i > 0; --i)
	{
		// 색종이를 다 썼거나 범위를 넘어가면 continue
		if (paper[i] == 0 || x + i > 10 || y + i > 10) continue;

		int flag = false;
		for (int j = 0; j < i; ++j)
		{
			for (int k = 0; k < i; ++k)
			{
				if (map[x + j][y + k] == 0)
				{
					flag = true;
					break;
				}
			}

			if (flag) break;
		}

		if (flag) continue;

		// 덮음
		for (int j = 0; j < i; ++j)
		{
			for (int k = 0; k < i; ++k)
			{
				map[x + j][y + k] = 0;
			}
		}

		paper[i]--;
		cnt++;

		DFS(x, y + i);

		// 원래대로
		for (int j = 0; j < i; ++j)
		{
			for (int k = 0; k < i; ++k)
			{
				map[x + j][y + k] = 1;
			}
		}

		paper[i]++;
		cnt--;
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cin >> map[i][j];
		}
	}

	DFS(0, 0);

	if (answer == 1e9) cout << "-1";
	else cout << answer;
}