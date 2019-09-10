#include<iostream>
#include<vector>
#include<queue>

using namespace std;
int N;
double d_prob[4];//동, 서 남 북
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
bool map[30][30] = { false, };
vector<double> results;

struct robot {
	int prob = 0;
	int x = 0, y = 0;
	int moved = 0;
};

double dfs(int moved, int x, int y, double prob) {

	if (moved == N) {
		//else results.push_back(1.00 - prob);
		return prob;
	}

	double ret = 0.0;

	for (int i = 0; i < 4; i++) {
		if (map[x + dx[i]][y + dy[i]]) continue;

		map[x + dx[i]][y + dy[i]] = 1;
		ret += dfs(moved + 1, x + dx[i], y + dy[i], prob * d_prob[i]);
		map[x + dx[i]][y + dy[i]] = 0;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	int input;
	for (int i = 0; i < 4; i++) {
		cin >> input;
		d_prob[i] = (double)input / 100.0;
	}

	map[15][15] = 1;
	double ans = dfs(0, 15, 15, 1);

	printf("%.9lf\n", ans);


}
