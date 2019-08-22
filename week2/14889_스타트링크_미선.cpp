#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N; //짝수
int S[20][20];
int ans = 200;
vector<int> team;

int go(int start) {
	int k = start;
	int s = 0, l = 0;
	for(int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j)continue;
			if ((k&(1 << i))&&(k&(1 << j))) {
				//스타트팀
				s += S[i][j];
			}
			if (!(k&(1 << i)) && !(k&(1 << j))) {
				//링크팀
				l += S[i][j];
			}
		}	
	}
	
	if (s - l < 0) return l - s;
	else return s - l;

}

void solve() {
	do {
		int start=0;
		for (int i = 0; i < N; i++) {
			if(team[i]==1)
				start |=(1<<i);
		}
		
		ans = min(ans,go(start));
	
	} while (next_permutation(team.begin(), team.end()));
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> S[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		if (i < N / 2) team.push_back(0);
		else team.push_back(1);
	}
	solve();

	cout << ans;

	return 0;
}
