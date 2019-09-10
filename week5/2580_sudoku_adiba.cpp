#include<iostream> // second rnd: 13:41~
#include<queue>
#include<cstring>
using namespace std; 
int dr[] = {1, -1, 0, 0}; 
int dc[] = {0, 0, 1, -1}; 

pair<int, int> board[9][9]; 
vector<pair<int, int> >info[10]; 
vector<pair<int, int> >empt; 
int EMPTY_SIZE; 

bool solve(int idx)
{
    if(idx==EMPTY_SIZE)
    {
        for(int i =0; i<9; i++)
        {
            for(int j =0; j<9; j++)
            {
                cout<<board[i][j].first<<' '; 
            }
            cout<<'\n'; 
        }
        exit(0); 
        return true; 
    }
    int row = empt[idx].first; 
    int col = empt[idx].second; 
    int block_num = board[row][col].second; 
    vector<pair<int, int> > cur_info = info[block_num]; 
    for(int i =1; i<=9; i++)
    {
        // try all the numbers from 1 to 9 
        bool col_ok =true , row_ok=true, block_ok=true;
        for(int k = 0; k<9; k++)
        {
            if(board[row][k].first==i) {col_ok = false; break;}
            if(board[k][col].first==i) {row_ok = false; break;}
            if(board[cur_info[k].first][cur_info[k].second].first==i) {block_ok = false; break;}
        }
        if(col_ok and row_ok and block_ok)
        {
            board[row][col].first = i; 
           if(solve(idx+1)) return true; 
            board[row][col].first = 0; 
        }
    }
    return false; 
}

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    
    int idx = 1, k = 1; 
    int temp=1, save=1; 
    for(int i =0; i<9; i++)
    {
        if(i!=0 and i%3==0)
        {
            idx = k+3;  
            save = k+3; 
            k+=3; 
        }
        for(int j =0; j<9; j++)
        {
             if(j!=0 and j%3==0) idx++; 
            cin>>temp; 
            board[i][j] = make_pair(temp, idx); 
            info[idx].push_back(make_pair(i ,j)); 
            if(temp==0)
            {
                empt.push_back(make_pair(i, j)); EMPTY_SIZE++; 
            }
        }
        idx = save; 
        
       
    }
    
    solve(0); 
    
    return 0; 
}
