#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int N;
int input[17][17]; //0:빈칸 1: 벽
int ans;
pair<int, int> h = make_pair(1,1);
pair<int, int> t = make_pair(1,2);

int dr[3] = {0,1,1}; //가로 세로 대각선
int dc[3] = {1,0,1};

void dfs() {
	stack<pair<pair<int, int>,int>> s; //r,s,d(0:가로/1:세로/2:대각선)
	int r,c,nr, nc,d;
	s.push({ { t.first,t.second },0 });

	while (!s.empty()) {
		r = s.top().first.first;
		c = s.top().first.second;
		d = s.top().second;
		s.pop();

		for (int i = 0; i < 3; i++) {
			if (1 - d == i) continue; //가로는 세로X,세로는 가로X
			nr = r + dr[i];
			nc = c + dc[i];
			
			if (!(nr >= 1 && nc >= 1 && nr <= N && nc <= N)) continue;
			if (i == 2) {//대각선
				if (input[nr][nc - 1] || input[nr - 1][nc]) continue;
			}
			if (input[nr][nc]) continue;
			if (nr == N && nc == N) {
				ans++;
				break;
			}

			s.push({ {nr,nc},i });
		}

	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> input[i][j];
		}
	}

	dfs();

	cout << ans;
	return 0;
}
