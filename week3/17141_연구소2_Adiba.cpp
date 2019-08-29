#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std; 
int N, M; 
int lab[55][55]; 
bool visit[55][55]; 
int dr[] = {0, 0, -1, 1}; 
int dc[] = {1, -1, 0, 0}; 
struct virus{
   int row; 
   int col; 
   int num; 
   virus(int row, int col, int num):row(row), col(col), num(num){}
}; 
bool comp_by(virus a, virus b)
{
    return (a.num<b.num)?true:false; 
}
vector<virus>vir; 
bool used[12]; 
vector<virus> chosen;
int ans = -1; 

bool in_range(int row, int col)
{
    return (row>=0 and row<N and col>=0 and col<N)?true:false; 
}
bool okay(int arr[55][55])
{
  
    for(int i =0; i<N; i++)
    {
        for(int j =0; j<N; j++)
        {
            if(arr[i][j]==0 || arr[i][j]==2) return false; 
        }
    }
    return true; 
}
void solve(vector<virus>&chosen)
{
    int t = 0, temp =0;
    memset(visit, false, sizeof(visit)); 
    queue<pair<int,int> > q, nextq; 
    int cpylab[55][55]; 
    memcpy(cpylab, lab, sizeof(cpylab)); 
    
    for(int i =0; i<chosen.size(); i++)
    {
        int row = chosen[i].row; 
        int col = chosen[i].col; 
        q.push(make_pair(row, col)); 
        cpylab[row][col] = 5; 
        visit[row][col]=true; 
    }
    
    bool pass_to_act = false; 
    while(!q.empty())
    {
        int sz = q.size(); 
        bool change = false; 
        for(int times = 0; times<sz; times++)
        { 
           int row = q.front().first; 
           int col = q.front().second; 
           visit[row][col]=true; 
           q.pop(); 
           // check the value in lab 
               for(int i =0; i<4; i++)
               {
                   int nr = row + dr[i]; 
                   int nc = col + dc[i]; 
                   if(!in_range(nr, nc)) continue; 
                   if(visit[nr][nc]) continue; 
                   if(cpylab[nr][nc]==1 || cpylab[nr][nc]==5) continue; // wall 
                  
                   
                   
                  if(cpylab[nr][nc]==0 || cpylab[nr][nc]==2) {
                      // only if it changed some block
                     change = true; 
                      cpylab[nr][nc] = 3; 
                      visit[nr][nc]=true; 
                       q.push(make_pair(nr, nc)); 
                  }
                  
               }
        } 
        if(change) t++; 
        if(okay(cpylab))
        {
             if(ans==-1 or ans>t) ans = t; 
        }
        
    }
   
    
}
void go(int idx, int start)
{
    if(idx==M)
    {
        solve(chosen); 
        return; 
    }
    for(int i = start; i<vir.size(); i++)
    {
        virus cur(vir[i].row, vir[i].col, vir[i].num); 
        chosen.push_back(cur); 
        go(idx+1, i+1); 
        chosen.pop_back(); 
    }
}
int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    cin>>N>>M; 
    int idx = 1; 
    for(int i =0; i<N; i++)
    {
        for(int j =0; j<N; j++)
        {
            cin>>lab[i][j]; 
            if(lab[i][j]==2) 
            {
               // lab[i][j] = 3; 
               virus v(i, j, idx);  vir.push_back(v); 
               idx++; 
            }
        }
    }
    sort(vir.begin(), vir.end(),comp_by); 
    
    
    go(0, 0); 
    cout<<ans<<'\n'; 
    
    return 0; 
}
