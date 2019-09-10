#include <iostream>
#include <vector>
using namespace std;

int board[9][9];
vector<pair<int, int>> emptySpace;		// �� ���� ���� ����

void DFS(int);

void checkpossible(int y, int x, int idx)
{
	bool num[10] = { 0, };			// 0 ~ 9

	for (int i = 0; i < 9; ++i)
	{
		// ���� �˻�
		if (board[y][i]) num[board[y][i]] = true;

		// ���� �˻�
		if (board[i][x]) num[board[i][x]] = true;
	}

	// 3*3 �˻�
	int ny = (y / 3) * 3;
	int nx = (x / 3) * 3;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (board[ny + i][nx + j]) num[board[ny + i][nx + j]] = true;
		}
	}

	int cnt = 0;

	// �� ���ڰ� �ִ��� ��
	for (int i = 1; i <= 9; ++i)
	{
		// �� ���ڰ� ������ board�� �ְ� ���� ����� Ž��
		if (!num[i])
		{
			board[y][x] = i;

			DFS(idx + 1);

			// 0���� ���� �ʱ�ȭ
			board[y][x] = 0;
		}
		else cnt++;
	}

	// �� ���ڰ� ������ return
	if (cnt == 9) return;
}

void DFS(int idx)
{
	// idx�� �� ���� ������ ���� �������ٸ� ����ϰ� exit�� ����
	if (idx == emptySpace.size())
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				cout << board[i][j] << " ";
			}
			cout << endl;
		}

		exit(0);
	}

	int y = emptySpace[idx].first;
	int x = emptySpace[idx].second;

	checkpossible(y, x, idx);
}

int main(void)
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			cin >> board[i][j];

			if (board[i][j] == 0) emptySpace.push_back({ i, j });
		}
	}

	// idx�� 0���� ����
	DFS(0);
}