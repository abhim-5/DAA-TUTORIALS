#include <bits/stdc++.h>
using namespace std;

// A point in 2D plane
struct Point {
    int x, y;
};

// To find orientation of ordered triplet (p, q, r).
// Returns: 0 → collinear, 1 → clockwise, 2 → counter-clockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;           // collinear
    return (val > 0) ? 1 : 2;         // 1=clockwise, 2=counter-clockwise
}

// Distance squared between two points
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}

Point p0; // global starting point

// Compare function for sorting points by polar angle w.r.t p0
bool compare(Point p1, Point p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) 
        return distSq(p0, p1) < distSq(p0, p2);
    return (o == 2); // keep counter-clockwise first
}

// Convex Hull function using Graham Scan
void convexHull(vector<Point>& points, int n) {
    // Step 1: Find the lowest y point (if tie, leftmost x)
    int ymin = points[0].y, minIndex = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || 
            (points[i].y == ymin && points[i].x < points[minIndex].x)) {
            ymin = points[i].y;
            minIndex = i;
        }
    }
    swap(points[0], points[minIndex]);
    p0 = points[0];

    // Step 2: Sort remaining points by polar angle w.r.t p0
    sort(points.begin() + 1, points.end(), compare);

    // Step 3: If collinear points at the end, keep farthest
    vector<Point> uniquePoints;
    uniquePoints.push_back(points[0]);
    for (int i = 1; i < n; i++) {
        while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0)
            i++;
        uniquePoints.push_back(points[i]);
    }

    // Step 4: If less than 3 points, convex hull not possible
    if (uniquePoints.size() < 3) {
        cout << "Convex hull not possible\n";
        return;
    }

    // Step 5: Create stack and process points
    stack<Point> hull;
    hull.push(uniquePoints[0]);
    hull.push(uniquePoints[1]);
    hull.push(uniquePoints[2]);

    for (int i = 3; i < (int)uniquePoints.size(); i++) {
        // Pop while top two and current point do not make a counterclockwise turn
        while (hull.size() > 1) {
            Point top = hull.top(); hull.pop();
            Point nextTop = hull.top();
            if (orientation(nextTop, top, uniquePoints[i]) == 2) {
                hull.push(top);
                break;
            }
        }
        hull.push(uniquePoints[i]);
    }

    // Step 6: Print result
    vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }
    reverse(result.begin(), result.end());

    cout << "Convex Hull points are:\n";
    for (auto p : result)
        cout << "(" << p.x << ", " << p.y << ")\n";
}

int main() {
    int n;
    cout << "Enter number of points: ";
    cin >> n;

    vector<Point> points(n);
    cout << "Enter the points (x y):\n";
    for (int i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y;

    convexHull(points, n);

    return 0;
}