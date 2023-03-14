//This code been written by: Badal
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
// make sure to sort before applying unique // else only consecutive duplicates would be removed

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

// =============================================================================================================
uint modInverse(int n, int p=MOD){       // using fermats little thm. [p needs to be prime which is mostly the case as mod value generally is 1e9+7]
    return power(n, p - 2, p);
}
// can also derive this using extended euclidean... however this has a much simpler code....

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

// ================================== take ip/op like vector,pairs directly!==================================
template<typename typC,typename typD> istream &operator>>(istream &cin,pair<typC,typD> &a) { return cin>>a.first>>a.second; }
template<typename typC> istream &operator>>(istream &cin,vector<typC> &a) { for (auto &x:a) cin>>x; return cin; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const pair<typC,typD> &a) { return cout<<a.first<<' '<<a.second; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const vector<pair<typC,typD> > &a) { for (auto &x:a) cout<<x<<endl; return cout; }
template<typename typC> ostream &operator<<(ostream &cout,const vector<typC> &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }
// ===================================END Of the input module ==========================================

int ans[1005][1005];
int grid[1005][1005];    

void Solve(){
	int n; cin >> n;
	int flag = n;
	memset(ans, 0, sizeof(ans));
	memset(grid, 0, sizeof(grid));
	vpp idx(n);
	int i = 0;
	while(flag--){
		int x, y; cin >> x >> y;
		idx[i].first = x;
		idx[i].second = y;
		grid[x][y] = 1;
		ans[x][y] = 1;
		i++;
	}

	for(int i = 0; i < 1005; i++){
		for(int j = 0; j < 1005; j++){
			if(i == 0 && j == 0){
				continue;
			}
			if(i == 0){
				ans[i][j] = ans[i][j] + ans[i][j-1];
				continue;
			}
			if(j == 0){
				ans[i][j] = ans[i][j] + ans[i-1][j];
				continue;
			}
			ans[i][j] = max(ans[i][j] + ans[i-1][j], ans[i][j] + ans[i][j-1]);
		}
	}
	if(ans[1004][1004] == n){
		int prevRow = 0;
		int prevCol = 0;
		cout << "YES" << endl;
		string ans = "";
		sort(idx.begin(), idx.end());
		for(int i = 0; i < n; i++){
			if(idx[i].first - prevRow > 0){
				int flag = idx[i].first - prevRow;
				while(flag--){
					ans += 'R';
				}
				prevRow = idx[i].first;
			}
			if(idx[i].second - prevCol > 0){
				int flag = idx[i].second - prevCol;
				while(flag--){
					ans += 'U';
				}
				prevCol = idx[i].second;
			}
		}
		cout << ans << endl;

	}else{
		// for(int i = 0; i < n; i++){
		// 	cout << ans[idx[i].first][idx[i].second] << endl;
		// }
		cout << "NO" << endl;
	}
}

int32_t main (){
    int tc = 1;
    cin >> tc;
    while (tc--){
        Solve();
    }
}
