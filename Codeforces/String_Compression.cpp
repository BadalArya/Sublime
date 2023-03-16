// ============================================================================ //
// ||                                                                        || //
// ||                    Bhagalpur College of Engineering                    || //
// ||                              Badal Kumar                               || //
// ||                                2020-24                                 || //
// ||                                                                        || //
// ============================================================================ //

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <climits>
#include <iomanip>
#include <cstring>
#include <math.h>
#include <numeric>

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------

#define MOD 1e9+7
#define Badal cin.sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define int long long int
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi >
#define vb vector<bool>
#define vvb vector<vb >
#define vpp vector<pair<int,int>>
#define fr(i,n) for(int i=0; i<(n); i++)
#define rep(i,a,n) for(int i=(a); i<=(n); i++)
#define nl cout << endl
#define all(v) v.begin(),v.end()
#define sz(v) (int)(v.size())
#define srt(v)  sort(v.begin(),v.end())         // sort
#define mxe(v)  *max_element(v.begin(),v.end())     // find max element in vector
#define mne(v)  *min_element(v.begin(),v.end())     // find min element in vector
#define unq(v)  v.resize(distance(v.begin(), unique(v.begin(), v.end())));

//--------------------------------------------------------------------------------------------------------------------------------------

uint power(int x, int y, int p =  MOD){
    unsigned long long res = 1;
    
    x = x % p;
    while (y > 0){
        
        if (y & 1)
            res = (res * x) % p;
        
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

//--------------------------------------------------------------------------------------------------------------------------------------

uint modInverse(int n, int p=MOD){       // using fermats little thm. [p needs to be prime which is mostly the case as mod value generally is 1e9+7]
    return power(n, p - 2, p);
}

//--------------------------------------------------------------------------------------------------------------------------------------

uint nCr(int n, int r, int p=MOD){     // faster calculation..
    if (n < r)
        return 0;
    
    if (r == 0)
        return 1;
    
    vector<int> fac(n+1,0);
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;
    
    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}

//--------------------------------------------------------------------------------------------------------------------------------------

template<typename typC,typename typD> istream &operator>>(istream &cin,pair<typC,typD> &a) { return cin>>a.first>>a.second; }
template<typename typC> istream &operator>>(istream &cin,vector<typC> &a) { for (auto &x:a) cin>>x; return cin; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const pair<typC,typD> &a) { return cout<<a.first<<' '<<a.second; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const vector<pair<typC,typD> > &a) { for (auto &x:a) cout<<x<<endl; return cout; }
template<typename typC> ostream &operator<<(ostream &cout,const vector<typC> &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }

//--------------------------------------------------------------------------------------------------------------------------------------

void eraseString(string &s, vector<string> &toDelete, int k){
	if(s == ""){
		return;
	}

	if(s.size() < k){
		return;
	}

	int n = s.size();
	int idx = -1;
	bool flag = true;
	for(int i = 0; i < 26; i++){
		// cout << toDelete[i];
		if(s.find(toDelete[i]) >= 0 && s.find(toDelete[i]) <= s.size()){
			idx = s.find(toDelete[i]);
			flag = false;
			break;
		}
	}
	if(flag){
		return;
	}
	
	if(idx != -1){
		s.erase(idx, k);
	}
	eraseString(s, toDelete, k);
}

void Solve(){
	string word; cin >> word;
	int k; cin >> k;
	vector<string> toDelete(26);
	for(int i = 0; i < 26; i++){
		string flag = "";
		flag += (i + 'a');
		int start = 1;
		while(start * 2 < k){
			flag += flag;
			start *= 2;
		}
		for(int j = flag.size(); j < k; j++){
			flag += i + 'a';
		}
		toDelete[i] = (flag);
	}
	// cout << toDelete << endl;
	cout << word.size() << endl;
	string s = word;
	bool bc = true;
	while(s != "" && bc){
		bc = false;
		for(int i = 0; i < 26; i++){
			if(s.find(toDelete[i]) >= 0 && s.find(toDelete[i]) <= s.size()){
				bc = true;
				s.erase(s.find(toDelete[i]), k);
			}
		}
	}
	cout << s << endl;
	eraseString(word, toDelete, k);
	// return word;
	cout << word << endl;
}

int32_t main (){
    Badal;
    int tc = 1;
    while (tc--){
        Solve();
    }
}
