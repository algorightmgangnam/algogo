#include<iostream> // 숫자카드 14:31~
#include<vector>
#include<algorithm>
using namespace std; 
int N, M; 
int inp[500001];
bool found = false; 
bool search(int left, int right,  int num)
{
    if(left<=right)
    {
        int mid = (left + right)/2; 
        if(inp[mid]==num) {
            found = true; 
            return true; 
        }
        else if(inp[mid]<num)
        {
           return search(mid+1, right, num); 
        }
        else
        {
            return search(left, mid-1, num); 
        }
    }
    else return false; 
}

int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    cin>>N;
    int temp; 
    for(int i =0; i<N; i++)
    {
        cin>>inp[i];  
    }
    sort(inp, inp+N); 
    cin>>M; 
    for(int i =0; i<M; i++)
    {
        cin>>temp; 
        found = false; 
        if(search(0, N-1, temp)) cout<<1<<' '; 
        else cout<<0<<' '; 
    }
    cout<<'\n'; 
    
    return 0; 
}
