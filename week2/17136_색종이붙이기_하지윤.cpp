#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
bool map[10][10];
bool visited[10][10];
int papers = 0;
int ans = 1e9;
int left_paper[6] = { 0,5,5,5,5,5 };

vector<pair<int, int>> v;
int cover(int r, int c, int size) {
	if (left_paper[size] == 0) return 0;
	bool flag = true;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++){
			if (r + i >= 10 || c + j >= 10) return 0;
			if (!visited[r + i][c + j] && map[r + i][c + j]) flag = true;
			else return 0;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (!visited[r + i][c + j] && map[r + i][c + j]) {
				visited[r + i][c + j] = true;
			}
		}
	}
	papers -= (size * size);
	left_paper[size]--;
	return size;
}

void uncover(int r, int c, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			visited[r + i][c + j] = false;
		}
	}
	left_paper[size]++;
	papers += (size * size);
}

void play(int idx, int score) {
	int tmp = 0;
	bool flag = false;
	for (int size = 1; size <= 5; size++) {
		if (left_paper[size] == 0) {
			flag = true;
		}
		else {
			flag = false;
			break;
		}
	}
	if (flag) {
		ans = min(ans, score);
		return;
	}

	if (papers == 0) {
		ans = min(ans, score);
		return;
	}
	
	int r, c;
	for (int i = idx; i < v.size(); i++) {
		r = v.at(i).first;
		c = v.at(i).second;
		if (!map[r][c] || visited[r][c]) continue;
		for (int size = 1; size <= 5; size++) {
			if (left_paper[size] == 0) continue;

			tmp = cover(r, c, size);
			if (tmp > 0) {
				play(i + 1, score + 1);
				uncover(r, c, size);
			}
			else break;
		}
		break;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);


	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> map[i][j];
			if (map[i][j]) {
				papers++;
				v.push_back(make_pair(i, j));
			}
		}
	}
	play(0,0);

	if (ans == 1e9) cout << "-1";

	else	cout << ans;


	return 0;
}
