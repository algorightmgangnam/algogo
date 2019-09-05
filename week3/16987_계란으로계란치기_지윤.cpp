#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int N;
int d[8];
int w[8];
int ans = 0;

void dfs(int idx) {
	if (idx == (N )) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			if (d[i] <= 0) {
				cnt++;
			}

		}
		
		ans = max(cnt, ans);
		return;
	}

	if (d[idx] <= 0) {
		dfs(idx + 1);
		return;
	}

	bool flag = false;

	for (int i = 0; i < N; i++) {
		if (d[i] <= 0) continue;
		if (idx == i) continue;

		flag = true;
		d[idx] = d[idx] - w[i];
		d[i] = d[i] - w[idx];

		dfs(idx + 1);

		d[idx] = d[idx] + w[i];
		d[i] = d[i] + w[idx];
	}
	
	if (!flag) dfs(N);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> d[i] >> w[i];
	}

	dfs(0);
	cout << ans;
}
