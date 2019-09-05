#include<iostream>
#include<queue>

using namespace std;
int map[100][100];
int cheeze_num = 0;
int N, M;
int left_cheeze;

int dr[4] = { 0,0,1,-1 };
int dc[4] = { 1,-1,0,0 };
bool visited[100][100] = { false, };

void bfs() {
	queue<pair<int, int>> q;
	queue<pair<int, int>> next;
	int time = 0;
	
	int r, c, nr, nc;

	q.push(make_pair(0, 0));
	visited[0][0] = true;

	while (cheeze_num > 0) {

		//for (int i = 0; i < N; i++) {
		//	for (int j = 0; j < M; j++) {
		//		std::cout<< map[i][j]<<" ";
		//		
		//	}
		//	std::cout << endl;
		//}

		time++;
		while (!q.empty()) {
			r = q.front().first;
			c = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				nr = r + dr[i];
				nc = c + dc[i];
			
				if (nr >= 0 && nc >= 0 && nr < N && nc < M) {
					if (map[nr][nc] == 0 && !visited[nr][nc]) {
						q.push(make_pair(nr, nc));
						visited[nr][nc] = true;
					}
					else if(map[nr][nc] == 1 && !visited[nr][nc]){
						next.push(make_pair(nr, nc));
						visited[nr][nc] = true;
					}
				}
			}

		}

		if (next.size() == 0) break;

		left_cheeze = next.size();

		while (!next.empty()) {
			r = next.front().first;
			c = next.front().second;
			next.pop();

			map[r][c] = 0;
			cheeze_num--;

			q.push(make_pair(r, c));
		}

	}
	std::cout << time<<"\n";
	std::cout << left_cheeze;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); std::cout.tie(0);
	
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				cheeze_num++;
			}
		}
	}


	bfs();
	return 0;


}
