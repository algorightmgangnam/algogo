
// 이 문제는 그냥 문제 읽고 아무 생각 없이 풀면 런타임 에러 뜸... 
//처음에는 그냥 롱롱 배열에 넣고 체크 배열에 그 인덱스 표시해서 있으면 1, 없으며 0 뽑도록 했는데
//이렇게 하니까 런타임 에러 뜨고
//롱롱 벡터에 값 받고 정렬 시킨 뒤 이분탐색
//찾는 값 k 가 v의 mid와 같아질 때까지 탐색하고
//점점 mid 탐색 범위를 반씩 좁혀서 탐색함.. 
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N;// 상근이가 갖고 있는 숫자 카드의 갯수
int M; //이 수를 갖고 있는지 아닌지 알아볼 정수의 갯수
vector<long long> v;

//이분 탐색
int two(int fir, int end, int k) {
	while (fir<=end)
	{
		int mid = (fir + end) / 2;
		if (v[mid] == k)
		{
			return 1;
		}
		else if (v[mid] < k) fir = mid + 1;
		else if (v[mid] > k) end = mid - 1;
	}

	return 0;
}



int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t, k;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> t;
		v.push_back(t);
	}
	sort(v.begin(), v.end());
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> k;
		cout << two(0, v.size() - 1, k) << " ";

	}


	return 0;
}


