#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define MAX(a,b) a>b?a:b

using namespace std;

int N;
int map[100][100];
bool visited[100][100] = { false, };
int max = 20000;

int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,1,-1 };

vector < pair<int, pair<int, int>>> v;

bool compare(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
	return a.first > b.first;
}

void check(int r, int c, int level) {
	int cr, cc, nr, nc;
	queue<pair<int, int>> q;

	q.push(make_pair(r, c));

	while (!q.empty()) {
		cr = q.front().first;
		cc = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			nr = cr + dr[i];
			nc = cc + dc[i];

			if (nr != -1 && nc != -1 && nr != N && nc != N) {
				if (!visited[nr][nc] && map[nr][nc] > level) {
					visited[nr][nc] = true;
					q.push(make_pair(nr, nc));
				}
			}
		}
	}
	

}

int search(int level) {
	queue<pair<int, int>> q;
	int ret = 0;

	for (int i = 0; i < v.size(); i++) {
		if (v.at(i).first > level) {
			q.push(make_pair(v.at(i).second.first, v.at(i).second.second));
			visited[v.at(i).second.first][v.at(i).second.second] = false;
		}
		else break;
	}
	
	int r, c;

	while (!q.empty()) {
		r = q.front().first;
		c = q.front().second;

		q.pop();
		
		if (visited[r][c]) continue;
		
		visited[r][c] = true;
		ret++;

		check(r, c, level);

	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int max_level = 0, min_level = 101;

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			v.push_back(make_pair(map[i][j], make_pair(i, j)));

			max_level = MAX(max_level, map[i][j]);
			min_level = min(min_level, map[i][j]);
		}
	}

	sort(v.begin(), v.end(), compare);
	int safety = 1;

	for (int i = min_level; i <= max_level; i++) {
		safety = MAX(safety, search(i));
	}
	
	
	cout << safety;

	return 0;
}
