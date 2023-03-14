#include <bits/stdc++.h>
using namespace std;

struct node{
	int maximum = INT_MAX;
	int minimum = INT_MAX;
};

void buildTree(int *arr, node *tree, int start, int end, int treeNode){
	if(start == end){
		tree[treeNode].maximum = arr[start];
		tree[treeNode].minimum = arr[start];
		return;
	}

	int mid = (start + end) / 2;
	buildTree(arr, tree, start, mid, 2*treeNode);
	buildTree(arr, tree, mid+1, end, 2*treeNode+1);

	node left = tree[2*treeNode];
	node right = tree[2*treeNode+1];

	tree[treeNode].maximum = max(left.maximum, right.maximum);
	tree[treeNode].minimum = min(left.minimum, right.minimum);
}

int countSubarrays(vector<int> nums, int left, int right){
	int n = nums.size();
	int arr[n];
	for(int i = 0; i < n; i++){
		arr[i] = nums[i];
	}
	node tree[3*n];
	buildTree(arr, tree, 0, n-1, 1);

	int ans = 0;
	for(int i = 0; i < 3*n; i++){
		if(tree[i].minimum >= left && tree[i].maximum <= right){
			ans++;
		}
	}
	for(int i = 0; i < 3*n; i++){
		cout << tree[i].maximum << " " << tree[i].minimum << endl;
	}
	return ans;
}

int main(){
	int n; cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++){
		cin >> v[i];
	}
	int left, right;
	cin >> left >> right;
	cout << countSubarrays(v, left, right) << endl;
}