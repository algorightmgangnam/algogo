#include<iostream> // chessboard 15:21~
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std; 

int dr[] = {1, -1, 0, 0}; 
int dc[] = {0, 0, 1, -1}; 

int N, M; 
int input[51][51]; // White: 0, Black: 1
int ans = 1e9; // we need min 
bool visit[51][51]; 
struct block
{
    int row; 
    int col; 
    int color; 
    block():row(0), col(0), color(0){}
    block(int row, int col, int color):row(row), col(col), color(color){}
}; 
bool in_range(int row, int col, int R_begin, int C_begin)
{
    return (row>=R_begin and row<R_begin+8 and col>=C_begin and col<C_begin+8)?true:false; 
}
void simulate(int row, int col, int color)
{
   queue<block>q; 
   int cnt = 0; 
   memset(visit, false, sizeof(visit)); 
   if(input[row][col]!=color) cnt++; 
   q.push(block(row, col, color)); 
   visit[row][col]= true; 
   
   while(!q.empty())
   {
       int r = q.front().row; 
       int c = q.front().col; 
       int clr = q.front().color; 
       //cout<<"cur color: "<<clr<<",   "; 
       q.pop(); 
       for(int i =0; i<4; i++)
       {
           int nr = r + dr[i]; 
           int nc = c + dc[i]; 
           
           if(!in_range(nr, nc, row, col)) continue;
           if(visit[nr][nc]) continue; 
           int nclr = input[nr][nc]; 
           visit[nr][nc] = true; 
           if(nclr==clr)
           {
               cnt++; 
               nclr = !nclr;  
           }
           q.push(block(nr, nc, nclr)); 
       }
   }
    ans = min(ans, cnt); 
}
void solve()
{
    for(int row =0; row<=N-8; row++)
    {
        for(int col =0; col<=M-8; col++)
        {
            for(int color = 0; color<=1; color++)
            {
                simulate(row, col, color); 
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    cin>>N>>M; 
    char temp; 
    for(int i =0; i<N; i++)
    {
        for(int j =0; j<M; j++)
        {
            cin>>temp; 
            if(temp=='B') input[i][j]=1; 
        }
    }
    solve();  
    cout<<ans<<'\n'; 
    
    return 0; 
}
