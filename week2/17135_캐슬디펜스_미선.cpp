#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int board[15][15];
int N, M, D;
vector<pair<int, int>> inputv;
vector<pair<int, int>> v;
vector<int> gs;
int target;
int ans;

bool pick(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first) {
		return v[a.second].second < v[b.second].second;
	}
	else
		return a.first < b.first;
}

bool desc(int a, int b) {
	return a > b;
}

void positioning() {
	
	do {
		int t = target;
		int numRemove = 0;
		vector<int> out;
		v = inputv; //적

		while (t > 0) {
			int k[3] = { -1, -1,-1 }; //공격할것 저장
			int idx = 0;

			for (int i = 0; i < M; i++) {
				if (gs[i] > 0) { //궁수 -> 적 공격

					int mind = D;
					vector<pair<int, int>> tmp; //d,j

					//(거리 D이하인 적 중에서 가장 가까운 적)
					 //(여럿이면 가장 왼쪽)
					for (int j = 0; j< v.size(); j++) {
						int d = max(v[j].first, N) - min(v[j].first, N) + max(v[j].second, i) - min(v[j].second, i);
						if (d > mind) continue;

						mind = d;
						tmp.push_back({ d,j });

					}
					if (tmp.size() > 0) {
						std::sort(tmp.begin(), tmp.end(), pick);
						k[idx] = tmp[0].second;/////제거할 v의 인덱스
					}
					else //공격x
						k[idx] = -1;

					idx++;
				}
			}

			//동시에 공격
			//공격받은 적 아웃
			std::sort(k, k + 3, desc);
			for (int i = 0; i < 3; i++) {
				if (k[i] == -1)continue;
				if (i != 0 && k[i] == k[i - 1]) continue;
				numRemove++;
				t--;
				v.erase(v.begin() + k[i]);
			}

			//적 한칸 아래로 이동
			for (int i = 0; i < v.size(); i++) {
				v[i].first += 1;
				//board[N]에 적이 오면 아웃
				if (v[i].first == N)
					out.push_back(i);
			}

			//board[N]에 적이 오면 아웃 제거
			std::sort(out.begin(), out.end(), desc);
			while (!out.empty()) {
				t--;
				v.erase(v.begin() + out[0]);
				out.erase(out.begin());
			}

		}
		ans = max(ans, numRemove);
	
	} while (next_permutation(gs.begin(), gs.end()));
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 1) {
				inputv.push_back({ i,j });
				target++;
			}
		}
	}

	for (int i = 0; i < M; i++) {
		if (i < M-3)
			gs.push_back(0);
		else
			gs.push_back(1);
	}


	positioning();

	cout << ans;

	return 0;
}
