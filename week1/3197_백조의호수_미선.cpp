#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int R, C;
int input[1500][1500]; //0:물 1:빙판 2:백조
int day;
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};
queue<pair<int, int>> findq,findnq;
bool visit[1500][1500] = { false, };
queue<pair<int, int>> waterq,waternq;

struct swan {
	int r;
	int c;
};

struct swan s[2];

bool findbfs() {
	int r,c,nr, nc;
	
	while (!findq.empty()) {
		r = findq.front().first;
		c = findq.front().second;
		findq.pop();

		for (int i = 0; i < 4; i++) {
			nr = r + dr[i];
			nc = c + dc[i];
			if (!(nr >= 0 && nr < R&&nc >= 0 && nc < C)) continue;
			if (visit[nr][nc]) continue;
			if (input[nr][nc] == 1){//빙판
				visit[nr][nc] = true;
				findnq.push(make_pair(nr, nc));
				continue;
			}
			
			if (nr == s[1].r && nc == s[1].c) { //다른백조
				return true;
			}

			findq.push(make_pair(nr, nc));
			visit[nr][nc] = true;

		}
	}
	return false;

}

void icetowater() {
	int r,c,nr, nc;

	while (!waterq.empty()) {
		r = waterq.front().first;
		c = waterq.front().second;
		waterq.pop();

		for (int i = 0; i < 4; i++) {
			nr = r + dr[i];
			nc = c + dc[i];
			if (!(nr >= 0 && nr < R&&nc >= 0 && nc < C)) continue;

			if (input[nr][nc] == 1) { //빙하
				input[nr][nc] = 0;
				waternq.push({ nr,nc });				
			}
		}
	}
}

void solve() {
	findq.push(make_pair(s[0].r, s[0].c));
	visit[s[0].r][s[0].c] = true;

	while (1) {
		//만나는지 확인
		if (findbfs()) {
			cout << day;
			break;
		}

		findq = findnq;
		while (!findnq.empty()) findnq.pop();
		
		//얼음녹기
		day++;
		icetowater();
		waterq = waternq;
		while (!waternq.empty()) waternq.pop();
	}
	return;
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	string str;
	int idx = 0;

	cin >> R >> C;
	getline(cin, str);

	for (int i = 0; i < R; i++) {
		getline(cin, str);
		for (int j = 0; j < C; j++) {
			if (str[j] == 'L') {
				input[i][j] = 2;
				s[idx].r = i;
				s[idx].c = j;
				idx++;
			}
			else
				input[i][j] = (str[j] == '.' ? 0 : 1);

			if (input[i][j] != 1)
				waterq.push({ i,j });
		}
	}

	solve();

	return 0;
}
