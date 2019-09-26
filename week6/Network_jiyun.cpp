#include <string>
#include <vector>
#include <queue>
#include<iostream>

using namespace std;

bool visited[200] = {false,};

void bfs(int start, vector<vector<int>> computers, int n) {
	queue<int> q;

	q.push(start);
    visited[start] = true;
	int cur;

	while (!q.empty()) {
		cur = q.front();
		q.pop();
        cout<<cur<<n<<" ";
		for (int i = 0; i < n; i++) {
			cout<<"a";
            if (cur != i && !visited[i]) {
               
				if (computers.at(cur).at(i) == 1) {
					visited[i] = true;
					q.push(i);
				}
			}

		}
	}
}

int solution(int n, vector<vector<int>> computers) {
	int answer = 0;
	
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
            cout<<i<< " ";
			bfs(i, computers,n);
			answer++;
            cout<<endl;
		}
	}

	return answer;
}
