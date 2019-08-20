#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int N, range;
int maximum = -2147483647;
bool selected[20] = { false, };
vector<char> v;

int calc(int a, int b, char c) {
	if (c == '+') {
		return a + b;
	}
	else if (c == '-') {
		return a - b;
	}
	else {
		return a*b;
	}

}

int eval() {
	int ans = v.at(0)-48;
	int operand1, operand2, op;
	for (int i = 2; i < N; ) {

		if (selected[i]) {
			operand1 = v.at(i) - 48;
			op = v.at(i + 1);
			operand2 = v.at(i + 2) - 48;

			operand2 = calc(operand1, operand2, op);
			ans = calc(ans, operand2, v.at(i - 1));
			i += 4;
		}
		else {
			operand1 = ans;
			op = v.at(i - 1);
			operand2 = v.at(i) - 48;
			ans = calc(operand1, operand2, op);
			i += 2;
		}
	}
	return ans;
}

void select(int idx) {
	if (idx > range) {
		maximum = max(maximum, eval());
		return;
	}

	selected[idx] = true;
	select(idx + 4);
	selected[idx] = false;
	select(idx + 2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);


	
	cin >> N;

	int i1 = 0, i2 = 0;
	char input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		v.push_back(input);
	}

	range = N-2;
	select(2);
	cout << maximum;
	return 0;
}
