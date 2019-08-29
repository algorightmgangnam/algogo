#include <iostream>
#include<vector>
using namespace std;
#define MAX 100001
#define MOD 9901

int N;

int dp[3][MAX];
// dp[0][x] : not inserted at x line 
// dp[1][x] : inserted at left side 
// dp[2][x] : inserted at right side

int main()
{
        cin >> N;
        dp[0][1] = 1; // 1 way to insert no lion on the first line 
        dp[1][1] = 1; // 1 way to insert on the left side on the first line
        dp[2][1] = 1; // 1 way to insert on the right side on the first line 
        
        
        for(int line = 2; line<=N; line++)
        {
            dp[0][line] = (dp[0][line-1] + dp[1][line-1] + dp[2][line-1])%MOD; 
            dp[1][line] = (dp[0][line-1] + dp[2][line-1])%MOD; 
            dp[2][line] = (dp[0][line-1] + dp[1][line-1])%MOD; 
        }
        
        int ans  = (dp[0][N] + dp[1][N] + dp[2][N])%MOD; 
        cout<<ans<<"\n"; 
        return 0;

}
