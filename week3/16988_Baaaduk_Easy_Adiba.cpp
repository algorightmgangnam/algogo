#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std; 
int N, M; 
const int MAX = 21; 
int input[MAX][MAX]; 
vector<pair<int, int> >candid, rival; 
int cnt; 
int ans; 
bool visit[MAX][MAX]; 
int dr[] = {1, -1, 0, 0}; 
int dc[] = {0, 0, 1, -1}; 
bool used[MAX][MAX]; 
int bfs(int row, int col)
{
    queue<pair<int,int> >q; 
    q.push(make_pair(row, col)); 
    visit[row][col]= true;
    int cnt = 1; 
    bool zero = false; 
    while(!q.empty())
    {
        int r = q.front().first; 
        int c = q.front().second; 
        q.pop(); 
        for(int i =0; i<4; i++)
        {
            int nr = r + dr[i]; 
            int nc = c + dc[i]; 
            if(nr<0 or nr>=N or nc<0 or nc>=M) continue; 
            if(visit[nr][nc]) continue; 
            if(input[nr][nc]==0) 
            {
              zero = true;    
            }
            if(input[nr][nc]==1) continue; 
            visit[nr][nc] = true; 
            q.push(make_pair(nr, nc)); 
            cnt++; 
        }
    }
    if(zero) return 0; 
    return cnt; 
}
int calc()
{
    int res =0; 
    memset(visit, false, sizeof(visit)); 
    for(int i =0; i<rival.size(); i++)
    {
        int row = rival[i].first; 
        int col = rival[i].second; 
        if(!visit[row][col])
        res+=bfs(row, col); 
        
    }
    return res; 
}

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    cin>>N>>M; 
    for(int i =0; i<N; i++)
    {
        for(int j =0; j<M; j++)
        {
            cin>>input[i][j]; 
            if(input[i][j]==2)
            {
                rival.push_back(make_pair(i, j)); 
            }
        }
    }
    
    
    
    for(int r =0; r<N; r++)
    {
        for(int c =0; c<M; c++)
        {
            if(input[r][c])
            {
                for(int i =0; i<4; i++)
                {
                    int nr = r + dr[i]; 
                    int nc = c + dc[i]; 
                    if(nr<0 or nr>=N or nc<0 or nc>=M) continue; 
                    if(input[nr][nc]==0 && !used[nr][nc])
                    {
                        used[nr][nc] = true; 
                        candid.push_back(make_pair(nr, nc)); 
                        cnt++; 
                    }
                }
            }
        }
    }
   
    for(int i =0; i<candid.size(); i++)
    {
        for(int j = i+1; j<candid.size(); j++)
        {
            int r1 = candid[i].first; 
            int c1 = candid[i].second; 
            int r2 = candid[j].first; 
            int c2 = candid[j].second; 
            input[r1][c1] = 1; 
            input[r2][c2] = 1; 
            ans = max(ans, calc()); 
            input[r1][c1] = 0; 
            input[r2][c2] = 0;
            
        }
    }
    
    cout<<ans<<'\n'; 
    
    return 0; 
}
