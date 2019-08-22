#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N;
int input[101][101];
int maxareanum = 1;
int dr[4] = { 0,0,1,-1 };
int dc[4] = {1,-1,0,0};


int bfs(int h) {
	bool visit[101][101] = { false, };
	queue<pair<int, int>> q;
	int r,c,nr, nc;
	int numarea = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j]) continue;
			if (input[i][j] <= h) continue;

			q.push({ i,j });
			visit[i][j] = true;

			while (!q.empty()) {
				r = q.front().first;
				c = q.front().second;
				q.pop();

				for (int k = 0; k < 4; k++) {
					nr = r + dr[k];
					nc = c + dc[k];

					if (!(nr >= 0 && nc >= 0 && nr < N &&nc < N))continue;
					if (visit[nr][nc]) continue;
					visit[nr][nc] = true;

					if (input[nr][nc] <= h) continue;

					q.push({ nr,nc });
					visit[nr][nc] = true;
				}
			}
			numarea++;
		}
	}
	return numarea;
	
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int m = 0;

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> input[i][j];
			if (input[i][j] > m)
				m = input[i][j];
		}
	}

	for (int i = 1; i <m; i++) {
		maxareanum = max(bfs(i),maxareanum);
	}

	cout << maxareanum;
}
