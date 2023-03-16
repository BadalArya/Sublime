#include <bits/stdc++.h>

using namespace std;

int main(){
	int y, w; cin >> y >> w;
	int maxm = max(y, w);

	if(maxm == 1){
		cout << "1/1" << endl;
	}else if(maxm == 6){
		cout << "1/6" << endl;
	}else if(maxm == 5){
		cout << "1/3" << endl;
	}else if(maxm == 4){
		cout << "1/2" << endl;
	}else if(maxm == 3){
		cout << "2/3" << endl;
	}else if(maxm == 2){
		cout << "5/6" << endl;
	}
}