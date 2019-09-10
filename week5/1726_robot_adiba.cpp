#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
int sr, sc, sd, er, ec, ed; 

int dr[] = {0, 0, 0, 1, -1}; 
int dc[] = {0, 1, -1, 0, 0};
const int MAX_N = 102; 
int board[MAX_N][MAX_N]; 
bool visit[MAX_N][MAX_N][5]; 
int R, C; 

struct state
{
    int row; 
    int col; 
    int dir; 
    int cmd; // command cnt 
    state(int row, int col, int dir, int cmd):row(row), col(col), dir(dir), cmd(cmd){}
}; 
bool in_range(int row, int col)
{
    return (row>=1 and row<=R and col>=1 and col<=C)?true:false; 
}
pair<int, int> next_rot(int cur)
{
    return (cur<3)?make_pair(3, 4):make_pair(1,2); 
}

void solve()
{
    visit[sr][sc][sd] = true; 
    queue<state>q; 
    q.push(state(sr, sc, sd, 0)); 
    while(!q.empty())
    {
        int row = q.front().row; 
        int col = q.front().col; 
        int dir = q.front().dir; 
        
        int cmd = q.front().cmd; 
        //cout<<"row: "<<row<<", col: "<<col<<", dir: "<<dir<<" , cmd: "<<cmd<<endl; 
        q.pop(); 
        if(row==er and col ==ec and dir == ed)
        {
            cout<<cmd<<'\n'; 
            return; 
        }
        // other cases to consider: 1) 90 deg. turn right, 2) 90 deg. turn left
        //                          3) go 1 step in same dir. 4) go 2 steps in same dir.
        //                          5) go 3 steps in same same dir.
        
        pair<int, int> ndirs = next_rot(dir); 
        if(!visit[row][col][ndirs.first]) 
        {
            visit[row][col][ndirs.first] = true; 
            q.push(state(row, col, ndirs.first, cmd+1)); 
        }
        if(!visit[row][col][ndirs.second])
        {
            visit[row][col][ndirs.second] = true; 
            q.push(state(row, col, ndirs.second, cmd+1)); 
        }
        
        for(int k = 1; k<=3; k++)
        {
            int nr = row + dr[dir]*k; 
            int nc = col + dc[dir]*k; 
            if(!in_range(nr, nc)) break; 
            if(board[nr][nc]) break;
            if(visit[nr][nc][dir]) continue; 
            visit[nr][nc][dir] = true; 
            q.push(state(nr, nc, dir, cmd+1)); 
        }
        
    }
    
    
}
int main() 
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    
    cin>>R>>C; 
    for(int i =1; i<=R; i++) for(int j =1; j<=C; j++) cin>>board[i][j]; 
    cin>>sr>>sc>>sd>>er>>ec>>ed; 
    solve(); 
    
  return 0;    
}
