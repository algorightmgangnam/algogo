#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

int dr[] = {0, 0, 1, -1}; // E, W, S, N
int dc[] = {1, -1, 0, 0};
int R, C, M, N; // robot num: N, command num: M
const int X = 110; 
int board[X][X]; 
struct rbt
{
    int row; 
    int col; 
    int dir; 
    rbt():row(-1), col(-1), dir(-1){}
    rbt(int row, int col, int dir):row(row), col(col), dir(dir){}
}; 
rbt robots[X]; 
int left(int cur)
{
    if(cur==0) return 3; 
    else if(cur==1) return 2; 
    else if(cur==2) return 0; 
    else  return 1; 
}
int right (int cur)
{
    if(cur==0) return 2; 
    else if(cur==1) return 3; 
    else if(cur==2) return 1; 
    else return 0; 
}
int main() 
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    cin>>C>>R; 
    cin>>N>>M;
    int x, y, row, col, dir; char dir_char; 
    int idx  =1; 
    for(int i = 1; i<=N; i++)
    {
        cin>>x>>y>>dir_char; 
        col = x, row = (R+1)-y; 
        if(dir_char=='E') dir = 0; 
        else if(dir_char=='W') dir = 1; 
        else if(dir_char =='S') dir = 2; 
        else if(dir_char =='N') dir = 3; 
        board[row][col] = idx;
        robots[idx] = rbt(row, col, dir); 
        idx++; 
    }
    int rnum, times; 
    char cmd; 
    bool fail = false; 
    for(int i = 0; i<M; i++)
    {
        cin>>rnum>>cmd>>times; 
        
        int cur_row = robots[rnum].row; 
        int cur_col = robots[rnum].col;
        int cur_dir = robots[rnum].dir; 
        if(times>0) board[cur_row][cur_col] = 0;
        int nr = cur_row, nc = cur_col, nd  = cur_dir; 
        for(int t = 0; t<times; t++)
        {
            if(cmd=='F')
            {
                nr+=dr[nd]; nc+=dc[nd]; 
            }
            else if(cmd=='L')
            {
                nd = left(nd); 
                //nr+=dr[nd], nc+=dc[nd]; 
            }
            else if(cmd=='R')
            {
                nd = right(nd); 
               // nr+=dr[nd], nc+=dc[nd]; 
            }
            if(nr<=0 or nc<=0 or nr>R or nc>C)
            {
                fail = true; 
                cout<<"Robot "<<rnum<<" crashes into the wall"; 
                break; 
            }
            else if(board[nr][nc]>0)
            {
                fail = true; 
                cout<<"Robot "<<rnum<<" crashes into robot " << board[nr][nc]; 
                break; 
            }
            
        }
        board[nr][nc] = rnum; 
        robots[rnum].row = nr, robots[rnum].col = nc, robots[rnum].dir = nd; 
        if(fail) break; 
    }
    if(!fail)
    {
        cout<<"OK"; 
    }
    
  return 0;    
}
