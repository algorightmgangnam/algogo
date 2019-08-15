#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

int n, m, k;
int A[51][51]; //입력
int B[51][51]; //회전후저장
int Avalue = 1e9;
int Mrotate[6][3]; //r,c,s
int Mrotate_order[6];

int dy[4] = {0,1,0,-1}; //우하좌상
int dx[4] = {1,0,-1,0};

//Mrotate[idx]를 이용하여 회전
void rotate(int idx) {
	int tmp[51][51];
	int ny, nx;
	int r = Mrotate[idx][0];
	int c = Mrotate[idx][1];
	int s = Mrotate[idx][2];

	pair<int, int> first = { r - s-1,c - s-1 };
	pair<int, int> last = { r + s-1,c + s-1 };

	memcpy(tmp, B, sizeof(B));
	while (1) {
		ny = first.first; nx = first.second;
		while (nx < last.second) {
			tmp[ny][nx + 1] = B[ny][nx];
			ny += dy[0];
			nx += dx[0];

		}

		ny = first.first; nx = last.second;
		while (ny < last.first) {
			tmp[ny + 1][nx] = B[ny][nx];
			ny += dy[1];
			nx += dx[1];
		}

		ny = last.first; nx = last.second;
		while (nx > first.second) {
			tmp[ny][nx - 1] = B[ny][nx];
			ny += dy[2];
			nx += dx[2];
		}

		ny = last.first; nx = first.second;
		while (ny > first.first) {
			tmp[ny - 1][nx] = B[ny][nx];
			ny += dy[3];
			nx += dx[3];
		}

		first.first += 1;
		first.second += 1;
		last.first -= 1;
		last.second -= 1;

		if (first.first >= last.first && first.second >= last.second)
			break;
	}

	memcpy(B, tmp, sizeof(B));
}

void calA() {
	int rowsum;
	for (int i = 0; i < n; i++) {
		rowsum = 0;
		for (int j = 0; j < m; j++) {
			rowsum += B[i][j];
		}
		Avalue = min(Avalue, rowsum);
	}
}

void solve() {
	
	do {
		memcpy(B, A, sizeof(A));
		for (int i = 0; i < k; i++) {
			rotate(Mrotate_order[i]);
		}

		calA();

	} while (next_permutation(Mrotate_order, Mrotate_order + k));

}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> Mrotate[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		Mrotate_order[i] = i;
	}

	solve();


	cout << Avalue;
	return 0;
}
