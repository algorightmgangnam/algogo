#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include<algorithm>


using namespace std;

struct comp {
	bool operator()(pair<int,int> p1, pair<int,int> p2) {
		if (p1.first == p2.first) return p1.second > p2.second;
		return p1.first > p2.first;
	}
};

struct job_info {
	int job_id, req_time, elapsed_time;
};

vector<job_info> v;

bool cmp(const job_info &j1, const job_info &j2) {
	if (j1.req_time == j2.req_time) {
		return j1.elapsed_time < j2.elapsed_time;
	}
	return j1.req_time < j2.req_time;
}

int solution(vector<vector<int>> jobs) {
	int answer = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, comp> pq;
	
	for (int i = 0; i < jobs.size(); i++) {
		v.push_back({i, jobs.at(i).at(0), jobs.at(i).at(1)});//job id, req time, elapsed time
	}

	sort(v.begin(), v.end(),cmp); // 요청이 들어온 순서대로 정렬
	
	int cur_time = v.at(0).req_time;
	int idx = 0;

	while (idx < v.size() || !pq.empty()) {
       
        if(idx < v.size()){
            if (v.at(idx).req_time <= cur_time) {
                pq.push(make_pair(v.at(idx).elapsed_time, v.at(idx).req_time)); // 요청 시간, 걸린 시간
                idx++;
                continue;
            }
        }
		
        if(!pq.empty()){
            answer = answer + (cur_time - pq.top().second + pq.top().first);
            cur_time += pq.top().first;
            cout<<answer<<" "<<pq.top().first<<"\n";
            pq.pop();

        }
        else{
            cur_time = v.at(idx).req_time;
            
             pq.push(make_pair(v.at(idx).elapsed_time, v.at(idx).req_time));
            idx++;
        }
		

	}
    
  
    
	answer = answer / jobs.size();
	return answer;
}>
#include <vector>
#include <queue>
#include<algorithm>


using namespace std;

struct comp {
	bool operator()(pair<int,int> p1, pair<int,int> p2) {
		if (p1.first == p2.first) return p1.second > p2.second;
		return p1.first > p2.first;
	}
};

struct job_info {
	int job_id, req_time, elapsed_time;
};

vector<job_info> v;

bool cmp(const job_info &j1, const job_info &j2) {
	if (j1.req_time == j2.req_time) {
		return j1.elapsed_time < j2.elapsed_time;
	}
	return j1.req_time < j2.req_time;
}

int solution(vector<vector<int>> jobs) {
	int answer = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, comp> pq;
	
	for (int i = 0; i < jobs.size(); i++) {
		v.push_back({i, jobs.at(i).at(0), jobs.at(i).at(1)});//job id, req time, elapsed time
	}

	sort(v.begin(), v.end(),cmp); // 요청이 들어온 순서대로 정렬
	
	int cur_time = v.at(0).req_time;
	int idx = 0;

	while (idx < v.size() || !pq.empty()) {
       
        if(idx < v.size()){
            if (v.at(idx).req_time <= cur_time) {
                pq.push(make_pair(v.at(idx).elapsed_time, v.at(idx).req_time)); // 요청 시간, 걸린 시간
                idx++;
                continue;
            }
        }
		
        if(!pq.empty()){
            answer = answer + (cur_time - pq.top().second + pq.top().first);
            cur_time += pq.top().first;
            cout<<answer<<" "<<pq.top().first<<"\n";
            pq.pop();

        }
        else{
            cur_time = v.at(idx).req_time;
            
             pq.push(make_pair(v.at(idx).elapsed_time, v.at(idx).req_time));
            idx++;
        }
		

	}
    
  
    
	answer = answer / jobs.size();
	return answer;
}
