#include<iostream>
#include<vector>


using namespace std;

struct robot {
	int x, y;
	int state;
	bool crashed;
};

int map[101][101];

int A, B;
int N, M;

vector<robot> r;

int dx[4] = { 1, -1, 0,0 };//E,W,N,S
int dy[4] = { 0,0,1,-1 };
int cw[4] = { 3, 2, 0,  1}; 
int ccw[4] = {2, 3, 1, 0};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> A >> B;
	cin >> N >> M;

	int x, y, s;
	char tmp;

	r.push_back({ 0,0,0 });
	for(int i = 0;i<N;i++){
		cin >> x >> y>>tmp; //E,W,N, S - 0,1,2,3
		if (tmp == 'E') s = 0;
		else if (tmp == 'W') s = 1;
		else if (tmp == 'N') s = 2;
		else s = 3;

		r.push_back({x, y,s, false});
		map[y][x] = (i + 1);
	}

	int n, cnt;
	char action;
	for (int i = 0; i < M; i++) {
		cin >> n >> action >> cnt;

		robot *cur = &r.at(n);
		if (cur->crashed) continue;
		for (int j = 0; j < cnt; j++) {
			if (action == 'F') {
				map[cur->y][cur->x] = 0;
				cur->x = cur->x + dx[cur->state];
				cur->y = cur->y + dy[cur->state];

				if (map[cur->y][cur->x] != 0) {
					cout << "Robot "<<n<<" crashes into robot "<<map[cur->y][cur->x]<<"\n";
					cur->crashed = true;
					break;
				}

				else map[cur->y][cur->x] = n;

				if (cur->x == 0 || cur->y == 0 || cur->x > A || cur->y > B) {
					cout << "Robot "<< n <<" crashes into the wall\n";
					cur->crashed = true;
					break;
				}
			}
			else if (action == 'L') {
				cur->state = ccw[cur->state];
			}
			else {
				cur->state = cw[cur->state];
			}
		}
		if (cur->crashed) exit(0);
	}
	cout << "OK\n";


}
