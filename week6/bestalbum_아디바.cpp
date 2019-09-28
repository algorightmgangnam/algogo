#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
// comparator to sort by the most amount of songs per genre
bool cmpG(pair<string, int>a, pair<string, int>b)
{
    return a.second>b.second; 
}
// comparator between plays: sort by played num and then sort by index
bool cmpP(pair<int, int>a, pair<int, int>b)
{
    if(a.second==b.second)
    {
        return a.first<b.first; 
    }
    return a.second>b.second; 

}
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    map<string, int>genmap;  // genres and playcount
    map<string, vector< pair<int, int> > >playmap;  // all play vectors per genre
    for(int i =0; i<genres.size(); i++)
    {
        genmap[genres[i]]+=plays[i]; 
        playmap[genres[i]].push_back({i, plays[i]}); 
    }
    vector<pair<string, int>>gensort; 
    // need to copy to vector in order to sort 
    copy(genmap.begin(), genmap.end(), 
         back_inserter<vector<pair<string, int>>>(gensort)); 
    sort(gensort.begin(), gensort.end(), cmpG); 
    
    int cnt; 
    for(int i =0; i<genmap.size(); i++)
    {
        vector<pair<int, int>> v = playmap[gensort[i].first]; 
        sort(v.begin(), v.end(), cmpP); 
        cnt = 2; 
        if(v.size()<cnt) cnt = v.size(); 
        for(int j =0; j<cnt; j++)
        {
            answer.push_back(v[j].first); 
        }
    }
    
    
    return answer;
}
