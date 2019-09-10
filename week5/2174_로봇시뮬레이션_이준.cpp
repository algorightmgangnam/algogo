
#include <iostream>
#include <vector>
#define E 1
#define S 2
#define W 3
#define N 4
using namespace std;

struct Node {
	int x, y, dir;
};
int A, B, n, m;
int map[102][102];
int dy[] = { 0,0,-1,0,1 };
int dx[] = { 0,1,0,-1,0 };

//1동 2남 3서 4북
int turn(int dir, int flag) {
	//왼쪽
	if (flag == 1) {
		return (dir == 1) ? 4 : dir - 1;
	}
	//오른쪽
	else {
		return (dir == 4) ? 1 : dir + 1;
	}
}

int main() {
	scanf("%d %d %d %d", &A, &B, &n, &m);

	//로봇을 집어넣을 벡터
	vector<Node> v(n + 1);
	for (int i = 1; i <= n; i++) {
		char c;
		scanf("%d %d %c", &v[i].x, &v[i].y, &c);
		if (c == 'W') v[i].dir = W;
		else if (c == 'N')v[i].dir = N;
		else if (c == 'E') v[i].dir = E;
		else v[i].dir = S;
		map[v[i].x][v[i].y] = i;
	}

	while (m--) {
		int x, y;
		char c;
		scanf("%d %c %d", &x, &c, &y);
		//직진 시키는 경우
		if (c == 'F') {
			for (int i = 0; i < y; i++) {
				int ax = v[x].x + dx[v[x].dir];
				int ay = v[x].y + dy[v[x].dir];
				// 다음 지점에 대해 타탕성 검증
				if (ax<1 || ay < 1 || ax > A || ay > B) {
					printf("Robot %d crashes into the wall\n", x);
					return 0;
				}
				else if (map[ax][ay] != 0) {
					printf("Robot %d crashes into robot %d\n", x, map[ax][ay]);
					return 0;
				}
				//타당하면 이동하기
				map[v[x].x][v[x].y] = 0;
				v[x].x = ax;
				v[x].y = ay;
				map[ax][ay] = x;
			}
		}
		//방향전환 하는 경우
		else {
			// 한방향으로 4번 돌면 같은방향
			if (y % 4 == 0) continue;
			y %= 4;
			while (y--) {
				if (c == 'L') {
					v[x].dir = turn(v[x].dir, 1);
				}
				else {
					v[x].dir = turn(v[x].dir, 0);
				}
			}
		}
	}
	printf("OK\n");

}
