#include    <cstdio>
#pragma warning (disable : 4996)
#define div 9901
int A[111111][4];
int main()
{
	int n;
	scanf("%d", &n);
	A[1][0] = 1; //00
	A[1][1] = 1; //01
	A[1][2] = 1; //10

	for (int i = 2; i <= n; ++i)
	{
		A[i][0] = (A[i - 1][0] + A[i - 1][1] + A[i - 1][2]) % div;
		A[i][1] = (A[i - 1][0] + A[i - 1][2]) % div;
		A[i][2] = (A[i - 1][0] + A[i - 1][1]) % div;
	}

	printf("%d", (A[n][0] + A[n][1] + A[n][2]) % div);


	return 0;
}
