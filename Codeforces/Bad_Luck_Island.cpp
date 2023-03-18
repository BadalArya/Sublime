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

int gcd (int a, int b) { return a ? gcd (b % a, a) : b; }

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

double dp[105][105][105];

double solveRock(int r, int s, int p){
	// If no rocks are left then probablity of winning rock is zero
	// If no scissors are left then match will be of rock and paper
	// And paper will win for sure and rock will loose

	if(r == 0 || s == 0){
		return 0.0;
	}

	// If paper's over, rock's winner
	if(p == 0){
		return 1.0;
	}

	if(dp[r][s][p] > -1.0){
		return dp[r][s][p];
	}

	double total = (r*s) + (r*p) + (s*p);

	double ans1 = (r*p) / total * solveRock(r - 1, s, p); // Rock, paper match && rock looses
	double ans2 = (r*s) / total * solveRock(r, s - 1, p); // Rock, scissor match && scissor looses
	double ans3 = (s*p) / total * solveRock(r, s, p - 1); // Scissor, paper match && paper looses

	return dp[r][s][p] = ans1 + ans2 + ans3;
}

double solveScissor(int r, int s, int p){
	// If no rocks are left then probablity of winning rock is zero
	// If no scissors are left then match will be of rock and paper
	// And paper will win for sure and rock will loose

	if(p == 0 || s == 0){
		return 0.0;
	}

	// If paper's over, rock's winner
	if(r == 0){
		return 1.0;
	}

	if(dp[r][s][p] > -1.0){
		return dp[r][s][p];
	}

	double total = (r*s) + (r*p) + (s*p);

	double ans1 = (r*p) / total * solveScissor(r - 1, s, p); // Rock, paper match && rock looses
	double ans2 = (r*s) / total * solveScissor(r, s - 1, p); // Rock, scissor match && scissor looses
	double ans3 = (s*p) / total * solveScissor(r, s, p - 1); // Scissor, paper match && paper looses

	return dp[r][s][p] = ans1 + ans2 + ans3;
}

double solvePaper(int r, int s, int p){
	// If no rocks are left then probablity of winning rock is zero
	// If no scissors are left then match will be of rock and paper
	// And paper will win for sure and rock will loose

	if(p == 0 || r == 0){
		return 0.0;
	}

	// If paper's over, rock's winner
	if(s == 0){
		return 1.0;
	}

	if(dp[r][s][p] > -1.0){
		return dp[r][s][p];
	}

	double total = (r*s) + (r*p) + (s*p);

	double ans1 = (r*p) / total * solvePaper(r - 1, s, p); // Rock, paper match && rock looses
	double ans2 = (r*s) / total * solvePaper(r, s - 1, p); // Rock, scissor match && scissor looses
	double ans3 = (s*p) / total * solvePaper(r, s, p - 1); // Scissor, paper match && paper looses

	return dp[r][s][p] = ans1 + ans2 + ans3;
}

void Solve(){
	int r, s, p; cin >> r >> s >> p;

	cout << fixed << setprecision(12);

	memset(dp, -1, sizeof(dp));
	cout << solveRock(r, s, p) << " ";

	memset(dp, -1, sizeof(dp));
	cout << solveScissor(r, s, p) << " ";

	memset(dp, -1, sizeof(dp));
	cout << solvePaper(r, s, p) << endl;
}

int32_t main (){
    Badal;
    int tc = 1;
    // cin >> tc;
    while (tc--){
        Solve();
    }
}
