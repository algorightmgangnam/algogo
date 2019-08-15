#include<iostream>
#include<queue>
#include<tuple>
#include<cstring>

using namespace std;

int map[1501][1501];
pair<int, int> bird;
queue<tuple<int, int, int>> water;
queue<pair<int, int>> q[2];
bool v[1501][1501] = { false, };
int R, C;

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0,0,1,-1 };
int idx = 0;


void melt() {
	int len = water.size();
	int r, c, nr, nc;
	bool can_melt = false;
	int minday;

	memset(v, false, sizeof(v));
	while (!water.empty()) {
		r = get<0>(water.front());
		c = get<1>(water.front());
		minday = get<2>(water.front());

		water.pop();
		can_melt = false;

		for (int i = 0; i < 4; i++) {
			nr = r + dr[i];
			nc = c + dc[i];

			if (nr != -1 && nc != -1 && nr != R && nc != C) {
				if (map[nr][nc] == 3000 && !v[nr][nc]) {
					water.push(make_tuple(nr, nc, minday + 1));
					v[nr][nc] = true;
					map[nr][nc] = minday + 1;
				}
			}
		}
	}
}



bool bfs(int day) {
	//memset(v, false, sizeof(v));


	int r, c, nr, nc;
	int len = q[idx].size();

	while (!q[idx].empty()) {
		r = q[idx].front().first;
		c = q[idx].front().second;

		q[idx].pop();

		for (int i = 0; i < 4; i++) {
			nr = r + dr[i];
			nc = c + dc[i];

			if (nr != -1 && nc != -1 && nr != R && nc != C) {
				if (!v[nr][nc] && map[nr][nc] <= day) {
					if (map[nr][nc] == -1) {
						return true;
					}
					else if (true) {
						v[nr][nc] = true;
						q[idx].push(make_pair(nr, nc));
					}
				}
				else if (!v[nr][nc] && map[nr][nc] == day + 1) {
					v[nr][nc] = true;
					q[(idx + 1) % 2].push(make_pair(nr, nc));
				}
			}
		}
	}
	return false;
}

int main() {


	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> R >> C;
	char input;

	q[0] = queue<pair<int, int>>();
	q[1] = queue<pair<int, int>>();
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> input;
			if (input == 'L') {
				bird.first = i;
				bird.second = j;
				map[i][j] = -1;
				water.push(make_tuple(i, j, 0));
			}
			else if (input == 'X') {
				map[i][j] = 3000;
			}
			else {
				water.push(make_tuple(i, j, 0));
				map[i][j] = 0;
			}
		}
	}

	int day = 0;


	melt();
	memset(v, false, sizeof(v));
	q[idx].push(bird);
	v[bird.first][bird.second] = true;
	while (true) {
		day++;
		
		if (bfs(day)) break;

		idx = (idx + 1) % 2;
		//cout << day << endl;

	}

	cout << day;
	return 0;
}
