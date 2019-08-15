#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> inp;
bool base[4];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	inp = vector<vector<int>>(n, vector<int>(9));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> inp[i][j];
		}
	}

	vector<int> order = { 1, 2, 3, 4, 5, 6 ,7, 8 };
	int ans = -1;

	do {
		int idx[9];
		memset(idx, 0, sizeof(idx));
		for (int i = 0; i < 3; i++) {
			idx[i] = order[i];
		}
		for (int i = 3; i < 8; i++) {
			idx[i + 1] = order[i];
		}
		int num = 0, player = idx[0];
		int inning = 0, score = 0, out = 0;
		memset(base, false, sizeof(base));
		
		while (inning < n) {
		    int val = inp[inning][player];
			if (val == 0) {
				out += 1;
			}
			else if (val == 1) {
				if (base[3] == 1) {
					score += 1;
					base[3] = 0;
				}
				if (base[2] == 1) {
					base[3] = 1;
					base[2] = 0;
				}
				if (base[1] == 1) {
					base[2] = 1;
					base[1] = 0;
				}
				base[1] = 1;
			}
			else if (val == 2) {
				if (base[3] == 1) {
					score += 1;
					base[3] = 0;
				}
				if (base[2] == 1) {
					score += 1;
					base[2] = 0;
				}
				if (base[1] == 1) {
					base[3] = 1;
					base[1] = 0;
				}
				base[2] = 1;
			}
			else if (val== 3) {
				if (base[3] == 1) {
					score += 1;
					base[3] = 0;
				}
				if (base[2] == 1) {
					score += 1;
					base[2] = 0;
				}
				if (base[1] == 1) {
					score += 1;
					base[1] = 0;
				}
				base[3] = 1;
			}
			else if (val== 4) {
				int check = 0;
				for (int i = 1; i <= 3; i++) {
					if (base[i] == 1) {
						check += 1;
						base[i] = 0;
					}
				}
				score += check + 1;
			}

			if (out == 3) {
				out = 0;
				memset(base, 0, sizeof(base));
				inning += 1;
			}
			if (++num == 9) {
				num = 0;
			}
			player = idx[num];
		}

		if (ans == -1 || score > ans) {
			ans = score;
		}
	} while (next_permutation(order.begin(), order.end()));

	cout << ans << '\n';
	return 0;
}
