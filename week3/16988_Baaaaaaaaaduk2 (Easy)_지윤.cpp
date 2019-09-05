#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int map[20][20];
vector<pair<int, int>> v;
vector<pair<int, int>> black_stone;
bool chk[400];
int N, M, ans = 0;
int dr[4] = { 0,0,1,-1 };
int dc[4] = { 1,-1,0,0 };

void bfs() {
	bool visited[20][20] = { false, };
	int r, c, nr, nc;
	int killed = 0;
	for (int i = 0; i < black_stone.size(); i++) {
		r = black_stone.at(i).first;
		c = black_stone.at(i).second;

		if (visited[r][c]) continue;
		else {
			queue<pair<int, int>> q;
			q.push(make_pair(r, c));

			bool flag = true;
			int tmp = 0;
			while (!q.empty()) {
				r = q.front().first;
				c = q.front().second;
				q.pop();
				for (int i = 0; i < 4; i++) {
					nr = r + dr[i];
					nc = c + dc[i];

					if (nr >= 0 && nc >= 0 && nr < N && nc < M) {
						if (map[nr][nc] == 2 && !visited[nr][nc]) {
							q.push(make_pair(nr, nc));
							visited[nr][nc] = true;
							tmp++;
						}
						else if (map[nr][nc] == 0) {
							flag = false;
							break;
						}
					}
				}
			}
			if (flag) {
				if (tmp == 0) killed += 1;
				else killed += tmp;
			}

		}

	}
	ans = max(ans, killed);
}

void select(int idx, int cnt) {
	if (cnt == 2) {
		bfs();
		return;
	}

	if (idx >= v.size()) return;

	map[v.at(idx).first][v.at(idx).second] = 1;
	select(idx + 1, cnt + 1);
	map[v.at(idx).first][v.at(idx).second] = 0;
	select(idx + 1, cnt);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) v.push_back(make_pair(i, j));
			else if (map[i][j] == 2) black_stone.push_back(make_pair(i, j));
		}
	}
	select(0, 0);

	cout << ans;
}
