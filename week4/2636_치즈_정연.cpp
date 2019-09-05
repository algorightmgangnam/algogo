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

	// BFS로 치즈 외부 공기를 찾는다.
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

			// 치즈 외부 공기면 queue에 push
			if (board[nx][ny] == 0) air.push({ nx, ny });
			// 치즈 가장자리면 piece 증가하고, meltingcheese에 push
			else
			{
				piece++;
				meltingcheese.push({ nx, ny });
			}
			visited[nx][ny] = true;
		}
	}

	// piece가 0이면 다 녹았다는 것이기 때문에 바로 0을 return
	if (piece == 0) return 0;

	while(!meltingcheese.empty())
	{
		int mcX = meltingcheese.front().first;
		int mcY = meltingcheese.front().second;
		meltingcheese.pop();

		// 가장자리는 녹았으니까 0으로 바꿔준다.
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

		if (!tmp) break;		// 다 녹았으면 break
		else lastPiece = tmp;
	}

	cout << meltingtime << "\n" << lastPiece;
}