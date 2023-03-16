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

void buildTree(int *arr, int *tree, int start, int end, int treeNode){
	if(start == end){
		tree[treeNode] = arr[start];
		return;
	}

	int mid = (start + end) / 2;
	buildTree(arr, tree, start, mid, 2 * treeNode);
	buildTree(arr, tree, mid + 1, end, 2 * treeNode + 1);

	tree[treeNode] = tree[2 * treeNode] + tree[2 * treeNode + 1];
}

void updateTree(int *tree, int *lazy, int start, int end, int left, int right, int val, int treeNode){
	if(start > end){
		return;
	}

	if(lazy[treeNode] != 0){
		int sum = end - start + 1;
		int value = lazy[treeNode];
		sum *= value;

		tree[treeNode] += sum;

		if(start != end){
			lazy[2 * treeNode] += value;
			lazy[2 * treeNode + 1] += value;
		}
		lazy[treeNode] = 0;
	}

	if(left > end || right < start){
		return;
	}

	if(start >= left && end <= right){
		int sum = end - start + 1;
		sum *= val;
		tree[treeNode] += sum;

		if(start != end){
			lazy[2 * treeNode] += val;
			lazy[2 * treeNode + 1] += val;
		}

		return;
	}

	int mid = (start + end) / 2;

	updateTree(tree, lazy, start, mid, left, right, val, 2 * treeNode);
	updateTree(tree, lazy, mid + 1, end, left, right, val, 2 * treeNode + 1);

	tree[treeNode] = tree[2 * treeNode] + tree[2 * treeNode + 1];
}

int query(int * tree, int *lazy, int start, int end, int left, int right, int treeNode){
	if(left > end || right < start){
		return 0;
	}

	if(lazy[treeNode] != 0){
		int sum = end - start + 1;
		int val = lazy[treeNode];
		sum *= val;
		tree[treeNode] += sum;

		if(start != end){
			lazy[2 * treeNode] += val;
			lazy[2 * treeNode + 1] += val;
		}
		lazy[treeNode] = 0;
	}

	if(start >= left && end <= right){
		return tree[treeNode];
	}

	int mid = (start + end) / 2;

	int ans1 = query(tree, lazy, start, mid, left, right, 2 * treeNode);
	int ans2 = query(tree, lazy, mid + 1, end, left, right, 2 * treeNode + 1);

	return ans1 + ans2;
}

void Solve(){
	int n; cin >> n;
	int k; cin >> k;

	int a[n];
	for(int i = 0 ; i < n; i++){
		cin >> a[i];
	}    

	int tree[4 * n] = {0};
	int lazy[4 * n] = {0};

	buildTree(a, tree, 0 , n - 1, 1);

	for(int i = 0; i < k; i++){
		int type; cin >> type;
		if(type == 1){
			int left, right, value;
			cin >> left >> right >> value;
			updateTree(tree, lazy, 0, n - 1, left - 1, right - 1, value, 1);
		}else{
			int pos; cin >> pos;
			cout << query(tree, lazy, 0 , n - 1, pos - 1, pos - 1, 1) << endl;
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
