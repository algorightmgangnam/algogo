#include <iostream>
#include <iomanip>
using namespace std;

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int N;
bool board[30][30];
double dirper[4];
double complexper;

void DFS(int x, int y, int idx, double per)
{
	if (idx == N) return;

	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		double tmp = per * dirper[i];

		if (board[nx][ny])
		{
			complexper += tmp;
			continue;
		}

		board[nx][ny] = true;
		DFS(nx, ny, idx + 1, tmp);
		board[nx][ny] = false;
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> N;

	for (int i = 0; i < 4; ++i)
	{
		cin >> dirper[i];

		dirper[i] /= 100;
	}

	board[15][15] = true;
	DFS(15, 15, 0, 1);

	cout << fixed;
	cout << setprecision(10) << 1 - complexper;
}