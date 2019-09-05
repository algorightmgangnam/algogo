#include <iostream>
#include <queue>
using namespace std;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int col, row;
int board[100][100];

int meltingtime;

int melt()
{
	queue<pair<int, int>> air;
	queue<pair<int, int>> meltingcheese;
	bool visited[100][100] = { 0, };

	air.push({ 0, 0 });
	visited[0][0] = true;

	int piece = 0;

	// BFS�� ġ�� �ܺ� ���⸦ ã�´�.
	while (!air.empty())
	{
		int cx = air.front().first;
		int cy = air.front().second;
		air.pop();

		for (int i = 0; i < 4; ++i)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= col || ny >= row) continue;
			if (visited[nx][ny]) continue;

			// ġ�� �ܺ� ����� queue�� push
			if (board[nx][ny] == 0) air.push({ nx, ny });
			// ġ�� �����ڸ��� piece �����ϰ�, meltingcheese�� push
			else
			{
				piece++;
				meltingcheese.push({ nx, ny });
			}
			visited[nx][ny] = true;
		}
	}

	// piece�� 0�̸� �� ��Ҵٴ� ���̱� ������ �ٷ� 0�� return
	if (piece == 0) return 0;

	while(!meltingcheese.empty())
	{
		int mcX = meltingcheese.front().first;
		int mcY = meltingcheese.front().second;
		meltingcheese.pop();

		// �����ڸ��� ������ϱ� 0���� �ٲ��ش�.
		board[mcX][mcY] = 0;
	}

	meltingtime++;

	return piece;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> col >> row;

	for (int i = 0; i < col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			cin >> board[i][j];
		}
	}

	int lastPiece = 0;

	while (true)
	{
		int tmp = melt();

		if (!tmp) break;		// �� ������� break
		else lastPiece = tmp;
	}

	cout << meltingtime << "\n" << lastPiece;
}