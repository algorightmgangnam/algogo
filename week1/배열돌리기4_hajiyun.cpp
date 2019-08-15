#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<tuple>

using namespace std;

int map[51][51];
int A[51][51];
int dx[4] = { 1, 0, -1, 0 }; // down, right, up, left
int dy[4] = { 0, 1, 0, -1 };

vector<tuple<int, int, int>> v;
vector<int> perm;

void rotate(int r, int c, int s) {//(r-s, c-s) ~ (r+s, c+s)
	int d = 0; //down, right, up, left
	int x, y, sx, sy, nx, ny;
	int tmp;

	int lowerx, lowery, upperx, uppery;

	for (int i = 1; i <= s; i++) {
		sx = r - s + i -1;
		sy = c - s + i -1;

		lowerx = r - s + i - 2;
		lowery = c - s + i - 2;
		upperx = r + s - i + 2;
		uppery = c + s - i + 2;
		x = sx;
		y = sy;
		tmp = A[sx][sy];
		d = 0;
		do {
			nx = x + dx[d];
			ny = y + dy[d];
			//cout << nx << " " << ny << endl;
			if (nx == lowerx || ny == lowery || nx == upperx || ny == uppery) {
				d = (d + 1) % 4;
				nx = x + dx[d];
				ny = y + dy[d];
			}
			A[x][y] = A[nx][ny];
			x = nx;
			y = ny;


		} while (nx != sx || ny != sy);
		A[x][y + 1] = tmp;
	}


}

int main() {
	int N, M, K;
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	int r, c, s;
	for (int i = 0; i < K; i++) {
		cin >> r >> c >> s; // r,c,s -> (r-s, c-s) ~ (r+s, c+s)
		v.push_back(make_tuple(r, c, s));


	}

	for (int i = 0; i < v.size(); i++) {
		perm.push_back(i);
	}

	int ans = 1000000; // max : 100 * 50 
	do {
		memcpy(A, map, sizeof(map));
		for (int i = 0; i < v.size(); i++) {
			r = get<0>(v.at(perm[i]));
			c = get<1>(v.at(perm[i]));
			s = get<2>(v.at(perm[i]));
			rotate(r, c, s);
		}

		int tmp = 0;
		for (int i = 1; i <= N; i++) {
			tmp = 0;
			for (int j = 1; j <= M; j++) {
				tmp += A[i][j];
			}

			ans = min(ans, tmp);
		}
	} while (next_permutation(perm.begin(), perm.end()));



	cout << ans;


	return 0;
}
