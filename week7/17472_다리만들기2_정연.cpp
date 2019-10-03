#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 다리 구조체
// 출발섬 번호, 도착섬 번호, 거리
struct Bridge {
	int u, v, dist;
};

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int N, M;
int Map[10][10];

vector<pair<int, int>> island[7];		// 섬 좌표 저장 벡터
vector<pair<int, int>> islandEdge[7];	// 섬 가장자리 좌표 저장 벡터
bool visited[10][10];

vector<Bridge> br;							// 다리 벡터
int group[7] = { 0, 1, 2, 3, 4, 5, 6 };		// Union-Find -- Make-Set

bool isRange(int x, int y)
{
	if (x < 0 || y < 0 || y >= M || x >= N) return false;
	return true;
}

void FindIsland(int x, int y, int num)
{
	bool isBr = false;	// 섬의 가장자리를 찾기 위한 boolean형 변수
	Map[x][y] = num;	// 섬을 번호에 맞게 바꾼다.

	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		// 범위가 아니고, 이미 방문했다면 continue
		if (!isRange(nx, ny)) continue;
		if (visited[nx][ny]) continue;
		// 주변이 물이면 가장자리이므로 true. 그리고 섬이 아니니까 continue
		if (Map[nx][ny] != 1)
		{
			isBr = true;
			continue;
		}

		visited[nx][ny] = true;
		island[num].push_back({ nx, ny });
		FindIsland(nx, ny, num);
	}

	// 가장자리면 push_back
	if (isBr) islandEdge[num].push_back({ x, y });
}

void MakeBridge(int x, int y)
{
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		int len = 0;	// 길이
		int dest = 0;	// 도착한 섬의 번호

		// 범위를 벗어나지 않고, 바다면 계속 뻗어나감
		while (isRange(nx, ny) && Map[nx][ny] == 0)
		{
			nx += dx[i];
			ny += dy[i];
			len++;
		}

		// 범위를 벗어나지 않았는데 while문을 빠져 나오면 섬을 만난거니까 dest에 섬 번호를 넣어준다.
		if (isRange(nx, ny)) dest = Map[nx][ny];
		// 다리의 길이가 2 이상이고 dest가 0이 아니면 다리 벡터에 출발섬, 도착섬 번호와 다리의 길이를 넣어준다.
		if (len >= 2 && dest) br.push_back({ Map[x][y], dest, len });
	}
}

int FindSet(int x)
{
	if (x == group[x]) return x;
	return group[x] = FindSet(group[x]);
}

void UnionSet(int a, int b)
{
	a = FindSet(a);
	b = FindSet(b);

	// 부모가 같으면 return
	if (a == b) return;

	// a, b의 각 집합을 합침
	group[b] = a;
}

int compare_dist(const Bridge& a, const Bridge& b)
{
	return a.dist < b.dist;
}

int Kruskal()
{
	int answer = 0;

	// 다리의 길이를 오름차순으로 정렬
	sort(br.begin(), br.end(), compare_dist);

	for (int i = 0; i < br.size(); ++i)
	{
		// 부모 노드가 같으면 continue
		if (FindSet(br[i].u) == FindSet(br[i].v)) continue;

		answer += br[i].dist;
		UnionSet(br[i].u, br[i].v);
	}

	return answer;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> Map[i][j];

	// 1. DFS로 연결된 섬을 찾는다.
	int num = 0;	// 섬 번호
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (!visited[i][j] && Map[i][j] == 1)
			{
				num++;
				FindIsland(i, j, num);
			}
		}
	}

	// 2. 다리를 만들어준다.
	for (int i = 1; i <= num; ++i)
	{
		for (int j = 0; j < islandEdge[i].size(); ++j)
		{
			MakeBridge(islandEdge[i][j].first, islandEdge[i][j].second);
		}
	}

	// 3. MST로 최소 거리를 찾는다. (크루스칼 사용)
	int answer = Kruskal();

	// 4. 모든 섬을 다 돌았는지 확인한다.
	int uf_first = FindSet(1);
	for (int i = 2; i <= num; ++i) if (uf_first != FindSet(i)) answer = 0;

	if (answer == 0) cout << "-1";
	else cout << answer;
}
