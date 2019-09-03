#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct puyo {
	int x, y;		// 좌표
	char color;		// 색
};

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

char map[12][6];
// 같은 색 뿌요 저장하는 벡터. 18인 이유는 12*6/4 = 18
vector<pair<int, int>> v[18];
// 한번에 터뜨리려고.. vector num
int vnum = 0;
// 방문 확인
bool visited[12][6];

void FindPuyo(int x, int y, char color)
{
	queue<puyo> q;
	int cnt = 1;

	q.push({ x, y, color });
	v[vnum].push_back({ x, y });
	visited[x][y] = true;

	while (!q.empty())
	{
		int cx = q.front().x;
		int cy = q.front().y;
		char cc = q.front().color;
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= 12 || ny >= 6) continue;

			// 색깔이 같고, 방문하지 않았다면
			if (map[nx][ny] == cc && !visited[nx][ny])
			{
				q.push({ nx, ny, map[nx][ny] });
				v[vnum].push_back({ nx, ny });
				visited[nx][ny] = true;
				cnt++;
			}
		}
	}

	// 같은 색이 4개보다 작으면 벡터 초기화, 크면 vnum 증가
	if (cnt < 4) v[vnum].clear();
	else vnum++;
}

void solve()
{
	// 연쇄작용 변수
	int explosion = 0;

	while (true)
	{
		memset(visited, false, sizeof(visited));
		vnum = 0;

		// 1. 같은색 뿌요 4개 이상 연결되어있는 것 찾기 --> BFS
		for (int i = 0; i < 12; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if (map[i][j] != '.')
				{
					FindPuyo(i, j, map[i][j]);
				}
			}
		}

		// vnum이 0이면 터뜨릴게 없다는 뜻이므로 while문 종료
		if (vnum == 0) break;

		// 2. 한번에 터뜨리기
		for (int i = 0; i < vnum; ++i)
		{
			int size = v[i].size();

			for (int j = 0; j < size; ++j)
			{
				map[v[i][j].first][v[i][j].second] = '.';
			}

			v[i].clear();
		}

		// 연쇄작용 증가
		explosion++;

		// 3. 중력 영향 받아서 내려오고 맵 다시 그리기
		for (int i = 0; i < 6; ++i)
		{
			int emptycnt = 0;	// 빈공간 카운트
			int stackcnt = 0;	// 밑바닥부터 쌓인 횟수 카운트
			vector<int> saveY;	// 밑으로 내려보낼 뿌요들 저장하는 벡터 

			for (int j = 11; j >= 0; --j)
			{
				// 빈공간
				if (map[j][i] == '.') emptycnt++;
				// 중력 작용할 뿌요(밑에 빈공간 있고, 현재 좌표가 빈공간이 아니라면)
				else if (emptycnt != 0 && map[j][i] != '.') saveY.push_back(j);
				// 밑바닥에 쌓여있는 뿌요 카운트
				else if (emptycnt == 0 && map[j][i] != '.') stackcnt++;
			}

			int size = saveY.size();
			for (int j = 0; j < size; ++j)
			{
				// 내려보내기
				map[11 - stackcnt - j][i] = map[saveY[j]][i];
				map[saveY[j]][i] = '.';
			}
		}
	}

	cout << explosion;
}

int main(void)
{
	// 입력
	for (int i = 0; i < 12; ++i) for (int j = 0; j < 6; ++j) cin >> map[i][j];

	solve();
}
