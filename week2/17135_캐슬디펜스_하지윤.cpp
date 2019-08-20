#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M, D;
int map[16][16];
bool selected[16] = { false, };

int ans = 0;
struct enemy {
	int r, c, id;
};

vector<enemy> v;
int play() {
	int len, r, c, id, dist,ret=0;
	queue<enemy> q;
	vector<int> archer;
	int e[3];
	bool dead[300] = { false, };
	for (int i = 0; i < v.size(); i++) {
		q.push(v.at(i));
	}
	for (int i = 0; i < 16; i++) {
		if (selected[i]) archer.push_back(i);
	}

	while (!q.empty()) {
		len = q.size();
		int d[3] = { N + 1, N + 1,N + 1 };
		while (len--) {
			r = q.front().r;
			c = q.front().c;
			id = q.front().id;

			q.pop();
			if (dead[id]) {
				ret++;
				continue;
			}
			if (r == N) continue;

			for (int i = 0; i < 3; i++) {
				dist = abs(N - r) + abs(c - archer[i]);
				if (dist <= D) {
					if (dist < d[i]) {
						d[i] = dist;
						e[i] = id;
					}
					else if (dist == d[i] && c< v[e[i]].c) {
						d[i] = dist;
						e[i] = id;
					}
			
				}
			}
			q.push({ r + 1,c,id });
		}

		for (int i = 0; i < 3; i++) {
			if (d[i] != N + 1) {
				dead[e[i]] = true;
				
			}
		}
	}
//	cout << ret << endl;
	return ret;
}

void select(int cnt, int idx) {
	if (cnt == 3) {
		ans = max(ans,play());
		return;
	}
	else {
		for (int i = idx; i < M; i++) {
			selected[i] = true;
			select(cnt + 1, i + 1);
			selected[i] = false;
			//select(cnt, i + 1);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> D;
	int id = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin>>map[i][j];
			if (map[i][j] == 1) {
				v.push_back({ i,j,id });
				id++;
			}
		}
	}

	select(0, 0);

	cout << ans;

	return 0;
}
