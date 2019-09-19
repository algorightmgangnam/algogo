#include<bits/stdc++.h>
using namespace std; 
#define MAX 101
#define endl "\n"

int n, ans; 
string input; 
int sz; 
int k; 
void init()
{
    ans = 0; 
    sz = input.size(); 
}
void dfs(int cur, int cnt)
{
    if(cnt==k)
    {
        ans = max(ans, stoi(input)); 
        return; 
    }
    for(int i = cur; i<sz;  i++)
    {
        for(int j = i +1; j<sz; j++)
        {
            if(input[i]<=input[j])
            {
                swap(input[i], input[j]); 
                dfs(i, cnt+1); 
                swap(input[i], input[j]); 
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    
    int T; 
    cin>>T; 
    for(int tc = 1; tc<=T; tc++)
    {
        cin>>input>>k; 
        init(); 
        dfs(0, 0); 
        cout<<"#"<<tc<<" "<<ans<<"\n"; 
    }
    
    return 0; 
}
