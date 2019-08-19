#include<iostream>
#include<vector>
using namespace std; 
vector<int>digits;
vector<char>ops; 
int ans = -2147483647; 
int calc(int a, int b, char op)
{
    if(op=='-') return a-b; 
    else if(op=='*') return a*b; 
    else return a+b; 
}

void solve(int pass_res, int idx)
{
    // idx: operator_idx
    
    if(idx>=ops.size())
    {
        ans = max(ans, pass_res); 
        return;
    }
    int cur_res = calc(pass_res, digits[idx+1], ops[idx]); 
    solve(cur_res, idx+1); 
    
    if(idx+2<digits.size())
    {
        int in_bracket_res = calc(digits[idx+1], digits[idx+2], ops[idx+1]); 
        int cur_res = calc(pass_res, in_bracket_res, ops[idx]); 
        solve(cur_res, idx+2); 
    }
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N; 
    cin>>N; 
    string expr; 
    cin>>expr; 
    for(int i =0; i<expr.length(); i++)
    {
        if(expr[i]>='0' and expr[i]<='9')
        {
            digits.push_back(expr[i]-'0'); 
        }
        else 
        {
            ops.push_back(expr[i]); 
        }
    }
    
    solve(digits[0], 0); 
    cout<<ans<<'\n';
    return 0; 
}
