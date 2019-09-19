#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cout << fixed;
	cout.precision(10);

	int tc;
	cin >> tc;

	for (int test_case = 1; test_case <= tc; ++test_case)
	{
		int n;
		int x[10] = { 0, }, m[10] = { 0, };

		cin >> n;
		for (int i = 0; i < n; ++i) cin >> x[i];		// x좌표 입력
		for (int i = 0; i < n; ++i) cin >> m[i];		// 질량 입력

		cout << "#" << test_case << " ";
		for (int i = 0; i < n - 1; ++i)
		{
			double left = x[i];
			double right = x[i + 1];
			double balance = 0;

			for (int j = 0; j < 50; ++j)
			{
				double mid = (left + right) / 2;
				double force = 0;

				// 왼쪽 자성체의 인력
				for (int k = 0; k <= i; ++k) force += m[k] / ((mid - x[k]) * (mid - x[k]));
				// 오른쪽 자성체의 인력
				for (int k = i + 1; k < n; ++k) force -= m[k] / ((mid - x[k]) * (mid - x[k]));
				
				balance = mid;

				// 0보다 크면 왼쪽이 더 강하다는 것이기 때문에 left가 mid가 됨
				if (force > 0) left = mid;
				// 0과 같으면 균형점
				else if (force == 0) break;
				// 0보다 작으면 오른쪽이 더 강하다는 것이기 때문에 right가 mid가 됨
				else right = mid;
			}

			cout << balance << " ";
		}
		cout << "\n";
	}
}
