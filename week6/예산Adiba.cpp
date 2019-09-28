#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solution(vector<int> budgets, int M) {
    int answer = 0; 
    long long total =0, avg = 0;
    sort(budgets.begin(), budgets.end()); 
    for(int i =0; i<budgets.size(); i++)
    {
        total+=budgets[i]; 
    }
    if(M>=total) answer = budgets.back(); 
    else
    {
        avg = M/budgets.size(); 
        int sz = budgets.size(); 
        for(int i =0; i<budgets.size(); i++)
        {
            if(budgets[i]<=avg)
            {
                M-=budgets[i]; sz--; 
                avg = M/sz; // update average value whenever one value is satisfied
            }
            else
            {
                answer = avg; break; 
            }
        }
    }
    
    return answer;
}
