#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std; 
int N; 
int ar[16][16]; 
int ans = 0; 
bool visit[16][16]; 
int dr[] = {0, 1, 1}; // right, down, rightdown 
int dc[] = {1, 0, 1}; //   0,     1,     2
bool in_range(int row, int col)
{
    if(row>=0 and row<N and col>=0 and col<N) return true; 
    return false; 
}
void dfs(int type, int row, int col)
{
    if(visit[N-1][N-1]) 
    {
        ans++; return; 
    }
    if(type==1 || type==2 || type==3) // to diagonal 
    {
       
        int nr1 = row + dr[0], nc1 = col + dc[0]; 
        int nr2 = row + dr[1], nc2 = col + dc[1]; 
        int nr3 = row + dr[2], nc3 = col + dc[2]; 
        if(in_range(nr1, nc1) and in_range(nr2, nc2) and in_range(nr3,nc3))
        {
            if(!visit[nr1][nc1] && !visit[nr2][nc2] && !visit[nr3][nc3] && ar[nr1][nc1]==0 && ar[nr2][nc2]==0 && ar[nr3][nc3]==0 )
            {
                visit[nr1][nc1] = visit[nr2][nc2] = visit[nr3][nc3] = true; 
                dfs(3, nr3, nc3); 
                visit[nr1][nc1] = visit[nr2][nc2] = visit[nr3][nc3] = false; 
            }
        }
    }
    if(type==1 || type==3) // to horizontal 
    {
        int nr = row + dr[0], nc = col + dc[0]; 
        if(in_range(nr, nc) && !visit[nr][nc] and ar[nr][nc]==0)
        {
            visit[nr][nc]=true; 
            dfs(1, nr, nc); 
             visit[nr][nc]=false; 
        }
    }
    if(type==2 || type==3) // to vertical 
    {
        int nr = row + dr[1], nc = col + dc[1]; 
        if(in_range(nr, nc) && !visit[nr][nc] and ar[nr][nc]==0)
        {
            visit[nr][nc]=true; 
            dfs(2, nr, nc); 
             visit[nr][nc]=false; 
        }
    }
}
int main()
{
    cin>>N; 
    for(int i =0; i<N; i++)
    {
        for(int j =0; j<N; j++)
        {
            cin>>ar[i][j]; 
        }
    }
    
    visit[0][0]= visit[0][1] = true; 
    dfs(1, 0, 1); 
    cout<<ans<<'\n';
    
    
    
    return 0; 
}
