#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
struct compare
{
    bool operator()( pair<int, int> &a,  pair<int, int> &b)
    {
        return a.second>b.second; 
    }
}; 



int solution(vector<vector<int>> jobs) {
    int answer = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, compare>pq; 
    int N = jobs.size(); 
    for(int i =0; i<N; i++)
    {
        pq.push({jobs[i][0], jobs[i][1]}); 
    }
   
    vector<pair<int, int> >v; 
    while(!pq.empty()) {
        v.push_back({pq.top().first, pq.top().second}); pq.pop(); 
    }
    int cur_time =0, total =0; 
    while(!v.empty())
    {
        for(int i =0; i<v.size(); i++)
        {
            int stime = v[i].first; 
            int btime = v[i].second; 
            // We can only start a job if starting time is less than 
            // or equal to current time 
            if(stime<=cur_time)
            {
                cur_time+=btime; 
                int add_val = cur_time - stime; 
                total+=add_val; 
                v.erase(v.begin() + i); 
                break; 
            }
            if(i==v.size()-1) {
                cur_time++; 
            }
        }
    }
    answer = total/N; 
    return answer;
}
