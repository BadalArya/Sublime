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

struct node{
	char letter = '\0';
	int freq[26] = {0};
};

const int N = 100010;

node tree[4*N + 100];

string s;

void buildTree(int start, int end, int treeNode){
	if(start == end){
		tree[treeNode].letter = s[start];
		tree[treeNode].freq[s[start] - 'A'] = 1;
		return;
	}

	int mid = (start + end) / 2;

	buildTree(start, mid, 2*treeNode);
	buildTree(mid+1, end, 2*treeNode + 1);

	node left = tree[2*treeNode];
	node right = tree[2*treeNode + 1];
	node check;
	for(int i = 0; i < 26; i++){
		check.freq[i] = left.freq[i] + right.freq[i];
	}

	tree[treeNode] = check;
}

void updateTree(int start, int end, int idx, char ch, int treeNode){
	if(start == end){
		char prev = tree[treeNode].letter;
		tree[treeNode].letter = ch;
		tree[treeNode].freq[prev - 'A'] = 0;
		tree[treeNode].freq[ch - 'A'] = 1;
		return;
	}


	int mid = (start + end) / 2;
	if(idx > mid){
		updateTree(mid + 1, end, idx, ch, 2 * treeNode + 1);		
	}else{
		updateTree(start, mid, idx, ch, 2 * treeNode);		
	}

	node left = tree[2*treeNode];
	node right = tree[2*treeNode + 1];
	node check;
	for(int i = 0; i < 26; i++){
		check.freq[i] = left.freq[i] + right.freq[i];
	}

	tree[treeNode] = check;
}

node query(int start, int end, int left, int right, int treeNode){
	// Completely outside

	if(left > end || right < start){
		node flag;
		return flag;
	}

	// Completely inside 

	if(start >= left && end <= right){
		return tree[treeNode];
	}

	// Partially inside or outside

	int mid = (start + end) / 2;

	node ans1 = query(start, mid, left, right, 2 * treeNode);
	node ans2 = query(mid + 1, end, left, right, 2 * treeNode + 1);

	node ans;
	for(int i = 0; i < 26; i++){
		ans.freq[i] = ans1.freq[i] + ans2.freq[i];
	}

	return ans;
}

int casse = 1;

void Solve(){
	cout << "Case #" << casse++ << ":" <<  endl;
	cin >> s;
	int n = s.size();

	memset(tree, 0, sizeof(tree));

	buildTree(0, n - 1, 1);

	int q; cin >> q;
	while(q--){
		char ch; cin >> ch;
		if(ch == 's'){
			int l, r; cin >> l >> r;
			sort(s.begin() + l, s.begin() + r + 1);
			for(int i = l; i <= r; i++){
				updateTree(0, n - 1, i, s[i], 1);
			}
		}else{
			int l, r; cin >> l >> r;

			node Node = query(0, s.size() - 1, l, r, 1);
                for(int i = 0; i < 26; i++) 
                    printf("%d%c", Node.freq[i], (i == 25) ? '\n' : ' ');
		}
	}
}

int32_t main (){
    int tc = 1;
    cin >> tc;
    while (tc--){
        Solve();
    }
}
