#include<bits/stdc++.h>
using namespace std; 
#define MAX 101
#define endl ’\n’

struct magnet
{
   double x; 
   double m; 
}; 
magnet info[11]; 

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); 
   // cout.tie(0); 
    
    cout<<fixed; 
    cout.precision(10); 
    int T, N; 
    cin>>T; 
    for(int tc = 1; tc<=T; tc++)
    {
        cin>>N; 
        for(int i = 1; i<=N; i++)
        {
            cin>>info[i].x; 
        }
        for(int i = 1; i<=N; i++)
        {
            cin>>info[i].m; 
        }
        cout<<"#"<<tc<<" "; 
        // for all possible cases 
        for(int i =1; i<N; i++)
        {
            double left, right, mid, ans;
            left = info[i].x, right = info[i+1].x; 
            ans = 0; 
        
            for(int cnt = 0; cnt<=50; cnt++)
            {
                mid = (left + right)/2.0; 
                double sum = 0; 
                for(int j = 1; j<=i; j++)
                {
                    sum+=(info[j].m)/((info[j].x - mid)*(info[j].x - mid)); 
                }
                for(int j = i+1; j<=N; j++)
                {
                    sum-=(info[j].m)/((info[j].x - mid)*(info[j].x-mid)); 
                }
                if(sum>0)
                {
                    left = mid; 
                }
                else 
                {
                    ans = mid; right = mid; 
                }
            }
            cout<<ans<<" "; 
        
        } 
        cout<<'\n'; 
    }
    
    
    return 0; 
}
