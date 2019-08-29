#include <iostream> //4:00~5:02
#include <vector>
#include <queue>

using namespace std;

int N, M, emptySpace=0;
int map[50][50], ans = 987654321;
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
vector <pair<int, int> > v;
vector <int> chosen;

int Spread(){
	queue <pair<int,int> > q;
	int cmap[50][50];
	bool visited[50][50] = { 0 };
	int virusSpace = 0;
	for (int i = 0; i < chosen.size(); i++){
		visited[v[chosen[i]].first][v[chosen[i]].second] = true;
		virusSpace++;
		q.push({ v[chosen[i]].first, v[chosen[i]].second });
	}
	//맵복사
	for (int i = 0; i < N; i++)for (int j = 0; j < N; j++){
		cmap[i][j] = map[i][j];
	}
	int time = 0;
	while (!q.empty()){
		if (emptySpace == virusSpace) return time;
		time++;
		int qSize = q.size();
		while (qSize--){
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			for (int i = 0; i < 4; i++){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N || cmap[nx][ny] == 1 || visited[nx][ny]) continue;
				visited[nx][ny] = true;
				//cmap[nx][ny] = 2;
				virusSpace++;
				q.push({ nx, ny });
			}
			
			//시간초과
			/*
			int cntEmpty = 0;
			for (int i = 0; i < N; i++)for (int j = 0; j < N; j++){
				if (cmap[i][j] == 1) continue;
				if (!visited[i][j]) cntEmpty++;
			}
			if (cntEmpty == 0){
				return time;
			}
			*/
		}
		
	}
	return 987654321;
}
void Choose(int index){
	if (chosen.size() == M){
		//바이러스 퍼뜨리기
		int res = Spread();
		if (ans>res) ans=res;
		return;
	}
	if (index == v.size()){
		return;
	}
	chosen.push_back(index);
	Choose(index + 1);
	chosen.pop_back();
	Choose(index + 1);
}
int main(){
	cin >> N >> M;
	for (int i = 0; i < N; i++)for (int j = 0; j < N; j++){
		cin >> map[i][j];
		if (map[i][j] == 2)
			v.push_back({ i, j });
		if (map[i][j] != 1) emptySpace++;
	}
	
	Choose(0);
	if (ans == 987654321){
		cout << -1;
	}
	else{
		cout << ans;
	}
	return 0;
}