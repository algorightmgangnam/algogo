#include <iostream>
#include <algorithm>
using namespace std;

int map[10][10];
int ans=987654321;
int dr[4] = { 0,0,1,-1 };
int dc[4] = { 1,-1,0,0 };
int one_cnt;
int remain[6] = { 0,5,5,5,5,5 };

bool check(int r, int c, int size) {
	for (int i = r; i < r + size; i++) {
		for (int j = c; j < c + size; j++) {
			if (map[i][j] == 0)return false;
		}
	}
	return true;
}

void setVisited(int r, int c, int size) {
	for (int i = r; i < r + size; i++) {
		for (int j = c; j < c + size; j++) {
			map[i][j] = map[i][j] ^ 1;; //XOR
		}
	}
}

void solve(int r, int cnt, int total) {
	if(ans <= cnt)	return; //현재 ans보다 많이 사용
	if (total == one_cnt) { //다지움
		ans = min(ans, cnt);
		return;
	}
	for (int i = r; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 1) {
				bool flag = false;
				for (int k = 5; k >= 1; k--) {
					if (!((i + k - 1) < 10 && (j + k - 1) < 10 && remain[k] > 0)) continue;
					if (flag == false)
						flag = check(i, j, k);
					if (flag == true) {
						setVisited(i, j, k); //0
						remain[k]--;
						solve(i, cnt + 1, total + k * k);
						remain[k]++;
						setVisited(i, j, k); //1
					}
				}
				if (flag == false) //못덮음
					return;
				if (map[i][j] == 1) return; //덮고 나서도 해당좌표를 못지움
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) one_cnt++;
		}
	}


	solve(0, 0, 0);
	if (ans == 987654321)
		ans = -1;
	cout << ans;
	return 0;

}
