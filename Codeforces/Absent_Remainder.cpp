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

int toInt(string s) {int res; stringstream ss; ss<<s; ss>>res; return res; }
string toString(int n) { stringstream ss; ss<<n; return ss.str(); }

//--------------------------------------------------------------------------------------------------------------------------------------

uint modInverse(int n, int p=MOD){       // using fermats little thm. [p needs to be prime which is mostly the case as mod value generally is 1e9+7]
    return power(n, p - 2, p);
}

//--------------------------------------------------------------------------------------------------------------------------------------

int gcd (int a, int b) { return a ? gcd (b % a, a) : b; }
int lcm (int a, int b) {return (a*b) / gcd(a, b);}

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

void Solve(){
	int n; cin >> n;
	vi a(n); cin >> a;
	srt(a);
	bool flag = false;
	unordered_map<int,int> sp;
	for(int i = 0; i < n; i++){
		if(a[i] == 1){
			flag = true;
		}
		sp[a[i]]++;
	}    

	if(flag){
		vpp ans;
		for(int i = 0; i < n; i++){
			if(a[i] != 1){
				ans.push_back({a[i], 1});
			}
			if(ans.size() == n / 2){
				cout << ans;
				return;
			}
		}
	}
	vpp ans;
	map<pair<int,int>, int> mp;
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			if(!mp[{a[i], a[j]}] && !mp[{a[j], a[i]}]){
				if(!sp[a[i] % a[j]]){
					ans.push_back({a[i], a[j]});
				}
				if(ans.size() == n / 2){
					cout << ans;
					return;
				}
				if(!sp[a[j] % a[i]]){
					ans.push_back({a[j], a[i]});
				}
				mp[{a[i], a[j]}] = 1;
			}
			if(ans.size() == n / 2){
				cout << ans;
				return;
			}
		}
	}
}

int32_t main (){
    Badal;
    int tc = 1;
    cin >> tc;
    while (tc--){
        Solve();
    }
}
