#include<iostream>
#include<vector>
using namespace std; 
#define MAX 8
int life[MAX]; 
int weight[MAX]; 
int N, ans; 

void dfs(int cur_idx)
{ 
    // if the egg on hand is the last one 
    if(cur_idx>=N)
    {
        int loc_ans = 0; 
        // count the number of broken eggs
        for(int i =0; i<N; i++) {
            if(life[i]<=0) 
            {
                loc_ans++;
            }
        }
        ans = max(ans, loc_ans); 
        return; 
    }
    // if the egg is broken, go and look for another nonbroken 
    if(life[cur_idx]<=0) dfs(cur_idx+1); 
    else
    {
        bool can_break = false; 
        for(int egg_idx = 0; egg_idx<N; egg_idx++)
        {
            if(egg_idx==cur_idx) continue;    
            
            if(life[egg_idx]<=0) continue; 
            life[cur_idx]-=weight[egg_idx]; 
            life[egg_idx]-=weight[cur_idx]; 
            can_break = true; 
            dfs(cur_idx+1); 
            // backtrack for other eggs
            life[egg_idx]+=weight[cur_idx]; 
            life[cur_idx]+=weight[egg_idx]; 
        }
        if(!can_break) 
        {
            int cnt = 0; 
            for(int i =0; i<N; i++)
            {
                if(life[i]<=0) cnt++; 
            }
            ans = max(ans, cnt); 
            return; 
        }
    }
}

int main()
{
     cin>>N; 
     for(int i =0; i<N; i++)
     {
         cin>>life[i]>>weight[i]; 
     }
     dfs(0); 
     cout<<ans<<'\n';
     
    return 0; 
}
