#include <iostream> //3:10~

using namespace std;

int N, ans = 0;
int S[8];
int W[8];

bool Check(int index){
	for (int i = 0; i <N; i++){
		if (index == i) continue;
		if (S[i]>0) return 1;
	}
	return 0;
}
void Solve(int index){
	if (index == N){
		int cnt = 0;
		for (int i = 0; i < N; i++){
			if (S[i]<=0){
				cnt++;
			}
		}
		if (ans < cnt) ans = cnt;
		return;
	}
	if (S[index]<=0 || Check(index) == 0){
		Solve(index + 1);
	}
	if(S[index]>=0 && Check(index)==1){
		for (int i = 0; i < N; i++){
			if (index == i || S[i]<=0) continue;
			S[index] -= W[i];
			S[i] -= W[index];
			Solve(index + 1);
			S[index] += W[i];
			S[i] += W[index];
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> S[i] >> W[i];
	}
	Solve(0);
	cout << ans;
	return 0;
}