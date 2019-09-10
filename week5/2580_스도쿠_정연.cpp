#include <iostream>
#include <vector>
using namespace std;

int board[9][9];
vector<pair<int, int>> emptySpace;		// 빈 공간 저장 벡터

void DFS(int);

void checkpossible(int y, int x, int idx)
{
	bool num[10] = { 0, };			// 0 ~ 9

	for (int i = 0; i < 9; ++i)
	{
		// 가로 검사
		if (board[y][i]) num[board[y][i]] = true;

		// 세로 검사
		if (board[i][x]) num[board[i][x]] = true;
	}

	// 3*3 검사
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

	// 빈 숫자가 있는지 셈
	for (int i = 1; i <= 9; ++i)
	{
		// 빈 숫자가 있으면 board에 넣고 다음 빈공간 탐색
		if (!num[i])
		{
			board[y][x] = i;

			DFS(idx + 1);

			// 0으로 보드 초기화
			board[y][x] = 0;
		}
		else cnt++;
	}

	// 빈 숫자가 없으면 return
	if (cnt == 9) return;
}

void DFS(int idx)
{
	// idx가 빈 공간 벡터의 수와 같아진다면 출력하고 exit로 종료
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

	// idx는 0부터 시작
	DFS(0);
}
