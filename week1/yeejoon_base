/*
#include<iostream>
#include<cstring>
#include<vector>
#define MAX 55
using namespace std;
int N, ans;
int map[MAX][MAX]; // [이닝][선수]
int set[9]; //타자 순서
bool isSet[9];



void setHitter(int idx) {
	if (idx == 3) setHitter(idx + 1); return; //4번 타자인 경우 다음 타자로 넘김

	if (idx == 9) { //9명 타자의 순서를 모두 정했을 때
		int temp_ans = 0;
		int nHitter = 0;

		for (int i = 0; i < N; i++)
		{
			int outCnt = 0; // 각 이닝마다 아웃 0으로 
			bool base[4]; // 0:home, 1: 1루, 2:2루, 3:3루
			while (true) //outCnt 가 3이 될 때 break
			{
				for (int j = nHitter; j < 9; j++) //타자만큼 반복
				{
					nHitter = (j + 1 == 9) ? 0 : j + 1;  //다음 이닝 때 칠 순서의 타자 정보 저장
					int state = map[i][set[j]]; //해당 타자의 해당 이닝 때 친 값
					if (state == 4) //홈런인 경우
					{
						temp_ans++;
					}

					if (state != 0) //아웃이 아닌 경우
					{
						for (int k = 3; k > 0; k--)
						{
							if (base[k]) { //베이스에 주자가 있는 경우
								if (k + state >= 4) {//득점
									temp_ans++;
									base[k] = false;
								}
								else {
									//득점하지 않은 경우
									base[k + state] = true;
									base[k] = false;
								}
							}
						}


						if (state < 4) {
							base[state] = true;
						}
					}
					else {
						outCnt++;
						if (outCnt >= 3)
						{
							continue; //다음 이닝으로
						}
					}
				}

			} //while 문 끝
		}//for문 끝
		ans = temp_ans > ans ? temp_ans : ans;
		return;
	}
	for (int i = 1; i < 10; i++) {
		if (!isSet[i]) { // 뽑지 않은 타자라면
			set[idx] = i; // set에 해당 타자 번호 저장
			isSet[i] = true; // 뽑은 것을 표시
			setHitter(idx + 1); // 다음 타자로 재귀 호출
			isSet[i] = false; // 다시 뽑을 수 있도록 false 처리
		}
	}
	

}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> map[i][j];
		}
	}

	set[3] = 0; //4번째 타자는 1번으로 고정
	setHitter(0);

	cout << ans;


	return 0;
}

*/
