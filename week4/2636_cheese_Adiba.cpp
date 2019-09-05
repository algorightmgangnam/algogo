#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int MAX = 100; 
int a[MAX][MAX]; 
int R, C; 
int last_cnt, ans; 
enum{CHEESE =1, PREAIR, AIR}; 
bool visit[MAX][MAX]; 
int dr[] = {1, -1, 0, 0}; 
int dc[] = {0, 0, 1, -1}; 
queue<pair<int, int> >cheese_info; 

bool inRange(int row, int col)
{
    return (row>=0 and row<R and col>=0 and col<C)?true:false; 
}
void findOutAir()
{
    memset(visit, false, sizeof(visit)); 
    queue<pair<int ,int> >q; 
    q.push({0, 0}); // no cheese in borders
    visit[0][0] = true; 
    while(!q.empty())
    {
        int r = q.front().first; 
        int c = q.front().second; 
        q.pop(); 
        for(int i =0; i<4; i++)
        {
            int nr = r + dr[i]; 
            int nc = c + dc[i]; 
            if(!inRange(nr, nc) || visit[nr][nc]) continue; 
            // if original input or already air
            // or when changing inner air to outer air
            if(a[nr][nc]==0 or a[nr][nc]==AIR)
            {
                a[nr][nc]  = AIR; 
                visit[nr][nc] = true; 
                q.push({nr, nc}); 
            }
        }
    }
}

void preairToAir()
{
    for(int i =0; i<R; i++)
    {
        for(int j =0; j<C; j++)
        {
            if(a[i][j]==PREAIR) a[i][j] = AIR; 
        }
    }
}

void meltCheese()
{
    int sz = cheese_info.size(); 
    for(int i =0; i<sz; i++)
    {
        int r = cheese_info.front().first; 
        int c = cheese_info.front().second; 
        cheese_info.pop(); 
        bool adjacent_to_air = false; 
        for(int d =0; d<4; d++)
        {
            int nr = r + dr[d]; 
            int nc = c + dc[d]; 
            if(!inRange(nr, nc)) continue; 
            if(a[nr][nc]==AIR)
            {
                adjacent_to_air = true; 
            }
        }
        if(adjacent_to_air)
        {
            a[r][c] = PREAIR; 
        }
        else
        {
            cheese_info.push({r, c}); 
        }
    }
    
}

void solve()
{
    int t = 0; 
    
    while(1)
    {
        t++; 
        findOutAir();
        last_cnt = cheese_info.size(); 
        meltCheese();
        preairToAir(); 
        if(cheese_info.empty())
        {
            ans = t; break; 
        }

    }
}

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    
    cin>>R>>C; 
    for(int i=0; i<R; i++)
    {
        for(int j =0; j<C; j++)
        {
            cin>>a[i][j]; 
            if(a[i][j]) cheese_info.push({i, j}); 
        }
    }
    solve(); 
    cout<<ans<<'\n'<<last_cnt<<'\n'; 
    return 0; 
}
