#include<bits/stdc++.h>
using namespace std; 
int R, C, K; 

struct distort{
   int idx; 
   int row; 
   int col; 
   int range;
   distort():idx(0), row(0), col(0), range(0){}
   distort(int idx, int row, int col, int range): idx(idx),row(row), col(col), range(range){}
}; 
struct coord
{
    int row; 
    int col; 
};
vector<distort>dv; 
int inp[50][50]; 
vector<int>order; 
int max_val = 1e9; 
int dr[] = {-1, 1, -1, 1}; // leftup, leftdown, rightup, rightdown
int dc[] = {-1, -1, 1, 1}; //  0        1          2        3

void rotate(int row, int col, int range, vector<vector<int> >&curmap)
{
    coord left_up, left_down, right_up, right_down; 
    
    for(int m = 1; m<=range; m++)
    {
        left_up.row = row + dr[0]*m; left_up.col  = col + dc[0]*m; 
        left_down.row = row + dr[1]*m; left_down.col = col + dc[1]*m; 
        right_up.row = row + dr[2]*m; right_up.col = col + dc[2]*m; 
        right_down.row = row + dr[3]*m; right_down.col = col +dc[3]*m;
        int temp = curmap[left_up.row][left_up.col]; 
        for(int cur_row = left_up.row; cur_row<left_down.row; cur_row++)
        {
            curmap[cur_row][left_up.col] = curmap[cur_row+1][left_up.col]; 
        }
        for(int cur_col = left_down.col; cur_col<right_down.col; cur_col++)
        {
            curmap[left_down.row][cur_col] = curmap[left_down.row][cur_col+1]; 
        }
        for(int cur_row = right_down.row; cur_row>right_up.row; cur_row--)
        {
            curmap[cur_row][right_down.col] = curmap[cur_row-1][right_down.col]; 
        }
        for(int cur_col = right_up.col; cur_col>left_up.col; cur_col-- )
        {
            curmap[right_up.row][cur_col] = curmap[right_up.row][cur_col-1]; 
        }
        curmap[left_up.row][left_up.col+1] =temp; 
        
    }
    
}

void solve_each(vector<distort>&chosen)
{
    vector<vector<int> >cpymap(R, vector<int>(C,0)); 
    
    for(int i =0; i<R; i++)
    {
        for(int j =0; j<C; j++)
        {
           // cout<<cpymap[i][j]<<' '; 
            cpymap[i][j] = inp[i][j]; 
        }
        //cout<<endl; 
    }
    for(int i =0; i<K; i++)
    {
        int row = chosen[i].row; 
        int col = chosen[i].col; 
        int range = chosen[i].range; 
       rotate(row, col, range, cpymap); 
    }
    for(int i=0; i<R; i++)
    {
        int sum =0; 
        for(int j =0; j<C; j++)
        {
            sum+=cpymap[i][j]; 
        }
        max_val = min(max_val, sum); 
    }
   
   // cout<<"max now: "<<max_val<<endl; 
}

void solve()
{
    do
    {
        vector<distort>chosen(K); 
        for(int i =0; i<K; i++)
        {
            chosen[i] = dv[order[i]]; 
        } 
        // call solve here 
        solve_each(chosen); 
        
    }while(next_permutation(order.begin(), order.end())); 
}

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    
    cin>>R>>C>>K; 
    for(int i =0; i<R; i++)
    {
        for(int j =0; j<C; j++)
        {
            cin>>inp[i][j]; 
        }
    }
    int r, c, s; 
    for(int i =0; i<K; i++)
    {
        cin>>r>>c>>s; 
        r-=1; c-=1; 
        distort d(i, r, c, s); 
        dv.push_back(d); 
    }
    for(int i =0; i<K; i++)
    {
        order.push_back(i); 
    }
    solve(); 
    cout<<max_val<<'\n';
    return 0; 
}
