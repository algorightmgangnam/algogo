#include <queue>
#include <iostream>
#include<algorithm>

using namespace std;

struct atom {
	int x, y, dir, energy, number;
};

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

bool comp(pair<double,pair<atom, atom>> p1, pair<double, pair<atom, atom>> p2) {
	return p1.first < p2.first;
}

double cond(atom a1, atom a2) {
	// 서로 마주보는가?
	if (a1.dir == 0 && a2.dir == 1) {
		if (a1.x == a2.x && a1.y < a2.y) return (abs(a1.y - a2.y) / 2.0);
		else return 0;
	}

	else if (a1.dir == 2 && a2.dir == 3) {
		if (a1.y == a2.y && a1.x > a2.x) return (abs(a1.x - a2.x) / 2.0);
		return 0;
	}
	else if (a1.dir == 1 && a2.dir == 0) {
		if (a1.x == a2.x && a1.y > a2.y) return (abs(a1.y - a2.y) /2.0);
		else return 0;
	}

	else if (a1.dir == 3 && a2.dir == 2) {
		if (a1.y == a2.y && a1.x < a2.x) return (abs(a1.x - a2.x)/2.0);
		return 0;
	}
	// 서로 직교할 가능성이 있는가?
	if (abs(a1.x - a2.x) == abs(a1.y - a2.y)) { // 둘의 x, y 거리가 같다면 부딪힐 수도 있다
		int sec = abs(a1.x - a2.x); // 그럴 가능성이 있다면 몇 초 후에?

							   // 해당 위치로 이동시켜본 후, 일치한다면 부딪히는 것
		a1.x = a1.x + dx[a1.dir] * sec;
		a1.y = a1.y + dy[a1.dir] * sec;
		a2.x = a2.x + dx[a2.dir] * sec;
		a2.y = a2.y + dy[a2.dir] * sec;

		if (a1.x == a2.x && a1.y == a2.y) {
			return sec;
		}

	}
	return 0;
}

int solve() {
	int n;
	cin >> n;

	vector<atom> v;
	queue<atom> crash;

	// 1. 입력을 받는다.
	int x, y, dir, energy;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> dir >> energy;
		v.push_back({ x, y, dir, energy, i });
	}

	// 2. 시뮬레이션
	atom a1, a2;
	double second;
	vector<pair<double,pair<atom, atom>>> log;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;

			a1 = v.at(i); a2 = v.at(j);

			// 같은 방향으로 이동하는 경우 -> 부딪히지 않는다
			if (a1.dir == a2.dir) {
				continue;
			}
			// 서로 부딪힐 가능성이 있는 경우 검사
			else {
				second = cond(a1, a2);

				if (second != 0) {
					log.push_back(make_pair(second, make_pair(a1, a2)));
				}
			}
		}
	}

	double visited[1000] = { 0, };

	int ans = 0;
	sort(log.begin(), log.end(), comp);

	for (int i = 0; i < log.size(); i++) {
		a1 = log.at(i).second.first;
		a2 = log.at(i).second.second;
		//cout << log.at(i).first << ' ' <<a2.number<< "\n";
		if (visited[a1.number] == 0 && visited[a2.number] == 0) {
			visited[a1.number] = log.at(i).first;
			visited[a2.number] = log.at(i).first;
			ans += a1.energy;
			ans += a2.energy;
		//	<< ans;
		}
		else if (visited[a1.number] != 0 && visited[a2.number] == 0) {
			if (visited[a1.number] == log.at(i).first) {
				visited[a2.number] = log.at(i).first;
				ans += a2.energy;
			}
		}
		else if (visited[a2.number] != 0 && visited[a1.number] == 0) {
			if (visited[a2.number] == log.at(i).first) {
				visited[a1.number] = log.at(i).first;
				ans += a1.energy;
			}
		}
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T = 0;

	cin >> T;

	int ans;
	for (int i = 0; i < T; i++) {
		ans = solve();
		cout << "#" << (i + 1) << " " << ans << "\n";
	}
}
