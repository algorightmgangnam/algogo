#include <iostream>
#include <stack>
#include <cstring>
#define MIN(a, b) (a < b) ? a : b
using namespace std;

// 메모리 크기, 프로그램 코드 크기, 입력 크기
int sm, sc, si;
// 명령어 수행횟수, 포인터 위치, 프로그램 입력 인덱스, 프로그램 코드 인덱스
int cnt, pointer, si_idx, sc_idx;
// 무한루프 지점
int looppos;

int command(char c, char *Data, char *input)
{
	// modulo 2^8
	if (c == '-')
	{
		Data[pointer] = (Data[pointer] - 1 + 256) % 256;
		sc_idx++;
	}
	else if (c == '+')
	{
		Data[pointer] = (Data[pointer] + 1) % 256;
		sc_idx++;
	}
	// 포인터를 움직이는데, 배열 범위 넘어가면 반대쪽으로 넘어감
	else if (c == '<')
	{
		pointer = (pointer - 1 + sm) % sm;
		sc_idx++;
	}
	else if (c == '>')
	{
		pointer = (pointer + 1) % sm;
		sc_idx++;
	}
	// loop
	else if (c == '[')
	{
		// 명령어 수행 횟수 넘어가면 3 return
		if (cnt >= 50000000 * 2) return 3;
		// 명령어 수행 횟수 넘어가면 무한루프 지점 저장
		else if (cnt >= 50000000) looppos = MIN(sc_idx, looppos);

		// ]로 점프 -> 1 return
		if (Data[pointer] == 0) return 1;
		else sc_idx++;
	}
	else if (c == ']')
	{
		// [로 점프 -> 2 return
		if (Data[pointer] != 0) return 2;
		else sc_idx++;
	}
	else if (c == '.') sc_idx++;
	else if (c == ',')
	{
		// 문자 하나를 읽고 포인터가 가리키는 곳에 저장
		Data[pointer] = input[si_idx];
		if (si_idx < si) si_idx++;
		sc_idx++;
	}

	return 0;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int tc;
	cin >> tc;

	for (int test_case = 0; test_case < tc; ++test_case)
	{
		// brainfuck 프로그램, 프로그램 입력, 데이터 배열
		char code[4096], input[4097], Data[100000] = { 0, };
		// loop 저장 스택
		stack<int> loop;
		// loop pair 배열
		int looppair[4096] = { 0, };

		cin >> sm >> sc >> si >> code >> input;
		input[si] = 255;		// EOF == 255

		cnt = 0, pointer = 0, si_idx = 0, sc_idx = 0;

		// loop 저장. 프로그램 코드 크기만큼 반복하면서 loop를 찾아낸다.
		for (int i = 0; i < sc; ++i)
		{
			if (code[i] == '[') loop.push(i);
			else if (code[i] == ']')
			{
				looppair[i] = loop.top();
				looppair[loop.top()] = i;
				loop.pop();
			}
		}

		bool isInfLoop = false;	// 무한루프인지
		looppos = sc + 1;

		// 프로그램 코드 인덱스가 프로그램 코드 크기보다 작으면 반복
		while (sc_idx < sc)
		{
			// 명령어 수행
			int result = command(code[sc_idx], Data, input);

			// [
			if (result == 1) sc_idx = looppair[sc_idx] + 1;
			// ]
			else if (result == 2) sc_idx = looppair[sc_idx];
			// 무한 루프
			else if (result == 3)
			{
				isInfLoop = true;
				break;
			}

			cnt++;
		}

		if (isInfLoop) cout << "Loops " << looppos << " " << looppair[looppos] << "\n";
		else cout << "Terminates\n";
	}
}
