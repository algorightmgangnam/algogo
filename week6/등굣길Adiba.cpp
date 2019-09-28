#include <string>
#include <vector>
#define MOD 1000000007
using namespace std;
// should be solved using dp!!!
int brd[101][101]; 
int ways[101][101]; 
int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    for(auto p: puddles)
    {
        brd[p[1]][p[0]] = 1; 
    }
    
    ways[0][1] = 1; // initialization
    for(int r =1; r<=n; r++)
    {
        for(int c = 1; c<=m; c++)
        {
            // 장애물이 있으면, 거기까지 못감
            if(brd[r][c]) ways[r][c] = 0; 
            // 없으면, 위쪽에서 올수 있는 경우의 수 + 왼쪽에서 올수 있는 겨우의 수
            else
                ways[r][c] = (ways[r-1][c] + ways[r][c-1])%MOD; 
        }
    }
    
    answer = ways[n][m];
    return answer;
}
