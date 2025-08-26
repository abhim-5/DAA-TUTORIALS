#include <bits/stdc++.h>
using namespace std;

// Get median of a small group (≤ 5 elements)
int getMedian(vector<int>& arr, int l, int r) {
    sort(arr.begin() + l, arr.begin() + r + 1);
    return arr[l + (r - l) / 2];  // middle element
}

// Partition the array around pivot value
int partition(vector<int>& arr, int l, int r, int pivot) {
    // Find pivot index
    int pivotIndex;
    for (pivotIndex = l; pivotIndex <= r; pivotIndex++)
        if (arr[pivotIndex] == pivot) break;

    swap(arr[pivotIndex], arr[r]); // move pivot to end

    int i = l;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]); // move pivot to final position
    return i;
}

// Recursively find k-th smallest element
int kthSmallest(vector<int>& arr, int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int n = r - l + 1; // size of subarray

        // Step 1: Divide into groups of 5 & find medians
        vector<int> medians;
        int i;
        for (i = 0; i < n / 5; i++) {
            medians.push_back(getMedian(arr, l + i * 5, l + i * 5 + 4));
        }
        if (i * 5 < n) {
            medians.push_back(getMedian(arr, l + i * 5, l + i * 5 + (n % 5) - 1));
        }

        // Step 2: Find median of medians
        int medOfMed;
        if (medians.size() == 1)
            medOfMed = medians[0];
        else
            medOfMed = kthSmallest(medians, 0, medians.size() - 1, (medians.size() + 1) / 2);

        // Step 3: Partition around median of medians
        int pos = partition(arr, l, r, medOfMed);

        // Step 4: Check position
        int rank = pos - l + 1;  // rank of pivot in current subarray
        if (rank == k)
            return arr[pos];
        else if (rank > k)
            return kthSmallest(arr, l, pos - 1, k);
        else
            return kthSmallest(arr, pos + 1, r, k - rank);
    }
    return INT_MAX; // k is out of bounds
}


int main() {
    int m,k;
    cout<<"Enter size of array: ";
    cin>>m;
    cout<<"Enter elements : "<<endl;
    vector<int> arr(m);
    for(int i=0;i<m;i++) 
        cin>>arr[i];
    cout<<"Enter k: ";
    cin>>k; 
    cout << k << "-th smallest element is " 
         << kthSmallest(arr, 0, arr.size() - 1, k) << endl;
    return 0;
}