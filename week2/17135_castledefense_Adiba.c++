#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std; 
#define MAX 15
int N, M, D; 
int ans; 
const int ARCH_NUM = 3; 
struct rival{
   int row; 
   int col; 
   rival():row(-1), col(-1){}
   rival(int row, int col):row(row), col(col){}
}; 
vector<rival>rival_info; 

int dist(int row1, int col1, int row2, int col2)
{
    return abs(row1-row2) + abs(col1-col2); 
}
int chosen[ARCH_NUM]; 

void solve()
{
    int shoot_cnt = 0; 
    // 1. Get the current location of archers
    vector<int>cur_archers; 
    for(int i =0; i<ARCH_NUM; i++)
    {
        cur_archers.push_back(chosen[i]); 
    } 
    // 2. Get a copy of rival information
    vector<rival>cur_rivals = rival_info; 
    while(!cur_rivals.empty())
    {
        set<int>killed; 
        for(int i =0; i<ARCH_NUM; i++)
        {
            int arch_col = cur_archers[i]; 
            int shoot_idx = 0; 
            int cur_dist = dist(N, arch_col, cur_rivals[0].row, cur_rivals[0].col); 
            for(int j =1; j<cur_rivals.size(); j++)
            {
                rival r(cur_rivals[j].row, cur_rivals[j].col); 
                int temp_dist = dist(N, arch_col, r.row, r.col); 
                if(temp_dist<cur_dist)
                {
                    shoot_idx = j; 
                    cur_dist = temp_dist; 
                }
                else if(temp_dist==cur_dist && r.col < cur_rivals[shoot_idx].col)
                {
                    shoot_idx = j; 
                }
            }
            if(cur_dist<=D)
            {
                killed.insert(shoot_idx); 
            }
        }
        std::set<int>::iterator it;  
        for(it = killed.begin(); it!=killed.end(); it++)
        {
            shoot_cnt++; 
            int idx = *it; 
            cur_rivals[idx].row = N, cur_rivals[idx].col = -1; 
        }
        vector<rival>next_info; 
        for(int i =0; i<cur_rivals.size(); i++)
        {
            if(cur_rivals[i].row<N-1)
            {
                next_info.push_back( rival(cur_rivals[i].row+1, cur_rivals[i].col) ); 
            }
        }
        cur_rivals = next_info; 
        
    }
    
    ans = max(ans, shoot_cnt); 
}

void comb(int idx, int chosen_idx)
{
    if(idx>M) return; 
    if(chosen_idx==ARCH_NUM)
    {
        solve(); 
        return; 
    }
    chosen[chosen_idx] = idx; // starting from 0_Th loc
    comb(idx+1, chosen_idx+1); 
    comb(idx+1, chosen_idx); 
    
}
int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    int temp; 
    cin>>N>>M>>D; 
    for(int i =0; i<N; i++)
    {
        for(int j =0; j<M; j++)
        {
            cin>>temp; 
            if(temp) rival_info.push_back(rival(i, j)); 
        }
    }
    comb(0, 0);
    
    cout<<ans<<'\n'; 
    
    return 0; 
}
