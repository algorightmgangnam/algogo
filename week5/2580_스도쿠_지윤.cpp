#include<iostream>
#include<vector>


using namespace std;

int map[9][9];
vector<pair<int, int>> v;

void dfs(int idx) {
	
	if (idx == v.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << map[i][j] <<" ";
			}
			cout << endl;
		}
		exit(0);
		return;
	}

	bool candi[9] = { 1,1,1,1,1,1,1,1,1 };
	int x = v.at(idx).first;
	int y = v.at(idx).second;

	

	for (int i = 0; i < 9; i++) {
		if(map[x][i] != 0)	candi[map[x][i]-1] = false;
		if(map[i][y] != 0) candi[map[i][y]-1] = false;
	}


	for (int i = 3 * (x/3); i < (3 * (x / 3) + 3); i++) {
		for (int j = 3 * (y/3); j < (3 * (y / 3)+3); j++) {
			if(map[i][j] != 0)

				candi[map[i][j] - 1] = false;
		}
	}

	for (int i = 0; i < 9; i++) {
		if (candi[i]) {
			map[x][y] = (i + 1);
			dfs(idx + 1);
			map[x][y] = 0;
		}
	}

}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) {
				v.push_back(make_pair(i, j));
			}
		}
	}

	dfs(0);
}
