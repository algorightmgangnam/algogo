#include <string>
#include <vector>
#include<iostream>
#include<algorithm>
#include <queue>

using namespace std;

int N, M;
int map[150][150];
bool visited[100][100];


vector<pair<int, int>> v;

int landnum = 1;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

int root[10] = { 0 };
int length[10][10] = { 0 };

bool comp(pair<int, pair<int, int>> p1, pair<int, pair<int, int>> p2) {
	return p1.first < p2.first;
}

void make_set() {
	for (int i = 0; i < 10; i++) {
		root[i] = i;
	}
}
int find(int x) {
	if (root[x] == x) return x;
	else {
		return root[x] = find(root[x]);
	}
}
void union_(int x, int y) {
	x = find(x);
	y = find(y);

	root[x] = y;
}



void dfs(pair<int, int> start) {
	map[start.first][start.second] = landnum;

	int nx, ny;
	for (int i = 0; i < 4; i++) {
		nx = start.first + dx[i];
		ny = start.second + dy[i];

		if (nx < 0 || ny < 0 || nx == N || ny == M) continue;
		if (visited[nx][ny] || map[nx][ny] == 0) continue;

		visited[nx][ny] = true;
		dfs(make_pair(nx, ny));
	}
}

bool bfs(const vector<vector<int>> & v) {
	bool chk[10] = { 0 };

	queue<int> q;

	q.push(1);
	chk[1] = true;
	int current;
	int vn = 1;

	while (!q.empty()) {
		current = q.front();
		q.pop();
		
		for (int i = 0; i < v[current].size(); i++) {
			if (!chk[v[current][i]]) {
				chk[v[current][i]] = true;
				q.push(v[current][i]);
				vn++;
			}
		}
	}
	if (vn != landnum - 1) return false;
	else return true;

}

void put_bridge(int x, int y) {
	int nx = x, ny = y;
	// 4방향으로 다리 놓을 수 있는지 확인
	for (int i = 0; i < 4; i++) {
		nx = x + dx[i];
		ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx == N || ny == M) continue; // 범위 벗어나므로 놓을 수 없음

		int len = 0;
		while (map[nx][ny] == 0) {
			if (nx < 0 || ny < 0 || nx == N || ny == M) break;
			nx = nx + dx[i];
			ny = ny + dy[i];
			len++;
		}
		if (nx < 0 || ny < 0 || nx == N || ny == M) continue;
		if (len < 2) continue;

		if (length[map[x][y]][map[nx][ny]] != 0) {
			length[map[x][y]][map[nx][ny]] = min(len, length[map[x][y]][map[nx][ny]]);
			length[map[nx][ny]][map[x][y]] = min(len,length[map[nx][ny]][map[x][y]]);

		}
		else {
			length[map[x][y]][map[nx][ny]] = len;
			length[map[nx][ny]][map[x][y]] = len;
		}


	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				v.push_back(make_pair(i, j));
				map[i][j] = 10;
			}
		}
	}

	// 1. 섬에 번호 매기기
	for (int i = 0; i < v.size(); i++) {
		if (!visited[v[i].first][v[i].second]) {
			visited[v[i].first][v[i].second] = true;
			dfs(v[i]);
			landnum++;
		}
	}
	
	//for (int i = 0; i < N; i++) {
	//for (int j = 0; j < M; j++) {
	//cout << map[i][j] << " ";
	//}
	//cout << endl;
	//}
	

	make_set();

	// 2. 다리 놓기
	for (int i = 0; i < v.size(); i++) {
		put_bridge(v[i].first, v[i].second);
	}


	// 3. 그래프 만들기


	vector<vector<int>> graph(100);
	for (int i = 1; i < landnum; i++) {
		for (int j = 1; j < landnum; j++) {
			if (i == j) continue;

			if (length[i][j]) {
				graph[i].push_back(j);

			}
		}
	}

	// !!!!!모두 연결되어 있는지 확인!!!!!
	if (!bfs(graph)) {
		cout << "-1";
		exit(0);
	}

	// 4. 최단 경로 찾기
	vector < pair<int, pair<int, int>>> edges;
	for (int i = 1; i < landnum; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			edges.push_back(make_pair(length[i][graph[i][j]], make_pair(i, graph[i][j])));
		}
	}

	sort(edges.begin(), edges.end(), comp);

	int answer = 0;
	
	for (int i = 0; i < edges.size(); i++) {
		
		if (find(edges[i].second.first) == find(edges[i].second.second)) {
			continue;
		}
		else {
			union_(edges[i].second.first, edges[i].second.second);
			answer += edges[i].first;
		}

	}

	if (answer == 0) cout << "-1";
	else	cout << answer;
}
