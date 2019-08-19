#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std; 
#define MAX 100
int dr[] = {0, 0, -1, 1}; 
int dc[] = {1, -1, 0, 0}; 
int N; 
int H; 
int ans; 
bool visit[MAX][MAX]; 
int land[MAX][MAX]; 

void dfs(int row, int col)
{
    visit[row][col] = true; 
    for(int i =0; i<4; i++)
    {
        int nr = row + dr[i]; 
        int nc = col + dc[i]; 
        if(nr<0 or nr>=N or nc<0 or nc>=N) continue; 
        if(visit[nr][nc]) continue; 
        dfs(nr, nc); 
    }
}
void solve()
{
    for(int height = 0; height<H; height++) // height==0: when no rain
    {
        int cnt = 0; 
        memset(visit, false, sizeof(visit)); 
        for(int i =0; i<N; i++)
        {
            for(int j =0; j<N; j++)
            {
                if(land[i][j]<=height)
                {
                    visit[i][j]=true; 
                }
            }
        }
        
        for(int i =0; i<N; i++)
        {
            for(int j =0; j<N; j++)
            {
                if(visit[i][j]) continue; 
                dfs(i, j);
                cnt++; 
            }
        }
        ans = max(ans, cnt); 
    }
    
   
}
int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    cin>>N; 
    for(int i=0; i<N; i++)
    {
        for(int j =0; j<N; j++)
        {
            cin>>land[i][j]; 
            H = max(H, land[i][j]); // update max height
        }
    }
    solve(); 
     cout<<ans<<'\n'; 
    
    return 0; 
}
