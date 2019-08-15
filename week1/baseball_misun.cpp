#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n;
int input[50][9];
int maxscore = 0;
int order_idx[9]; //_idx[i] =k; i번째 선수 k
bool idx_used[9];

void solve() {
	int outcnt = 0;
	bool board_status[4] = { false, };
	int nidx=0;
	int score = 0;
	for (int i = 0; i < n; i++) {

		while (outcnt < 3) {
			int tmp = input[i][order_idx[nidx]];
			if (tmp == 0) {
				outcnt++;
			}
			else if (tmp == 4) {
				int cntperson = 0;
				for (int k = 0; k < 3; k++) {
					if (board_status[k]) {
						cntperson++;
						board_status[k] = false;
					}
				}
				score += (cntperson + 1);
			}
			else {
				for (int j = 0; j < tmp; j++) {
					for (int k = 2; k >= 0; k--) {
						if (board_status[k]) {
							board_status[k + 1] = true;
							board_status[k] = false;
						}
					}
					if (board_status[3]) {
						score += 1;
						board_status[3] = false;
					}
				}
				board_status[tmp-1] = true;

			}
			
			nidx = (nidx + 1) % 9;
			
		}
		for (int k = 0; k < 4; k++)
			board_status[k] = false;
		outcnt = 0;
	}
	maxscore = max(maxscore, score);
}

void make_order(int k) {
	if (k == 9) {
		solve();
	}

	if (k == 3) {
		order_idx[k] = 0;
		make_order(k + 1);
	}
	else {
		for (int i = 0; i < 9; i++) {
			if (idx_used[i]) continue;
			order_idx[k] = i;
			idx_used[i] = true;
			make_order(k + 1);
			idx_used[i] = false;
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> input[i][j];
		}
	}

	idx_used[0] = true; //1번째 선수 위치 고정
	make_order(0);

	cout << maxscore;
	return 0;
}
