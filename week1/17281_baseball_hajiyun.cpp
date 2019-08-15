#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;
int game_info[51][10];
vector<int> order;
int total_inning;
int ground_info[5]; // X, 1루, 2루, 3루

int cnt = 0;

class Runner {
public:
	int current_runner_idx = 0; // 0 ~ 7
	int current_runner;
	bool flag = true;

	int next() {
		if (current_runner_idx == 3 && flag) { // 4번타자
			flag = false;
			current_runner = 1;
			current_runner_idx--;
		}
		else {
			flag = true;
			current_runner = order[current_runner_idx];
		}
		current_runner_idx = (current_runner_idx + 1) % 8;

		return current_runner;
	}
};

int get_result(int result, int runner) {
	int score = 0;
	if (result == 1) {
		if (ground_info[3] > 0) score++; // 3루 주자 귀환
		for (int i = 2; 0 < i; i--) {
			ground_info[i + 1] = ground_info[i];
		}
		ground_info[1] = runner;

	}
	else if (result == 2) {
		for (int i = 3; 1 < i; i--) { //2, 3루 주자 귀환
			if (ground_info[i] > 0) {
				score++;
				ground_info[i] = 0;
			}
		}
		ground_info[3] = ground_info[1]; // 1루 -> 3루
		ground_info[1] = 0;
		ground_info[2] = runner;
	}
	else if (result == 3) {
		for (int i = 1; i <= 3; i++) { // 각 주자 홈으로 귀환
			if (ground_info[i] > 0) {
				score++;
				ground_info[i] = 0;
			}
		}
		ground_info[3] = runner;
	}
	else if (result == 4) {
		score++; //타자가 획득하는 score

		for (int i = 1; i <= 3; i++) { // 각 주자 홈으로 귀환
			if (ground_info[i] > 0) {
				score++;
				ground_info[i] = 0;
			}
		}
	}
	return score;
}

int play_game() {
	Runner r;

	int cur_runner;
	int out_count = 0;

	int batting_info;
	int score = 0;

	for(int cur_inning = 1; cur_inning <= total_inning ; cur_inning++) {
		memset(ground_info, 0, sizeof(ground_info));
		out_count = 0;


		while (out_count < 3) {
			cur_runner = r.next();
			batting_info = game_info[cur_inning][cur_runner];

			if (batting_info == 0) {
				out_count++;
			}

			else {
				score += get_result(batting_info, cur_runner);
			}
			
		}
	}

	return score;
}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> total_inning;

	
	for (int i = 1; i <= total_inning; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> game_info[i][j];
		}
	}

	for (int i = 2; i <= 9; i++) {
		order.push_back(i);
	}

	int tmp = 0, ans = 0;

	do {
		tmp = play_game();
		ans = max(ans, tmp);
	} while (next_permutation(order.begin(), order.end()));

	cout << ans;


	return 0;
}
