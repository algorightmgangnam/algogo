#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int N, M, input;
vector<int> v;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	v.reserve(500000);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> input;
		v.push_back(input);
	}

	sort(v.begin(), v.end());
	cin >> M;

	for (int k = 0; k < M; k++) {
		cin >> input;

		cout<<binary_search(v.begin(), v.end(), input)<<" ";
	}

}
