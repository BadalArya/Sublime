#include <bits/stdc++.h>
using namespace std;

struct node{
	int maximum;
	int smaximum;
};

void buildTree(int *arr, node *tree, int start, int end, int treeNode){
	if(start == end){
		tree[treeNode].maximum = arr[end];
		tree[treeNode].smaximum = INT_MIN;
		return;
	}

	int mid = (start + end) / 2;
	buildTree(arr, tree, start, mid, 2*treeNode);
	buildTree(arr, tree, mid+1, end, 2*treeNode+1);

	node left = tree[2*treeNode];
	node right = tree[2*treeNode+1];

	tree[treeNode].maximum = max(left.maximum, right.maximum);
	tree[treeNode].smaximum = min(max(left.maximum, right.smaximum), max(right.maximum, left.smaximum));

}

void updateTree(int *arr, node *tree, int start, int end, int idx, int val, int treeNode){
	if(start == end){
		arr[idx] = val;
		tree[treeNode].maximum = val;
		tree[treeNode].smaximum = INT_MIN;
		return;
	}

	int mid = (start + end) / 2;
	if(idx > mid){
		updateTree(arr, tree, mid+1, end, idx, val, 2*treeNode+1);
	}else{
		updateTree(arr, tree, start, mid, idx, val, 2*treeNode);
	}

	node left = tree[2*treeNode];
	node right = tree[2*treeNode+1];

	tree[treeNode].maximum = max(left.maximum, right.maximum);
	tree[treeNode].smaximum = min(max(left.maximum, right.smaximum), max(right.maximum, left.smaximum));
}

node query(node *tree, int start, int end, int treeNode, int left, int right){
	// Completely outside

	if(left > end || right < start){
		node flag;
		flag.maximum = INT_MIN;
		flag.smaximum = INT_MIN;
		return flag;
	}

	// Completely inside
	if(start >= left && end <= right){
		return tree[treeNode];
	}

	//Partially inside or outside
	int mid = (start + end) / 2;
	node ans1 = query(tree, start, mid, 2*treeNode, left, right);
	node ans2 = query(tree, mid+1, end, 2*treeNode+1, left, right);
	
	node ans;
	ans.maximum = max(ans1.maximum, ans2.maximum);
	ans.smaximum = min(max(ans1.maximum, ans2.smaximum), max(ans2.maximum, ans1.smaximum));
	return ans;
}

int main(){
	int n; cin >> n;
	int arr[n];
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}

	node tree[3*n];
	buildTree(arr, tree, 0, n-1, 1);

	int operations; cin >> operations;
	char ch;
	int x, y;
	while(operations--){
		cin >> ch;
		cin >> x >> y;
		if(ch == 'U'){
			updateTree(arr, tree, 0, n-1, x-1, y, 1);
		}else{
			node ans = query(tree, 0, n-1, 1, x-1, y-1);
			cout << ans.maximum + ans.smaximum << endl;
		}
	}
}