#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> events;
    for (auto& b : buildings) {
        // entering building → height negative
        events.push_back({b[0], -b[2]});
        // leaving building → height positive
        events.push_back({b[1], b[2]});
    }

    // sort events: by x, then height
    sort(events.begin(), events.end());

    multiset<int> heights = {0}; // current active heights
    int prevMax = 0;
    vector<vector<int>> ans;

    for (auto& e : events) {
        int x = e.first, h = e.second;

        if (h < 0) {
            // building enters
            heights.insert(-h);
        } else {
            // building exits
            heights.erase(heights.find(h));
        }

        int currMax = *heights.rbegin();
        if (currMax != prevMax) {
            ans.push_back({x, currMax});
            prevMax = currMax;
        }
    }
    return ans;
}

int main() {
    int n;
    cout << "Enter number of buildings: ";
    cin >> n;

    vector<vector<int>> buildings(n, vector<int>(3));
    cout << "Enter each building as three integers: Left Right Height\n";
    cout << "Example: 1 5 11 means building starts at 1, ends at 5, height 11\n";

    for (int i = 0; i < n; i++) {
        cout << "Building " << i + 1 << ": ";
        cin >> buildings[i][0] >> buildings[i][1] >> buildings[i][2];
    }

    vector<vector<int>> ans = getSkyline(buildings);

    cout << "\nSkyline formed is:\n";

    //   for (auto [x, h] : ans) {
    //     cout << "(" << x << "," << h << ") ";
    // }

    for (auto& p : ans) {
        cout << "[" << p[0] << ", " << p[1] << "] ";
    }
    cout << endl;

    return 0;
}
