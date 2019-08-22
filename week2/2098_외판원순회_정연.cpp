#include <iostream>
#define MIN(a, b) (a < b) ? a : b
using namespace std;

int n;
int city[17][17];
int save[17][65536];	// 65536 : 2^16

// 1 << n : 1�� n��ŭ �������� ����Ʈ. 1 << 4�� 10000
// a = a | (1 << n) : a��� ������ n��° ��Ʈ�� Ŵ
// a & (1 << n) : a��� ������ n��° ��Ʈ�� ���������� 1 << n��, �ƴϸ� 0�� ��ȯ

// ��ȭ�� : TSP(curr, visited) = MIN(TSP(next, visited+next)+distance[curr][next])
int TSP(int curr, int visited)
{
	// ���� 7����� 10000000 - 1 = 01111111
	// ��, �� �湮�ߴٸ� 0�� ���÷� ���ư��� return
	// ** ó������ ���ư��� ���� 0�� �ƴ��� �Ǻ������ Ʋ���� ����!
	if (visited == (1 << n) - 1)
	{
		if(city[curr][0]) return city[curr][0];
		return 1e9;
	}

	// ** reference�� ������ ������ �ð��ʰ�!
	int& ret = save[curr][visited];
	if (ret) return ret;
	ret = 1e9;
	for (int i = 0; i < n; ++i)
	{
		// �̹� �湮�� ���ø� continue
		if (visited & (1 << i)) continue;
		// ���� ���ٸ� or city[i][i]��� continue
		if (city[curr][i] == 0) continue;

		// ��ȭ��
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