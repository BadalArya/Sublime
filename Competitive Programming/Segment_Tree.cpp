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
	tree[treeNode] = tree[2*treeNode] + tree[2*treeNode + 1];
}

void updateTree(int *arr, int *tree, int start, int end, int idx, int val, int treeNode){
	if(start == end){
		arr[end] = val;
		tree[treeNode] = val;
		return;
	}
	int mid = (start + end) / 2;
	if(idx > mid){
		updateTree(arr, tree, mid+1, end, idx, val, 2*treeNode+1);
	}else{
		updateTree(arr, tree, start, mid, idx, val, 2*treeNode);
	}
	tree[treeNode] = tree[2*treeNode] + tree[2*treeNode+1];
}

int query(int *tree, int start, int end, int treeNode, int left, int right){

	// Completely outside the given range

	if(start > right || end < left){
		return 0;
	}

	// Completely inside the given range

	if(start >= left && end <= right){
		return tree[treeNode];
	}

	// Partially inside and outise the given range

	int mid = (start + mid) / 2;
	int ans1 = query(tree, start, mid, 2*treeNode, left, right);
	int ans2 = query(tree, mid+1, end, 2*treeNode+1, left, right);

	return ans1 + ans2;

}

int main(){
	int arr[] = {1, 2, 3, 4, 5};
	int* tree = new int[10];

	buildTree(arr, tree, 0, 4, 1);

	for(int i = 1; i < 10; i++){
		cout << tree[i] << " ";
	}
	cout << endl;

	updateTree(arr, tree, 0, 4, 2, 10, 1);

	for(int i = 1; i < 10; i++){
		cout << tree[i] << " ";
	}
}