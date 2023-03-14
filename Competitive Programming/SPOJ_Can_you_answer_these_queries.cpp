#include <bits/stdc++.h>
using namespace std;

void buildTree(int *arr, int *tree, int start, int end, int treeNode){
	if(start == end){
		tree[treeNode] = arr[start];
		return;
	}

	int mid = (start + end) / 2;
	buildTree(arr, tree, start, mid, 2*treeNode);
	buildTree(arr, tree, mid+1, end, 2*treeNode+1);

	if(tree[2*treeNode] >= 0 && tree[2*treeNode+1] >= 0){
		tree[treeNode] = tree[2*treeNode] + tree[2*treeNode+1];
	}else{
		tree[treeNode] = max(tree[2*treeNode], tree[2*treeNode+1]);
	}
}

int query(int *tree, int start, int end, int treeNode, int left, int right){
	// Completely outside
	if(start > right || end < left){
		return INT_MIN;
	}

	// Completely inside
	if(start >= left && end <= right){
		return tree[treeNode];
	}

	// Partially Inside or Outside
	int mid = (start+end) / 2;
	int ans1 = query(tree, start, mid, 2*treeNode, left, right);
	int ans2 = query(tree, mid+1, end, 2*treeNode+1, left, right);

	if(ans1 >= 0 && ans2 >= 0){
		return ans1 + ans2;
	}else{
		return max(ans1, ans2);
	}
}

int main(){
	int n; cin >> n;
	int arr[n];
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}

	int tree[3*n];
	buildTree(arr, tree, 0, n-1, 1);

	int k; cin >> k;
	while(k--){
		int left, right;
		cin >> left >> right;
		cout << query(tree, 0, n-1, 1, left-1, right-1) << endl;
	}
}