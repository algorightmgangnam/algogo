#include <iostream>
#include <queue>
using namespace std;

// 고객 번호, 도착시간, 접수 창구
struct customer {
	int num, arrival, rec;
};

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int tc;
	cin >> tc;

	for (int test_case = 1; test_case <= tc; ++test_case)
	{
		int n, m, k, a, b;
		int rectime[10], reptime[10], tk[1001];

		customer recdesk[10] = { 0, }, repdesk[10] = { 0, };	// 창구 상태
		queue<int> recwait;
		queue<pair<int, int>> repwait;		// 고객 번호, 접수 창구 번호

		cin >> n >> m >> k >> a >> b;
		for (int i = 1; i <= n; ++i) cin >> rectime[i];
		for (int i = 1; i <= m; ++i) cin >> reptime[i];
		for (int i = 1; i <= k; ++i) cin >> tk[i];

		int currtime = -1;
		int cnt = 0;
		int answer = 0;

		while (cnt < k)
		{
			currtime++;

			// 현재 시간 = 도착 시간 --> 접수 대기열에 추가
			for (int i = 1; i <= k; ++i) if (tk[i] == currtime) recwait.push(i);

			// 접수 완료 -> 정비 대기열에 추가
			for (int i = 1; i <= n; ++i)
			{
				// 창구가 비어있지 않고, 처리가 완료되면 정비 대기열에 고객 번호와 접수 창구 번호 넣고 num 초기화
				if (recdesk[i].num != 0 && recdesk[i].arrival == currtime)
				{
					repwait.push({ recdesk[i].num, recdesk[i].rec });
					recdesk[i].num = 0;
				}
			}

			// 정비 종료 -> cnt 증가
			for (int i = 1; i <= m; ++i)
			{
				// 창구가 비어있지 않고, 처리가 완료되면
				// 지갑을 잃어버린 고객의 접수&정비 창구 번호가 같은지 확인 -> 같으면 answer에 고객번호를 더함
				// num 초기화 하고 cnt 증가
				if (repdesk[i].num != 0 && repdesk[i].arrival == currtime)
				{
					if (repdesk[i].rec == a && i == b) answer += repdesk[i].num;

					repdesk[i].num = 0;
					cnt++;
				}
			}

			// 접수 
			for (int i = 1; i <= n; ++i)
			{
				// 대기열이 비어있으면 break
				if (recwait.empty()) break;

				// 접수 창고가 비어있다면
				if (recdesk[i].num == 0)
				{
					// 대기열 고객 번호를 recdesk.num에 넣고 pop
					recdesk[i].num = recwait.front();
					recwait.pop();

					// recdesk.arrival에 현재시간 + 처리시간 넣음
					recdesk[i].arrival = currtime + rectime[i];
					// 창구 번호 저장
					recdesk[i].rec = i;
				}
			}

			// 정비
			for (int i = 1; i <= m; ++i)
			{
				// 대기열이 비어있으면 break
				if (repwait.empty()) break;

				// 정비 창구가 비어있다면
				if (repdesk[i].num == 0)
				{
					// 대기열 고객 번호를 repdesk.num에 넣고, 접수 창구 번호를 repdesk.rec에 넣고 pop
					repdesk[i].num = repwait.front().first;
					repdesk[i].rec = repwait.front().second;
					repwait.pop();

					// repdesk.arrival에 현재시간 + 처리시간 넣음
					repdesk[i].arrival = currtime + reptime[i];
				}
			}
		}

		if (answer == 0) answer = -1;

		cout << "#" << test_case << " " << answer << "\n";
	}
}
