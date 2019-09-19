#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

vector<string> v;


int main() {

	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		string s;
		int K;
		cin >> K;
		cin >> s;
		int len = s.length();
		v.resize(len + 1);
		for (int i = 0; i < len; i++)
		{
			string tmp = "";
			for (int j = i; j < len; j++)
			{
				tmp += s[j];
			}
			v[i] = tmp;
		}
		
		sort(v.begin(), v.end());
		cout << "#" << tc+1 <<" "<< v[K] << "\n";
		v.clear();
	}

	return 0;

}
