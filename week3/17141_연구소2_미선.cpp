#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;

int N, M;
int virusNum;
vector<int> putV; //바이러스를 놓은 v의 인덱스
vector<pair<int, int>> v; //바이러스 좌표
queue<pair<int, int>> q;

int input[51][51]; //0:빈칸 1:벽 2:바이러스가능
int visit[51][51];
int dr[4] = { 0,0,-1,1 };
int dc[4] = { -1,1,0,0 };
int ans;


void solve() {
	do {
		int r, c, nr, nc;
		int time = 0;

		memset(visit, -1, sizeof(visit));

		for (int i = 0; i < virusNum; i++) {
			if (putV[i] == 1) {
				q.push({ v[i].first,v[i].second });
				visit[v[i].first][v[i].second] = 0;
			}
		}

		while (!q.empty()) {
			r = q.front().first;
			c = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				nr = r + dr[i];
				nc = c + dc[i];
				if (!(nr >= 0 && nc >= 0 && nr < N&& nc < N)) continue;
				if (input[nr][nc] == 1) continue; //벽
				if (visit[nr][nc] >= 0) continue;

				visit[nr][nc] = visit[r][c] + 1;
				time = max(time, visit[nr][nc]);
				q.push({ nr,nc });
			}
		}

		bool nonvisit = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visit[i][j] == -1 && input[i][j] == 0)
					nonvisit = true;
			}
		}
		if (!nonvisit)
			ans = min(ans, time);


	} while (next_permutation(putV.begin(), putV.end()));
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> M;
	ans = N * N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> input[i][j];
			if (input[i][j] == 2) {
				v.push_back({ i,j });
				virusNum++;
			}
		}
	}

	for (int i = 0; i < virusNum; i++) {
		if (i < virusNum - M)
			putV.push_back(0);
		else
			putV.push_back(1);
	}

	solve();
	if (ans == N * N)
		cout << -1;
	else
		cout << ans;

	return 0;
}
