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
#define uint unsigned long long
#define int long long int
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
const int N = 200200;
int arr[N];
int tree[4 * N];
int lazy[4 * N];


void buildTree(int start, int end, int treeNode){
	if(start == end){
		tree[treeNode] = arr[start];
		return;
	}

	int mid = (start + end) / 2;

	buildTree(start, mid, 2 * treeNode);
	buildTree(mid + 1, end, 2 * treeNode + 1);

	tree[treeNode] = min(tree[2 * treeNode], tree[2 * treeNode + 1]);
}

void updateTree(int start, int end, int left, int right, int val, int treeNode){
	if(start > end){
		return;
	}

	if(lazy[treeNode] != 0){
		tree[treeNode] += lazy[treeNode];

		if(start != end){
			lazy[2 * treeNode] += lazy[treeNode];
			lazy[2 * treeNode + 1] += lazy[treeNode];
		}

		lazy[treeNode] = 0;
	}

	if(left > end || right < start){
		return ;
	}

	if(start >= left && end <= right){
		tree[treeNode] += val;
		if(start != end){
			lazy[2 * treeNode] += val;
			lazy[2 * treeNode + 1] += val;
		}
		return;
	}

	int mid = (start + end) / 2;

	updateTree(start, mid, left, right, val, 2 * treeNode);
	updateTree(mid + 1, end, left, right, val, 2 * treeNode + 1);

	tree[treeNode] = min (tree[2 *treeNode], tree[2 * treeNode + 1]);
}

int query(int start, int end, int left, int right, int treeNode){
	if(left > end || right < start){
		return INT_MAX;
	}

	if(lazy[treeNode] != 0){
		tree[treeNode] += lazy[treeNode];

		if(start != end){
			lazy[2 * treeNode] += lazy[treeNode];
			lazy[2 * treeNode + 1] += lazy[treeNode];
		}

		lazy[treeNode] = 0;
	}

	if(start >= left && end <= right){
		return tree[treeNode];
	}

	int mid = (start + end) / 2;

	int ans1 = query(start, mid, left, right, 2 * treeNode);
	int ans2 = query(mid + 1, end, left, right,  2 * treeNode + 1);

	return min(ans1, ans2);
}

void Solve(){	
    int n; cin >> n;

    for(int i = 0; i < n; i++){
    	cin >> arr[i];
    }

    // Let's build the segment tree
    buildTree(0, n - 1, 1);

    int q; cin >> q;
    while(q--){
    	int left, right, val;
    	cin >> left >> right;
    	char c;
    	// cout << left << " " << right;
    	c = cin.get();
    	if(c == ' '){
    		cin >> val;
    		if(left > right){
    			// right = n + right;
	    		updateTree(0, n - 1, left, n-1, val, 1);
	    		updateTree(0, n - 1, 0, right, val, 1);
    		}else{
    			updateTree(0, n - 1, left, right, val, 1);
    		}
    	}else{
    		int flag1 = INT_MAX;
    		int flag2 = INT_MAX;
    		// cout << left << " " << right << " ";
    		if(right < left){
    			flag1 = query(0, n - 1, left, n - 1, 1);
    			flag2 = query(0, n - 1, 0, right, 1);
    			cout << min(flag1, flag2) << endl;
    		}else{
	    		cout << query(0, n - 1, left, right, 1) << endl;
    		}
    	}
    }
}

int32_t main (){
    Badal;
    int tc = 1;
    while (tc--){
        Solve();
    }
}
