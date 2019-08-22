#include <iostream>
#define MIN(a, b) (a < b) ? a : b
using namespace std;

int n;
int city[17][17];
int save[17][65536];	// 65536 : 2^16

// 1 << n : 1을 n만큼 왼쪽으로 시프트. 1 << 4면 10000
// a = a | (1 << n) : a라는 변수의 n번째 비트를 킴
// a & (1 << n) : a라는 변수의 n번째 비트가 켜져있으면 1 << n을, 아니면 0을 반환

// 점화식 : TSP(curr, visited) = MIN(TSP(next, visited+next)+distance[curr][next])
int TSP(int curr, int visited)
{
	// 점이 7개라면 10000000 - 1 = 01111111
	// 즉, 다 방문했다면 0번 도시로 돌아가고 return
	// ** 처음으로 돌아갔을 때가 0이 아닌지 판별해줘야 틀리지 않음!
	if (visited == (1 << n) - 1)
	{
		if(city[curr][0]) return city[curr][0];
		return 1e9;
	}

	// ** reference를 붙이지 않으면 시간초과!
	int& ret = save[curr][visited];
	if (ret) return ret;
	ret = 1e9;
	for (int i = 0; i < n; ++i)
	{
		// 이미 방문한 도시면 continue
		if (visited & (1 << i)) continue;
		// 길이 없다면 or city[i][i]라면 continue
		if (city[curr][i] == 0) continue;

		// 점화식
		ret = MIN(ret, TSP(i, visited | (1 << i)) + city[curr][i]);
	}

	return ret;
}

int main(void)
{
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> city[i][j];
		}
	}

	cout << TSP(0, 1);
}