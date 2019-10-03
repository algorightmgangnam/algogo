#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int V, E;
int K;

int d[20001];
int INF = 11 * 200000;

struct cmp{
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.first > p2.first;
	}
};

int main() {
	cin >> V >> E;
	cin >> K;


	priority_queue<pair<int, int>, vector<pair<int,int>>, cmp> graph; // (가중치,(시작, 끝))
	vector <vector<pair<int, int>>> edges(20001);

	for (int i = 0; i < 20001; i++) {
		d[i] = INF;
	}
	d[K] = 0;


	
	int u, v, w;
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> w;

		edges[u].push_back(make_pair(w, v));

	}

	bool visited[20001] = { false, }	;
	graph.push(make_pair(0, K));
	//visited[0] = true;
	while(!graph.empty()) {
		w = graph.top().first;
		u = graph.top().second; //시작점

		graph.pop();

		if (!visited[u]) {
			visited[u];
			for (int j = 0; j < edges[u].size(); j++) {
				v = edges[u][j].second;
				w = edges[u][j].first;

				if (d[v] > w + d[u]) {
					d[v] = w + d[u];
					graph.push(make_pair(d[v], v));
				}
			}
		}
	}

	for (int i = 1; i <= V; i++) {
		if (d[i] == INF) cout << "INF\n";
		else cout << d[i] << "\n";
	}
}
