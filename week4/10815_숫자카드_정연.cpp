#include <iostream>
#include <algorithm>
using namespace std;

int BinarySearch(int arr[], int s, int e, int value)
{
	if (s > e) return -1;
	else if (s == e)
	{
		if (value == arr[s]) return s;
		else return -1;
	}

	int mid = (s + e) / 2;
	if (arr[mid] == value) return mid;
	else if (arr[mid] > value) return BinarySearch(arr, s, mid - 1, value);
	else return BinarySearch(arr, mid + 1, e, value);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int N, M;

	cin >> N;
	int* sgCard = new int[N];
	for (int i = 0; i < N; ++i) cin >> sgCard[i];
	sort(sgCard, sgCard + N);

	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		int intCard;
		cin >> intCard;
		int check = BinarySearch(sgCard, 0, N - 1, intCard);

		if (check == -1) cout << "0 ";
		else cout << "1 ";
	}

	delete[] sgCard;
}