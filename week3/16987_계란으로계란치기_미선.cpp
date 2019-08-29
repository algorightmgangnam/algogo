#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<pair<int, int>> breakeggs;
int maxbroken = 0;
int broken=0;

void breaking(int k) {
	bool canbreak = false;
	if (k == N) {
		maxbroken = max(maxbroken, broken);
		if (maxbroken == N) {
			cout << N;
			exit(0);
		}
		return;
	}

	if (breakeggs[k].first <= 0) {
		//깨짐
		breaking(k + 1);
		return;
	}

	for (int i = 0; i < N; i++) {
		if (k == i)continue;
		if (breakeggs[i].first <= 0) //깨짐
			continue;

		canbreak = true;
		//치기
		breakeggs[k].first -= breakeggs[i].second;
		breakeggs[i].first -= breakeggs[k].second;
		if (breakeggs[k].first <= 0)
			broken++;
		if (breakeggs[i].first <= 0)
			broken++;
		breaking(k + 1);
		//원래값
		if (breakeggs[k].first <= 0)
			broken--;
		if (breakeggs[i].first <= 0)
			broken--;
		breakeggs[k].first += breakeggs[i].second;
		breakeggs[i].first += breakeggs[k].second;
	}
	if (canbreak == false) {
		breaking(k + 1);
		return;
	}
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int a, b;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		breakeggs.push_back({ a,b });
	}

	breaking(0);
	cout << maxbroken;

	return 0;
}
