#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
#define MAX 200
vector<int> adjList[MAX]; 
bool visit[MAX]; 
void dfs(int node, int n )
{
    visit[node] = true;  
    for(int i =0; i<adjList[node].size(); i++)
    {
        int nextnode = adjList[node][i]; 
        if(nextnode!=node and !visit[nextnode]) dfs(nextnode, n); 
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<computers[i].size(); j++)
        {
           if(computers[i][j]) // connection
           {
               adjList[i].push_back(j); 
           }
        }
    }
    int cnt = 0; 
    for(int i =0; i<n; i++)
    {
        if(!visit[i])
        {
            dfs(i, n); cnt++; 
        }
    }
    answer = cnt; 
    return answer;
}
