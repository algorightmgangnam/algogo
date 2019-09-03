
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;
char map[51][51];
int ans = 1e9;

char arr[2][2] = {
	{'W','B'},
	{'B','W'}
};

void chk(int r, int c) {
	
	for (int k = 0; k < 2; k++) {
		int ret = 0;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (map[i + r][j + c] != arr[(i + k) % 2][j % 2]) {
					ret++;
				}
			}
		}

		ans = min(ans, ret);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int r = 0; r <= N - 8; r++) {
		for (int c = 0; c <= M - 8; c++) {
			chk(r, c);
		}
	}
	cout << ans;
}
