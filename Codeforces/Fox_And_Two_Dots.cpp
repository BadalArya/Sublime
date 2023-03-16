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

vector<vector<int>> graph(2510);
vector<int> vis(2510, 0);

bool dfs_cycle(int source, int parent){
		vis[source] = 1;
		for(auto ch: graph[source]){
			if(!vis[ch]){
				if(dfs_cycle(ch, source)){
					// cout << ch << " " << source << endl;
					return true;
				}
			}else if(ch != parent){
				// cout << ch << " " << source << endl;
				return true;
			}
		}

	return false;
}

void Solve(){
	int n, m; cin >> n >> m;
	char color[n][m];

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> color[i][j];
		}
	}

	// for(int i = 0; i < n; i++){
	// 	for(int j = 0; j < m; j++){
	// 		cout << color[i][j];
	// 	}
	// 	cout << endl;
	// }    

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int current = (i*m) + j + 1;
			int next = current + 1;
			int bottom = (i+1)*m + j + 1;
			// cout << current << " " << next << " " << bottom << endl;
			if(j < m - 1 && color[i][j] == color[i][j+1]){
				// cout << i << " " << j << endl;
				graph[current].push_back(next);
				graph[next].push_back(current);
			}
			if(i < n - 1 && color[i][j] == color[i+1][j]){
				// cout << i << " " << j << endl;
				graph[current].push_back(bottom);
				graph[bottom].push_back(current);
			}
		}
	}

	for(int i = 1; i <= n*m; i++){
		// cout << i << "-> ";
		// for(auto ch : graph[i]){
		// 	cout << ch << " ";
		// }
		// cout << endl;
	}

	for(int i = 1; i <= n*m; i++){
		if(!vis[i]){
			if(dfs_cycle(i, -1)){
				cout << "Yes" << endl;
				return;
			}
		}
	}

	cout << "No" << endl;

}

int32_t main (){
    Badal;
    int tc = 1;
    while (tc--){
        Solve();
    }
}
