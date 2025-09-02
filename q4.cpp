#include <bits/stdc++.h>
using namespace std;

int findPeakElement(vector<int>& A) {
    int n = A.size();
    
    // Edge cases
    if (n == 1) return 0;
    if (A[0] >= A[1]) return 0;
    if (A[n - 1] >= A[n - 2]) return n - 1;

    int low = 1, high = n - 2; // search only in middle part

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if A[mid] is a peak
        if (A[mid] >= A[mid - 1] && A[mid] >= A[mid + 1]) {
            return mid;
        }
        // If left neighbor is greater, move left
        else if (A[mid - 1] > A[mid]) {
            high = mid - 1;
        }
        // Otherwise, move right
        else {
            low = mid + 1;
        }
    }

    return -1; // should never happen
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> A(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int peakIndex = findPeakElement(A);
    cout << "Peak index: " << peakIndex 
         << " (value: " << A[peakIndex] << ")" << endl;

    return 0;
}
