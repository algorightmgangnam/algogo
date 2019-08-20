#include <iostream>
#include <climits>
using namespace std;

int N;
int operands[10];
char operators[9];
int operandsCnt, operatorsCnt;

long long answer = -LLONG_MAX;

long long Calculate(long long a, long long b, char op)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	}
}

void DFS(long long result, int operatorIdx)
{
	int nResult = 0, cResult = 0;

	if (operatorIdx >= operatorsCnt)
	{
		if (answer < result) answer = result;
		return;
	}

	cResult = Calculate(result, operands[operatorIdx + 1], operators[operatorIdx]);
	DFS(cResult, operatorIdx + 1);

	if (operatorIdx + 2 < operandsCnt)
	{
		nResult = Calculate(operands[operatorIdx + 1], operands[operatorIdx + 2], operators[operatorIdx + 1]);
		cResult = Calculate(result, nResult, operators[operatorIdx]);
		DFS(cResult, operatorIdx + 2);
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		char numStn;
		cin >> numStn;

		if (i % 2 == 0) operands[operandsCnt++] = numStn - '0';
		else operators[operatorsCnt++] = numStn;
	}

	DFS(operands[0], 0);

	cout << answer;
}