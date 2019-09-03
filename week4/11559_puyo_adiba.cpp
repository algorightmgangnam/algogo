#include<iostream> // chessboard 15:21~
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<stack>
using namespace std; 

int dr[] = {1, -1, 0, 0}; 
int dc[] = {0, 0, 1, -1}; 
const int N = 12, M = 6; 
string input[N]; 
bool visit[N][M]; 
bool crash; 
int ans; 
vector<pair<int,int> >puyo; 

void bfs(int row, int col)
{ 
    visit[row][col] = true; 
    queue<pair<int, int> >q; 
    char color = input[row][col]; 
    q.push(make_pair(row, col)); 
    vector<pair<int,int> >same_color; 
    same_color.push_back(make_pair(row, col));
    
    while(!q.empty())
    {
        int r = q.front().first; 
        int c = q.front().second; 
        q.pop(); 
        
        for(int i=0; i<4; i++)
        {
            int nr = r + dr[i]; 
            int nc = c + dc[i]; 
            if(nr<0 or nr>=N or nc<0 or nc>=M) continue; 
            if(visit[nr][nc]) continue; 
            if(input[nr][nc]=='.' or input[nr][nc]!=color) continue; 
            visit[nr][nc] = true; 
            q.push(make_pair(nr, nc)); 
            same_color.push_back(make_pair(nr, nc)); 
        } 
    }
    if(same_color.size()>=4)
    {
        for(int i =0; i<same_color.size(); i++)
        {
            input[same_color[i].first][same_color[i].second] = '.'; 
        }
        crash = true; 
    }
    
}
void gravity()
{
    for(int i =0; i<puyo.size(); i++)
    {
        int r = puyo[i].first; 
        int c = puyo[i].second; 
        if(input[r][c]=='.') continue; 
        else if(r==N-1) continue; 
        else
        {
            stack<char>st; 
            for(int row = r; row<N; row++)
            {
                if(input[row][c]!='.')
                {
                    st.push(input[row][c]); 
                    input[row][c]='.'; 
                }
            }
            int ntemp = N-1; 
            while(!st.empty())
            {
                char cur = st.top(); st.pop(); 
                input[ntemp--][c] = cur; 
            }
        }
    }
}
void solve()
{
    int rnd = 0; 
    while(1)
    {
        rnd++; 
        // 1. put alive puyos into puyo vector 
        for(int i =0; i<N; i++)
        {
            for(int j =0; j<M; j++)
            {
                if(input[i][j]!='.')
                {
                    puyo.push_back(make_pair(i, j)); 
                }
            }
        }
        
        memset(visit, false, sizeof(visit));
        //2. bfs
        crash = false;  
        for(int i =0; i<puyo.size(); i++)
        {
            int row = puyo[i].first; 
            int col = puyo[i].second;
            if(!visit[row][col]) bfs(row, col); 
        }
        if(crash)
        {
            ans++; 
            // go down
            gravity();  
            puyo.clear(); 
        }
        else
        {
            break; 
        }
        
    }
}
int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    
    for(int i =0; i<N; i++) cin>>input[i]; 
    solve(); 
    cout<<ans<<'\n'; 
    return 0; 
}
