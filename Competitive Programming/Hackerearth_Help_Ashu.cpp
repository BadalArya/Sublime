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

//--------------------------------------------------------------------------------------------------------------------------------------

template<typename typC,typename typD> istream &operator>>(istream &cin,pair<typC,typD> &a) { return cin>>a.first>>a.second; }
template<typename typC> istream &operator>>(istream &cin,vector<typC> &a) { for (auto &x:a) cin>>x; return cin; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const pair<typC,typD> &a) { return cout<<a.first<<' '<<a.second; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const vector<pair<typC,typD> > &a) { for (auto &x:a) cout<<x<<endl; return cout; }
template<typename typC> ostream &operator<<(ostream &cout,const vector<typC> &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }

//--------------------------------------------------------------------------------------------------------------------------------------

struct node{
	int even = 0;
	int odd = 0;
};

void buildTree(int *arr, node *tree, int start, int end, int treeNode){
	if(start == end){
		if(arr[start] % 2 == 0){
			tree[treeNode].even = 1;
			tree[treeNode].odd = 0;
		}else{
			tree[treeNode].odd = 1;
			tree[treeNode].even = 0;
		}
		return;
	}


	int mid = (start + end) / 2;

	buildTree(arr, tree, start, mid, 2*treeNode);
	buildTree(arr, tree, mid+1, end, 2*treeNode + 1);

	node left = tree[2*treeNode];
	node right = tree[2*treeNode+1];

	tree[treeNode].odd = left.odd + right.odd;
	tree[treeNode].even = left.even + right.even;
}

void updateTree(int *arr, node*tree, int start, int end, int idx, int val, int treeNode){
	if(start == end){
		arr[idx] = val;
		if(arr[idx] % 2 == 0){
			tree[treeNode].even = 1;
			tree[treeNode].odd = 0;
		}else{
			tree[treeNode].odd = 1;
			tree[treeNode].even = 0;

		}
		return;
	}

	int mid = (start + end) / 2;

	if(idx > mid){
		updateTree(arr, tree, mid+1, end, idx, val, 2*treeNode + 1);
	}else{
		updateTree(arr, tree, start, mid, idx, val, 2*treeNode);
	}

	node left = tree[2*treeNode];
	node right = tree[2*treeNode+1];

	tree[treeNode].odd = left.odd + right.odd;
	tree[treeNode].even = left.even + right.even;
}

int queryOdd(node *tree, int start, int end, int left, int right, int treeNode){
	// Completely outside
	if(left > end || right < start){
		return 0;
	}

	// Completely inside
	if(start >= left && end <= right){
		return tree[treeNode].odd;
	}

	// Partially inside or Outside
	
	int mid = (start + end) / 2;
	int ans1 = queryOdd(tree, start, mid, left, right, 2*treeNode);
	int ans2 = queryOdd(tree, mid + 1, end, left, right, 2*treeNode + 1);

	return ans1 + ans2;
}

int queryEven(node *tree, int start, int end, int left, int right, int treeNode){
	// Completely outside
	if(left > end || right < start){
		return 0;
	}

	// Completely inside
	if(start >= left && end <= right){
		return tree[treeNode].even;
	}

	// Partially inside or Outside
	
	int mid = (start + end) / 2;
	int ans1 = queryEven(tree, start, mid, left, right, 2*treeNode);
	int ans2 = queryEven(tree, mid + 1, end, left, right, 2*treeNode + 1);

	return ans1 + ans2;
}

void Solve(){
    int n; cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
    	cin >> a[i];
    }

    node tree[4*n];

    buildTree(a, tree, 0, n - 1, 1);

    int q; cin >> q;

    while(q--){
    	int operation, x, y; cin >> operation >> x >> y;
    	if(operation == 0){
    		updateTree(a, tree, 0, n - 1, x - 1, y, 1);
    	}else if(operation == 1){
    		cout << queryEven(tree, 0, n -1, x - 1, y - 1, 1) << endl;
    	}else{
    		cout << queryOdd(tree, 0, n - 1, x - 1, y - 1, 1) << endl;
    	}
    }
}

int32_t main (){
    Badal;
    int tc = 1;
    // cin >> tc;
    while (tc--){
        Solve();
    }
}
