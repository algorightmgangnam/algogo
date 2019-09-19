#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000;

struct Edge {
	int u, v;
	double cost;
};

pair<double, double> island[1000];
int group[1000];
double E;

int Find(int x)
{
	if (x == group[x]) return x;
	return group[x] = Find(group[x]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return;

	group[b] = a;
}

int compare_dist(const Edge& a, const Edge& b)
{
	return a.cost < b.cost;
}

double Kruskal(vector<Edge>& edge)
{
	double answer = 0;

	// 가중치에 따라 오름차순 정렬
	sort(edge.begin(), edge.end(), compare_dist);

	for (int i = 0; i < edge.size(); ++i)
	{
		// 사이클이 존재하면 continue
		if (Find(edge[i].u) == Find(edge[i].v)) continue;

		answer += edge[i].cost;
		Union(edge[i].u, edge[i].v);
	}

	return E * answer;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cout << fixed;
	cout.precision(0);

	int tc;
	cin >> tc;

	for (int test_case = 1; test_case <= tc; ++test_case)
	{
		int N;
		cin >> N;

		for (int i = 0; i < N; ++i)
		{
			cin >> island[i].first;
			group[i] = i;			// Make-Set
		}	
		for (int i = 0; i < N; ++i) cin >> island[i].second;

		cin >> E;

		vector<Edge> edge;

		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				// cost(환경 부담금) = E * L^2 ==> sqrt 사용할 필요 없음
				edge.push_back({ i, j, pow(island[i].first - island[j].first, 2) + pow(island[i].second - island[j].second, 2) });
			}
		}

		cout << "#" << test_case << " " << Kruskal(edge) << "\n";
	}
}
