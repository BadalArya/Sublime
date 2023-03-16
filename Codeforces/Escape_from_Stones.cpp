#include <bits/stdc++.h>

using namespace std;

int main(){
	string s; cin >> s;

	int start = 1;

	int n = s.size();
	vector<int> ans(n);
	int startIdx = 0;
	int lastIdx = n - 1;

	for(int i = 0; i < n; i++){
		if(s[i] == 'r'){
			ans[startIdx++] = start;
		}else{
			ans[lastIdx--] = start;
		}
		start++;
	}
	
	for(int i = 0; i < n; i++){
		printf("%d \n", ans[i]);
	}
}