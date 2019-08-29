#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int N, res;
typedef struct egg {
	int naegu;
	int weight;
};
struct egg e[9];

void crush(int cur, int cnt) {
	if (cur == N) //현재 계란이 끝 차례까지 왔을 경우
	{
		res = max(res, cnt);
		return;
	}

	if (e[cur].naegu <= 0) {
		return crush(cur + 1, cnt);//현재 쥔 계란이 깨졌으면 다음 계란으로
	}
	for (int i = 0; i < N; i++)
	{
		//현재 계란이 이미 깨졌거나 현재 계란=다음 계란인 경우 패스
		if (cur == i|| e[i].naegu <= 0) continue;

		//cout << cur << ":" << e[cur].naegu <<"/"<< e[cur].weight << endl;
		//깨졌을 때 내구력 감소
		e[cur].naegu -= e[i].weight; //cout << e[cur].naegu << "/";
		e[i].naegu -= e[cur].weight; //cout << e[i].naegu << endl;
		int t = 0;
		if (e[cur].naegu <= 0) { //쥐고 있는 계란이 깨졌을 때
			t++;
		}
		if (e[i].naegu<=0)//부딪힌 계란이 깨졌을 경우
		{
			t++;
		}

		crush(cur + 1, cnt + t);

		e[cur].naegu += e[i].weight;//초기화 
		e[i].naegu += e[cur].weight;
	}

	res = max(res, cnt);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N; //계란의 수
	for (int i = 0; i < N; i++)
	{
		cin >> e[i].naegu >> e[i].weight;
	}


	crush(0,0);
	cout << res << endl;

	return 0;
}
