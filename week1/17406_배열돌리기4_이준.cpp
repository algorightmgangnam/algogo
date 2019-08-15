#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
int A[55][55];
typedef struct _Rot {
	int r, c, s;
} Rot;
Rot rot[10];
int N, M, K;
int ans;
void get_input();
bool used[10];
int order[10];
void copy(int A[][55], int B[][55]);
const int dx[] = { +0, +1, +0, -1 };
const int dy[] = { +1, +0, -1, +0 };

void _rotate(int B[][55], int row, int col, int rad) {
	vector<int> val;
	int x = row - rad;
	int y = col - rad;
	int cnt = rad * 8;
	set<pii> check;
	check.insert(make_pair(row + rad, col + rad));
	check.insert(make_pair(row - rad, col + rad));
	check.insert(make_pair(row + rad, col - rad));
	int k = 0;
	for (int i = 0; i < cnt; i++) {
		val.push_back(B[x][y]);
		x += dx[k];
		y += dy[k];
		if (check.find(make_pair(x, y)) != check.end()) {
			k++;
		}
	}
	k = 0;
	x = row - rad;
	y = col - rad;
	x += dx[0];
	y += dy[0];
	for (int i = 0; i < cnt; i++) {
		B[x][y] = val[i];
		x += dx[k];
		y += dy[k];
		if (check.find(make_pair(x, y)) != check.end()) {
			k++;
		}
	}
}
void rotate(int B[][55], int row, int col, int rad) {
	for (int i = 1; i <= rad; i++) {
		_rotate(B, row - 1, col - 1, i);
	}
}
void dfs(int p) {
	if (p < K) {
		for (int i = 0; i < K; i++) {
			if (used[i] == false) {
				used[i] = true;
				order[p] = i;
				dfs(p + 1);
				used[i] = false;
			}
		}
	}
	else {
		//do simulation
		int B[55][55];
		copy(B, A);
		for (int i = 0; i < K; i++) {
			auto& o = rot[order[i]];
			rotate(B, o.r, o.c, o.s);
		}

		for (int i = 0; i < N; i++) {
			int sum = 0;
			for (int j = 0; j < M; j++) {
				sum += B[i][j];
			}
			ans = min(ans, sum);
		}


	}
}
int main() {
	ans = 987654321;
	get_input();
	dfs(0);
	cout << ans << endl;
}

void get_input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> A[i][j];

	for (int i = 0; i < K; i++) {
		auto& R = rot[i];
		cin >> R.r >> R.c >> R.s;
	}
}
void copy(int A[][55], int B[][55]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			A[i][j] = B[i][j];
		}
}
