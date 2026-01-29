# Technical Documentation: Algorithm Analysis

## 1. Algorithm Overview
[cite_start]The core routing engine of the Flight Reservation System utilizes **Breadth-First Search (BFS)** to determine optimal routes between cities[cite: 35, 43].

* **Class:** `RouteGraph`
* **Method:** `findShortestPath(const string& start, const string& end)`
* **Graph Representation:** Adjacency List (`std::map<string, std::list<pair<string, double>>>`)

## 2. Time Complexity Analysis
The time complexity of the route calculation is **$O(V + E)$**, where:
* **$V$ (Vertices):** The number of cities in the network (e.g., Lahore, Karachi, Dubai).
* **$E$ (Edges):** The number of flight routes connecting these cities.

### Detailed Breakdown
The BFS algorithm functions by exploring the graph layer-by-layer. The complexity is derived from two main operations:

#### A. Vertex Processing ($O(V)$)
In the `while (!q.empty())` loop, every city (vertex) is:
1.  Enqueued exactly once (when first discovered).
2.  Dequeued exactly once (when processed).
3.  Checked against the `visited` map.

Since each operation is constant time (ignoring map overhead for a moment), processing all vertices takes time proportional to the number of cities: **$O(V)$**.

#### B. Edge Traversal ($O(E)$)
Inside the loop, we iterate through the adjacency list of the current city:
```cpp
for (const auto& neighbor : adjList[current]) { ... }