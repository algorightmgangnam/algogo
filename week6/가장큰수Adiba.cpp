#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
bool cmp(string a, string b)
{
    string ab = a; ab.append(b); 
    string ba = b; ba.append(a); 
    return ab>ba?true:false; 
}
string solution(vector<int> numbers) {
    string answer = "";
    vector<string>vals; 
    for(int i =0; i<numbers.size(); i++)
    {
        vals.push_back(to_string(numbers[i])); 
    }
    sort(vals.begin(), vals.end(), cmp); 
    
   int cnt = 0; 
    bool zero = true; 
    for(int i = 0; i<vals.size(); i++)
    {
        if(vals[i][0]=='0' && zero) continue; 
        answer.append(vals[i]);  zero = false;  
    }
    if(answer.size()==0) answer = "0"; 
    
    return answer;
}
