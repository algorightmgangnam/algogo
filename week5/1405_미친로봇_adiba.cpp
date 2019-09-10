#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include<iomanip>
using namespace std;

int dr[] = {0, 0, 1, -1}; 
int dc[] = {1, -1, 0, 0};
double prob[4]; 
double ans; 
int N; 
const int MAX = 35; 
bool visit[MAX][MAX]; 
void dfs(int row, int col, double cur_prob)
{
    if(N==0)
    {
        ans+=cur_prob; 
        return; 
    }
   
    for(int i =0; i<4; i++)
    {
        int nr = row + dr[i]; 
        int nc = col + dc[i]; 
        if(visit[nr][nc]) continue; 
         visit[nr][nc] =true; 
        N--; 
        dfs(nr, nc, cur_prob * prob[i]); 
        N++; 
        visit[nr][nc] = false; 
    }
    
    
}

int main() 
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    cin>>N; 
    for(int i =0; i<4; i++) cin>>prob[i]; 
    for(int i =0; i<4; i++) prob[i]*=0.01; 
    visit[15][15] = true; 
    dfs(15, 15, 1); 
    cout << fixed; cout << setprecision(10) << ans << "\n";
    
    
  return 0;    
}
