#include<iostream>
#include<queue>

using namespace std;
int map[101][101] = { 0, };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); std::cout.tie(0);
	
	int num, x, y;

	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> x >> y;
	
		for (int r = 0; r < 10; r++) {
			for (int c = 0; c < 10; c++) {
				map[100-y -r][x + c] = 1;
			}
		}
	}

	int cnt = 0;
	for (int r = 0; r < 100; r++) {
		for (int c = 0; c < 100; c++) {
			if (map[r][c] == 1) cnt++;
		}
	}

	cout << cnt;
	return 0;


}
