#include <iostream>
using namespace std;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	bool dp[100][100] = { 0, };		// drawing paper
	int cpnum;						// color paper num
	int answer = 0;

	cin >> cpnum;
	for (int i = 0; i < cpnum; ++i)
	{
		int cpX, cpY;
		cin >> cpX >> cpY;

		// 10*10 색종이 만큼 도화지에 칠해준다.
		for (int j = 0; j < 10; ++j) for (int k = 0; k < 10; ++k) dp[cpX + j][cpY + k] = true;
	}

	// 도화지 전체를 돌면서 색종이로 덮은 범위 찾기
	for (int i = 0; i < 100; ++i) for (int j = 0; j < 100; ++j) if (dp[i][j]) answer++;

	cout << answer;
}