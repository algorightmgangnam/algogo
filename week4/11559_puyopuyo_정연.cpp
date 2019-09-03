#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct puyo {
	int x, y;		// ��ǥ
	char color;		// ��
};

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

char map[12][6];
// ���� �� �ѿ� �����ϴ� ����. 18�� ������ 12*6/4 = 18
vector<pair<int, int>> v[18];
// �ѹ��� �Ͷ߸�����.. vector num
int vnum = 0;
// �湮 Ȯ��
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

			// ������ ����, �湮���� �ʾҴٸ�
			if (map[nx][ny] == cc && !visited[nx][ny])
			{
				q.push({ nx, ny, map[nx][ny] });
				v[vnum].push_back({ nx, ny });
				visited[nx][ny] = true;
				cnt++;
			}
		}
	}

	// ���� ���� 4������ ������ ���� �ʱ�ȭ, ũ�� vnum ����
	if (cnt < 4) v[vnum].clear();
	else vnum++;
}

void solve()
{
	// �����ۿ� ����
	int explosion = 0;

	while (true)
	{
		memset(visited, false, sizeof(visited));
		vnum = 0;

		// 1. ������ �ѿ� 4�� �̻� ����Ǿ��ִ� �� ã�� --> BFS
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

		// vnum�� 0�̸� �Ͷ߸��� ���ٴ� ���̹Ƿ� while�� ����
		if (vnum == 0) break;

		// 2. �ѹ��� �Ͷ߸���
		for (int i = 0; i < vnum; ++i)
		{
			int size = v[i].size();

			for (int j = 0; j < size; ++j)
			{
				map[v[i][j].first][v[i][j].second] = '.';
			}

			v[i].clear();
		}

		// �����ۿ� ����
		explosion++;

		// 3. �߷� ���� �޾Ƽ� �������� �� �ٽ� �׸���
		for (int i = 0; i < 6; ++i)
		{
			int emptycnt = 0;	// ����� ī��Ʈ
			int stackcnt = 0;	// �عٴں��� ���� Ƚ�� ī��Ʈ
			vector<int> saveY;	// ������ �������� �ѿ�� �����ϴ� ���� 

			for (int j = 11; j >= 0; --j)
			{
				// �����
				if (map[j][i] == '.') emptycnt++;
				// �߷� �ۿ��� �ѿ�(�ؿ� ����� �ְ�, ���� ��ǥ�� ������� �ƴ϶��)
				else if (emptycnt != 0 && map[j][i] != '.') saveY.push_back(j);
				// �عٴڿ� �׿��ִ� �ѿ� ī��Ʈ
				else if (emptycnt == 0 && map[j][i] != '.') stackcnt++;
			}

			int size = saveY.size();
			for (int j = 0; j < size; ++j)
			{
				// ����������
				map[11 - stackcnt - j][i] = map[saveY[j]][i];
				map[saveY[j]][i] = '.';
			}
		}
	}

	cout << explosion;
}

int main(void)
{
	// �Է�
	for (int i = 0; i < 12; ++i) for (int j = 0; j < 6; ++j) cin >> map[i][j];

	solve();
}
