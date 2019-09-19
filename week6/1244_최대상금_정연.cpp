#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

// 6개의 수 중 똑같은 숫자를 저장하는 구조체
// 가장 큰 수를 넣음
// 배열 idx, 숫자, 중복 횟수
struct same {
	int idx, num, cnt;
};

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int test_case;
	cin >> test_case;

	for (int tc = 1; tc <= test_case; ++tc)
	{
		char input[7] = { 0, };
		int change;
		cin >> input >> change;

		int len = strlen(input);
		int num[7] = { 0, };		// 숫자로 변환

		int savechange = change;	// change 저장
		int savenum[7] = { 0, };	// num 배열 저장

		same s;
		s.idx = 0; s.num = -1; s.cnt = 0;

		for (int i = 0; i < len; ++i)
		{
			num[i] = input[i] - '0';
			savenum[i] = num[i];

			// #5 32888 2의 답을 찾기 위한 과정임 (밑에서 설명)
			// i가 0보다 크고(i-1 때문에 추가한 조건), i번째와 i-1번째가 같으면
			if (i > 0 && num[i] == num[i - 1])
			{
				if (s.num < num[i])			// num[i]가 s.num보다 크면
				{
					s.idx = i;
					s.num = num[i];		// s.num에 더 큰 숫자를 넣음
					s.cnt = 2;			// cnt는 2개
				}
				else if(s.num == num[i])	// 같은 숫자면
				{
					s.idx = i;			// idx 갱신
					s.cnt++;			//  s.cnt 증가
				}
			}
		}

		// swap
		for (int i = 0; i < len; ++i)
		{
			// 교환 횟수 다 쓰면 break
			if (change == 0) break;

			// 가장 큰 수의 idx를 찾음
			int maxidx = i;
			for (int j = i + 1; j < len; ++j) if (num[maxidx] <= num[j]) maxidx = j;

			// i가 아니면 swap하고 change 감소
			if (maxidx != i)
			{
				int tmp = num[maxidx];
				num[maxidx] = num[i];
				num[i] = tmp;
				change--;
			}
		}

		// savenum이 더 큰지 판별하는 boolean
		bool isBig = false;

		// #5 32888 2의 답을 찾기 위한 과정임
		// 중복되는 값이 있고, change의 수가 3과 같거나 작으면 (그 이상이면 savenum underflow)
		if (s.cnt != 0 && savechange <= 3)
		{
			// savechange만큼 반복하면서 savenum swap
			// #5 32888 2의 case를 예로 들면 s.idx는 4. (32)8(88) 둘을 swap하는 과정
			// 또 다른 예인 321888 3을 보면 s.idx는 5. (321)(888) 둘을 swap하는 과정
			for (int i = 0; i < savechange; ++i)
			{
				int tmp = savenum[s.idx - i];
				savenum[s.idx - i] = savenum[savechange - i - 1];
				savenum[savechange - i - 1] = tmp;
			}

			// 그렇게 swap한 savenum과 num을 비교해서 savenum이 더 큰 경우면 isBig true
			for (int i = 0; i < len; ++i)
			{
				if (savenum[i] > num[i])
				{
					isBig = true;
					break;
				}
				else if (savenum[i] == num[i]) continue;
				else break;
			}
			
			// savenum이 더 크니까 num에 옮겨줌
			if (isBig)
			{
				for (int i = 0; i < len; ++i)
				{
					num[i] = savenum[i];
				}
			}
		}

		// #10 456789 10 처리
		// 교환 횟수가 남았는데 남은 교환 횟수가 홀수이고, s.cnt가 0이면 1의 자리와 10의 자리 swap
		// s.cnt == 0을 처리해주는 이유는 #6 777770 5가 반례임 처리 안 해주면 777707 됨 
		if (change > 0 && change % 2 == 1 && s.cnt == 0)
		{
			int tmp = num[len - 1];
			num[len - 1] = num[len - 2];
			num[len - 2] = tmp;
		}

		cout << "#" << tc << " ";

		for (int i = 0; i < len; ++i)
		{
			cout << num[i];
		}
		cout << endl;
	}
}
