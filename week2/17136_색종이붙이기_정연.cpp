#include <iostream>
#include <cstring>
using namespace std;

int map[10][10];
int cnt, answer = 1e9;
int paper[6] = { 0, 5, 5, 5, 5, 5 };

void DFS(int x, int y)
{
	// ���� �� �� ��
	if (y == 10)
	{
		DFS(x + 1, 0);
		return;
	}

	// ������ �� �� ��
	if (x == 10)
	{
		if (answer > cnt) answer = cnt;
		return;
	}

	// ���������� ������ �ƴ� ��
	if (map[x][y] == 0)
	{
		DFS(x, y + 1);
		return;
	}

	for (int i = 5; i > 0; --i)
	{
		// �����̸� �� ��ų� ������ �Ѿ�� continue
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

		// ����
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

		// �������
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