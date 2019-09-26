#include <string>
#include <vector>
#include<map>
#include<algorithm>
#include<queue>

using namespace std;

class songInfo {
public:
	int song_num, count;

	songInfo(int n, int c) {
		this->song_num = n;
		this->count = c;
	}

	bool operator <(songInfo &s) {
		return this->count > s.count;
	}
};

bool cmp(const pair<string,int> &s1, const pair<string,int> &s2) {
	return s1.second > s2.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
	vector<int> answer;

	map<string, int> m;

	map<string, vector<songInfo>> m2;
	string genre;
	for (int i = 0; i < genres.size(); i++) {
		genre = genres.at(i);

		m[genre] += plays.at(i);
		m2[genre].push_back(songInfo( i, plays.at(i)));

	}

	vector<pair<string, int>> v(m.begin(), m.end());
	sort(v.begin(), v.end(), cmp);


	vector<songInfo> ptr;
	for (int i = 0; i < v.size();i++) {
		genre = v.at(i).first;
		ptr = m2[genre];

		sort(ptr.begin(), ptr.end());

		answer.push_back(ptr.at(0).song_num);
        if(ptr.size() > 1) answer.push_back(ptr.at(1).song_num);
	
	}
	return answer;
}
