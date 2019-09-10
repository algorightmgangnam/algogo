#include<iostream>
using namespace std;
const int roff[4] = { 0, 0, 1, -1 };
const int coff[4] = { 1, -1, 0, 0 };

double P[4];
bool visited[29][29];

// 현재 r행 c열에 있고 limit번 더 이동할 때 앞으로 단순경로일 확률
double crazyRobot(int r, int c, int limit) {
	// 기저 사례: 당장 탐색을 멈추므로 항상 단순하다.
	if (limit == 0) return 1.0;

	visited[r][c] = true;
	double result = 0.0;
	// DFS로 다른 방향들을 탐색하여 결과를 구함
	for (int d = 0; d<4; d++) {
		int nr = r + roff[d];
		int nc = c + coff[d];
		if (visited[nr][nc]) continue;
		// 해당 방향으로 이동할 확률을 곱해서 결과에 더함
		result += P[d] * crazyRobot(nr, nc, limit - 1);
	}
	visited[r][c] = false;
	return result;
}

int main() {
	int N;
	cin >> N;
	for (int i = 0; i<4; i++) {
		int p;
		cin >> p;
		P[i] = p / 100.0;
	}
	// N이 최대 14이므로 0~28까지의 행, 열 번호를 쓰며 중앙은 14
	printf("%.10lf\n", crazyRobot(14, 14, N));
}
