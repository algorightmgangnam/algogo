#include <iostream>
#define MIN(a, b) (a < b) ? a : b
using namespace std;

char map[50][50];

int Black(int x, int y)
{
	int cnt = 0;

	for (int i = x; i < x + 8; ++i)
	{
		for (int j = y; j < y + 8; ++j)
		{
			// (0,0)이 B --> 행이 짝수이면 B로 시작
			if (i == x || i == x + 2 || i == x + 4 || i == x + 6)
			{
				// BWBWBWBW
				if (j == y || j == y + 2 || j == y + 4 || j == y + 6)
				{
					if (map[i][j] != 'B') cnt++;
				}
				else
				{
					if (map[i][j] != 'W') cnt++;
				}
			}
			else
			{
				if (j == y || j == y + 2 || j == y + 4 || j == y + 6)
				{
					if (map[i][j] != 'W') cnt++;
				}
				else
				{
					if (map[i][j] != 'B') cnt++;
				}
			}
		}
	}

	return cnt;
}

int White(int x, int y)
{
	int cnt = 0;

	for (int i = x; i < x + 8; ++i)
	{
		for (int j = y; j < y + 8; ++j)
		{
			// (0,0)이 W --> 행이 짝수이면 W로 시작
			if (i == x || i == x + 2 || i == x + 4 || i == x + 6)
			{
				// WBWBWBWB
				if (j == y || j == y + 2 || j == y + 4 || j == y + 6)
				{
					if (map[i][j] != 'W') cnt++;
				}
				else
				{
					if (map[i][j] != 'B') cnt++;
				}
			}
			else
			{
				if (j == y || j == y + 2 || j == y + 4 || j == y + 6)
				{
					if (map[i][j] != 'B') cnt++;
				}
				else
				{
					if (map[i][j] != 'W') cnt++;
				}
			}
		}
	}

	return cnt;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int N, M;
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> map[i][j];

	int result = 1e9;
	for (int i = 0; i < N; ++i)
	{
		if (i + 8 > N) break;

		for (int j = 0; j < M; ++j)
		{
			if (j + 8 > M) break;

			int black = Black(i, j);
			int white = White(i, j);
			int min = MIN(black, white);

			result = MIN(result, min);
		}
	}

	cout << result;
}