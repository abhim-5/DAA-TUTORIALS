#include <bits/stdc++.h>
using namespace std;

// Partition function for dual-pivot quicksort
int partition(vector<int>& arr, int low, int high, int& lp) {
    if (arr[low] > arr[high])
        swap(arr[low], arr[high]);

    int p = arr[low];   // left pivot
    int q = arr[high];  // right pivot

    int i = low + 1;
    int j = high - 1;
    int k = i;

    while (k <= j) {
        if (arr[k] < p) {                // belongs to left part
            swap(arr[k], arr[i]);
            i++;
        }
        else if (arr[k] >= q) {          // belongs to right part
            while (arr[j] > q && k < j) j--;
            swap(arr[k], arr[j]);
            j--;
            if (arr[k] < p) {
                swap(arr[k], arr[i]);
                i++;
            }
        }
        k++;
    }

    // Place pivots in correct position
    i--; j++;
    swap(arr[low], arr[i]);
    swap(arr[high], arr[j]);

    lp = i;  // left pivot index
    return j; // right pivot index
}

// Dual pivot quicksort recursive function
void dualPivotQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int lp, rp;
        rp = partition(arr, low, high, lp);

        dualPivotQuickSort(arr, low, lp - 1);    // left part
        dualPivotQuickSort(arr, lp + 1, rp - 1); // middle part
        dualPivotQuickSort(arr, rp + 1, high);   // right part
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    dualPivotQuickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
