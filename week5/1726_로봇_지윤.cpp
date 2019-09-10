#include<iostream>
#include<queue>


using namespace std;

int N, M;
int map[100][100];
int visited[100][100] = { false, };
int rotated[100][100] = { 0, };
int sx, sy, sd, ex, ey, ed;

int cw[5] = { 0,3,4,2,1 };
int ccw[5] = { 0,4 ,3,1,2 };
int dx[5] = {0,0,0,1,-1}; // 동, 서, 남, 북
int dy[5] = {0,1,-1,0,0};

struct info {
	int x, y, dir;
	int cnt;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> M >> N;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	cin >> sx >> sy >> sd;
	cin >> ex >> ey >> ed;

	sx--; sy--;
	ex--; ey--;

	int cnt = 0;
	queue<info> q;
	q.push({ sx,sy,sd, 0 });
	visited[sx][sy] = true;
	
	int cx, cy, nx, ny, cd, nd;
	while (!q.empty()) {
		cx = q.front().x;
		cy = q.front().y;
		cd = q.front().dir;
		cnt = q.front().cnt;

		q.pop();
		//printf("%d %d %d %d\n", cx, cy, cd, cnt);
		
		if (cx == ex && cy == ey && cd == ed) {
			cout << cnt;
			break;
		}

		for (int i = 1; i < 4; i++) {
			nx = cx + dx[cd] *i;
			ny = cy + dy[cd] *i;

			if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
			if (map[nx][ny] == 1) break;
			
			if(!visited[nx][ny]){
				q.push({ nx,ny,cd, cnt+1 });
				visited[nx][ny] = true;
			}
		}

		if (rotated[cx][cy] < 4) {
			q.push({ cx,cy, cw[cd] , cnt + 1 });
			q.push({ cx,cy,ccw[cd], cnt + 1 });
			rotated[cx][cy]++;
		}

	}
}
