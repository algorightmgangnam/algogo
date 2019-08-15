#include <iostream>
#include <algorithm>
#define MAX(a, b) (a > b) ? a : b
using namespace std;

// 이닝 수
int N;
// 타격 정보 저장 배열
int batting[50][9];

int answer = -1;

// 게임을 진행하는 함수
void Play(int *player)
{
	int playerNum[9] = { 0, };

	for (int i = 0; i < 3; ++i) playerNum[i] = player[i];
	playerNum[3] = 0;
	for (int i = 4; i < 9; ++i) playerNum[i] = player[i - 1];

	int total = 0;	// 점수
	int curr = 0;	// 현재 타순

	for (int i = 0; i < N; ++i)
	{
		int outcnt = 0;			// 아웃 카운트
		bool base[4] = { 0, };	// 베이스에 사람이 있는지 판별

		// 삼진 당할 때까지 반복
		while (outcnt < 3)
		{
			// 아웃이면
			if (batting[i][playerNum[curr]] == 0)
			{
				outcnt++;
			}
			// 홈런이면
			else if (batting[i][playerNum[curr]] == 4)
			{
				for (int j = 3; j > 0; --j)
				{
					// 모든 주자를 홈으로 부르고 점수 1점씩 추가
					if (base[j])
					{
						total++;
						base[j] = false;
					}
				}

				// 그리고 본인 점수 추가
				total++;
			}
			// 안타면
			else
			{
				// 진루한 주자 처리
				for (int j = 3; j > 0; --j)
				{
					if (base[j])
					{
						// 현재 베이스 + 진루가 3을 넘어가면 홈 도착 
						if (j + batting[i][playerNum[curr]] > 3)
						{
							total++;
							base[j] = false;
						}
						else
						{
							base[j + batting[i][playerNum[curr]]] = true;
							base[j] = false;
						}
					}
				}

				// 진루
				base[batting[i][playerNum[curr]]] = true;
			}

			// 타순 증가
			curr++;
			// 9번 타자까지 했으면 1번 타자로 돌아감
			if (curr == 9) curr = 0;
		}
	}

	answer = MAX(answer, total);
}

// 타순 정하는 함수
void SetSeq()
{
	int playerNum[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	// 순열로 타순 만들어줌
	do
	{
		Play(playerNum);
	} while (next_permutation(playerNum, playerNum + 8));
}

int main(void)
{
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			cin >> batting[i][j];
		}
	}

	SetSeq();

	cout << answer;
}
