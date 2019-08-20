#include<iostream>
#include<queue>
#include<tuple>
#include<cstring>

using namespace std;

int dr[3] = {0,1,1}; // 가로, 세로, 대각선
int dc[3] = {1,0,1};

int N;
int map[18][18];

bool can_reach(int r,int c,int state) {
	int w,x,y,z;
	w = map[r][c];
	x = map[r][c+1];
	y = map[r + 1][c];
	z = map[r + 1][c + 1];
	
	if (state == 0) return(w + x == 0);
	else if (state == 1) return(w + y == 0);
	else return (w + x + y + z == 0);

}

bool at_end(int r, int c, int state) {
	

	if (state == 2 && r+1 == N && c+1==N) return true;
	else if (state == 1 && r+1 == N && c == N) return true;
	else if (state == 0 && r == N && c+1 == N) return true;
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i <= 17; i++) {
		for (int j = 0; j <= 17; j++) {
			map[i][j] = 1;
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	/*for (int i = 0; i <= 17; i++) {
		for (int j = 0; j <= 17; j++) {
			cout<<map[i][j];
		}
		cout << endl;
	}*/

	queue<tuple<int, int, int>> q; // state, r, c

	q.push(make_tuple(0, 1, 1));
	int r, c, state, nr, nc, ns;
	int ans = 0;

	int step;
	while (!q.empty()) {
		state = get<0>(q.front());
		r = get<1>(q.front());
		c = get<2>(q.front());
		q.pop();
		nr = r + dr[state];
		nc = c + dc[state];
		bool flag = false;
		//cout << "debug";

		//cout << state << " " << r << " " << c << endl;
		for (ns = 0; ns <= 2; ns++) {
			flag = false;
			//cin >> step;
			if (state==2 || (state == 1 && ns != 0) || (state == 0 && ns != 1)){
				flag = can_reach(nr, nc, ns); 
				if (flag) {
					if (!at_end(nr, nc, ns)) {
						q.push(make_tuple(ns, nr, nc));
					}
					else {
						ans++;
					}
				}
			}
			
		}
	}

	cout << ans;

	return 0;
}
