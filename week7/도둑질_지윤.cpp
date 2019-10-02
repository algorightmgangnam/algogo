#include <string>
#include <vector>
#include<iostream>

using namespace std;

int d[1000001] = {0,};

int solution(vector<int> money) {
	int answer = 0;
	
    // 첫 번째 집을 터는 경우
    d[1] = money.at(0);
    d[2] = 0;
    answer = max(d[1], d[2]);
    
    for(int i = 3; i <= money.size()-1 ; i++){
        d[i] = max(d[i-2], d[i-3]) + money.at(i-1);
        
        answer = max(answer, d[i]);
    }
    
    d[1] = 0;
    d[2] = money.at(1);
    d[3] = money.at(2);
    answer = max(answer,max(d[2], d[3]));
    for(int i = 4; i <= money.size() ; i++){
        d[i] = max(d[i-2],d[i-3]) + money.at(i-1);
         answer = max(answer, d[i]);
        
    }
    
	return answer;
}
