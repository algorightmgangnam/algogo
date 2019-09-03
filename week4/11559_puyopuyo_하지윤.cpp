#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

queue<pair<int, int>> puyo_coord;

char map[12][6];
bool visited[12][6];
int dr[4] = { 0,0,1,-1 };
int dc[4] = { 1,-1,0,0 };
int ans = 0;

void move() {
	int r, c;
	for (int i = 10; i >= 0; i--) {
		for (int j = 5; j >= 0; j--) {
			if (map[i][j] == '.') continue;
			r = i, c = j;
			while (r < 12 && map[r+1][c] =='.') {
				r = r + 1;
			}
			char tmp = map[i][j];
		map[i][j] = '.';
		map[r][c] = tmp;

		puyo_coord.push(make_pair(r, c));
		}
		
	}

}

int chk(int r, int c) {
	int nr, nc, cr, cc;
	int cnt = 0;

	queue<pair<int, int>> q;
	q.push(make_pair(r, c));

	while (!q.empty()) {
		cr = q.front().first;
		cc = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			nr = cr + dr[i];
			nc = cc + dc[i];

			if (nr >= 0 && nc >= 0 && nr <= 11 && nc <= 5) {
				if (map[nr][nc] == map[r][c] && !visited[nr][nc]) {
					visited[nr][nc] = true;
					q.push(make_pair(nr, nc));
					cnt++;
				}
			}
		}
	}
	return cnt;
}

void break_puyo_(int r, int c) {
	int nr, nc, cr, cc;
	queue<pair<int, int>> q;
	q.push(make_pair(r, c));
	while (!q.empty()) {
		cr = q.front().first;
		cc = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			nr = cr + dr[i];
			nc = cc + dc[i];

			if (nr >= 0 && nc >= 0 && nr <= 11 && nc <= 5) {
				if (nr == r && nc == c) continue;
				if (map[nr][nc] == map[r][c]) {
					map[nr][nc] = '.';
					q.push(make_pair(nr, nc));
				}
			}
		}
	}
	map[r][c] = '.';
}

int break_puyo() {
	int r, c;
	int ret = 0;
	memset(visited, false, sizeof(visited));
	while (!puyo_coord.empty()) {
		r = puyo_coord.front().first;
		c = puyo_coord.front().second;
		puyo_coord.pop();

		if (map[r][c] == '.') continue;

		if (visited[r][c]) {
			continue;
		}

		if (chk(r, c) >= 4) {
			ret = 1;
			break_puyo_(r, c);
		}
	}


	ans += ret;

	return ret;
}

void play() {

	while (true) {
		if (break_puyo() == 0) break;
		move();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> map[i][j];
			if (map[i][j] != '.') {
				puyo_coord.push(make_pair(i, j));
			}
		}
	}	play();
	cout << ans;
}
