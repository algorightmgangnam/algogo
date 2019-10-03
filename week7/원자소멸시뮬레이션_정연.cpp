#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 4001;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

struct Atom_Info {
	int x, y, dir, energy;
	bool isLive;
};

int MAP[MAX][MAX];
vector<Atom_Info> atom;

bool isAllDead()
{
	for (int i = 0; i < atom.size(); ++i) if (atom[i].isLive) return false;
	return true;
}

int Move()
{
	int total = 0;

	while (true)
	{
		int tmpEnergy = 0;
		if (isAllDead()) break;

		for (int i = 0; i < atom.size(); ++i)
		{
			if (!atom[i].isLive) continue;

			int x = atom[i].x;
			int y = atom[i].y;
			int dir = atom[i].dir;

			int nx = x + dx[dir];
			int ny = y + dy[dir];

			if (nx < 0 || ny < 0 || nx >= MAX || ny >= MAX)
			{
				atom[i].isLive = false;
				MAP[x][y] = 0;
			}
			else
			{
				MAP[x][y] = 0;
				MAP[nx][ny] += 1;
				atom[i].x = nx;
				atom[i].y = ny;
			}
		}

		for (int i = 0; i < atom.size(); ++i)
		{
			if (!atom[i].isLive) continue;

			int x = atom[i].x;
			int y = atom[i].y;

			if (MAP[x][y] >= 2)
			{
				for (int j = 0; j < atom.size(); ++j)
				{
					if (i == j) continue;
					if (!atom[j].isLive) continue;

					int tmpx = atom[j].x;
					int tmpy = atom[j].y;

					if (x == tmpx && y == tmpy)
					{
						tmpEnergy += atom[j].energy;
						atom[j].isLive = false;
					}
				}

				tmpEnergy += atom[i].energy;
				atom[i].isLive = false;
				MAP[x][y] = 0;
			}
		}

		total += tmpEnergy;
	}

	return total;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int tc;
	cin >> tc;

	for (int test_case = 1; test_case <= tc; ++test_case)
	{
		atom.clear();
		memset(MAP, 0, sizeof(MAP));

		int N;
		cin >> N;

		for (int i = 0; i < N; ++i)
		{
			int x, y, dir, k;
			cin >> x >> y >> dir >> k;

			x = (x + 1000) * 2;
			y = (y + 1000) * 2;

			atom.push_back({ x, y, dir, k, true });
			MAP[x][y] = 1;
		}

		cout << "#" << test_case << " " << Move() << "\n";
	}
}
