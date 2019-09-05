#include<iostream>
using namespace std; 
#define MAX 100
int paper[MAX][MAX]; 
const int N = 10; 
int main()
{
    int M; 
    cin>>M; 
    int r, c; 
    while(M--)
    {
        cin>>c>>r; 
        r=MAX-r-1; 
        for(int i = r; i>r-N; i--)
        {
            for(int j = c; j<c+N; j++)
            {
                paper[i][j] = 1; 
            }
        }
    }
    int cnt =0; 
    for(int i =0; i<100; i++)
    {
        for(int j =0;j <100; j++)
        {
            if(paper[i][j]) cnt++; 
        }
    }
    cout<<cnt<<'\n'; 
    return 0; 
}
