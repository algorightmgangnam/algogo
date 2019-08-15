#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std; 
#define MAX 1500
bool water_check[MAX][MAX]; // for water bfs
bool swan_check[MAX][MAX]; // for swan bfs
string inp[MAX]; 
int R, C; 
int dr[] = {1, -1, 0, 0}; 
int dc[] = {0, 0, 1, -1}; 

pair<int,int>swan1, swan2; 
int main()
{
    swan1.first = swan1.second = -1; 
    swan2.first = swan2.second = -1; 
    queue<pair<int, int> >swan, next_swan, water, next_water; 
    cin>>R>>C; 
    for(int i =0; i<R; i++)
    {
        cin>>inp[i]; 
        for(int j =0; j<C; j++)
        {
            if(inp[i][j]=='L')
            {
                if(swan1.first==-1)
                {
                    swan1 = make_pair(i, j); 
                }
                else
                {
                    swan2 = make_pair(i, j); 
                }
                inp[i][j]='.'; // make the original swan location as water
            }
            if(inp[i][j]=='.') // not else if!!!!!!
            {
                water.push(make_pair(i, j)); // insert all water blocks  
                water_check[i][j] = true; // check visited
            }
        }
    }
    swan.push(make_pair(swan1.first, swan1.second)); 
    swan_check[swan1.first][swan1.second] = true; 
    
    for(int day = 0; ; day++) // similar to while(1){ day++}
    {
        // melt ice first
        while(!water.empty())
        {
            int r = water.front().first; 
            int c = water.front().second; 
            inp[r][c]='.'; 
            water.pop(); 
            for(int i =0; i<4; i++)
            {
                int nr = r + dr[i]; 
                int nc = c + dc[i]; 
                if(nr<0 or nr>=R or nc<0 or nc>=C) continue; 
                if(water_check[nr][nc]) continue; 
                water_check[nr][nc] = true; 
                if(inp[nr][nc]=='.')
                {
                    water.push(make_pair(nr, nc)); 
                }
                else 
                {
                    next_water.push(make_pair(nr, nc)); 
                }
            }
        }
        while(!swan.empty())
        {
            int r = swan.front().first; 
            int c = swan.front().second; 
            swan.pop(); 
            for(int i =0; i<4; i++)
            {
                int nr = r + dr[i]; 
                int nc = c + dc[i]; 
                if(nr<0 or nr>=R or nc<0 or nc>=C) continue; 
                if(swan_check[nr][nc]) continue; 
                swan_check[nr][nc] = true; 
                if(inp[nr][nc]=='.')
                {
                    swan.push(make_pair(nr, nc)); 
                }
                else 
                {
                    next_swan.push(make_pair(nr, nc)); 
                    
                }
            }
        }
        if(swan_check[swan2.first][swan2.second]) 
        {
            cout<<day<<'\n'; 
            break; 
        }
        swan = next_swan; 
        water = next_water; 
        next_swan = queue<pair<int,int> >(); 
        next_water = queue<pair<int, int> >(); 
    }
    
    
    
    return 0; 
}
