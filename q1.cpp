#include <bits/stdc++.h>
using namespace std;

// Function to merge two halves and count inversions
long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    long long invCount = 0;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
            invCount += (leftArr.size() - i); // count inversions
        }
    }

    // Copy remaining elements
    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];

    return invCount;
}

// Recursive function
long long mergeSortAndCount(vector<int>& arr, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long invCount = 0;

    invCount += mergeSortAndCount(arr, left, mid);
    invCount += mergeSortAndCount(arr, mid + 1, right);
    invCount += mergeAndCount(arr, left, mid, right);

    return invCount;
}

int main() {
    int n;
    cout<<"Enter size of array: ";
    cin>>n;
    cout<<"Enter elements : "<<endl;
    vector<int> arr(n);
    for(int i=0;i<n;i++) 
        cin>>arr[i];

    

    long long result = mergeSortAndCount(arr, 0, n - 1);

    cout << "Number of inversions = " << result << endl;
    return 0;
}