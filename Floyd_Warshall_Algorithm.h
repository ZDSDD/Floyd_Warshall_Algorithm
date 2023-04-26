//
// Created by User on 26.04.2023.
//

#ifndef FLOYD_WARSHALL_ALGORITHM_FLOYD_WARSHALL_ALGORITHM_H
#define FLOYD_WARSHALL_ALGORITHM_FLOYD_WARSHALL_ALGORITHM_H

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

// define infinity
const int inf = INT_MAX;

using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Solution {
private:
// Recursive function to print path of given vertex `to` from source vertex `from`
    static void printPath(vector<vector<int>> const &path, int from, int to) {
        if (path[from][to] == from) {
            return;
        }
        printPath(path, from, path[from][to]);
        cout << path[from][to] << ", ";
    }

public:
    static void showPath(vector<vector<int>> const &cost, vector<vector<int>> const &path, int from, int to) {
        if (from == to) {
            cout << "Two point are the same, there is no path";
            return;
        }
        if (path[from][to] == -1) {
            cout << "There is no path from " << from << " —> " << to << endl;
            return;
        }

        cout << "The shortest path from " << from << " —> " << to << " is ["
             << from << ", ";
        printPath(path, from, to);
        cout << to << "]" << " and it costs: " << cost[from][to] << endl;

    }

    //utility function to manually build adjacency matrix
    static vector<vector<int>> buildAdjMatrix(int vertices, int edges) {
        vector<vector<int>> out(vertices, vector<int>(vertices, inf));
        for (int i = 0; i < vertices; i++) {
            out[i][i] = 0;
        }
        for (int i = 0; i < edges; i++) {
            int source, destination, edge_weight;
            cin >> source >> destination >> edge_weight;
            out[source][destination] = edge_weight;
        }
        return out;
    }

//utility function to set up path matrix
    static void setPath(vector<vector<int>> &path, vector<vector<int>> const &cost, int n) {
        for (int v = 0; v < n; v++) {
            for (int u = 0; u < n; u++) {
                if (v == u) {
                    path[v][u] = 0;
                } else if (cost[v][u] != INT_MAX) {
                    path[v][u] = v;
                } else {
                    path[v][u] = -1;
                }
            }
        }
    }

//utility function
    static void printMatrix(vector<vector<int>> const &matrix) {
        for (const auto &item: matrix) {
            for (const auto &item2: item) {
                if (item2 != inf)
                    cout << item2 << '\t';
                else
                    cout << "I\t";
            }
            cout << endl;
        }
        cout << endl;
    }


// Function to print the shortest cost with path information between
// all pairs of vertices
    static void printSolution(vector<vector<int>> const &cost, vector<vector<int>> const &path, int n) {
        for (int v = 0; v < n; v++) {
            for (int u = 0; u < n; u++) {
                if (path[v][u] == -1) {
                    cout << "There is no path from " << v << " —> " << u << endl;
                } else if (u != v) {
                    cout << "The shortest path from " << v << " —> " << u << " is ["
                         << v << ", ";
                    printPath(path, v, u);
                    cout << u << "]" << " and it costs: " << cost[v][u] << endl;
                }
            }
        }
    }

// Function to run the Floyd–Warshall algorithm
    static void floydWarshall(vector<vector<int>> &cost, vector<vector<int>> &path, int n) {
        if (n == 0) {
            return;
        }
        for (int k = 0; k < n; k++) {
            for (int v = 0; v < n; v++) {
                for (int u = 0; u < n; u++) {
                    // If vertex `k` is on the shortest path from `v` to `u`,
                    // then update the value of cost[v][u] and path[v][u]

                    if (cost[v][k] != INT_MAX && cost[k][u] != INT_MAX
                        && cost[v][k] + cost[k][u] < cost[v][u]) {
                        cost[v][u] = cost[v][k] + cost[k][u];
                        path[v][u] = path[k][u];
                    }
                }

                // if diagonal elements become negative, the
                // graph contains a negative-weight cycle
                if (cost[v][v] < 0) {
                    cout << "Negative-weight cycle found!!";
                    return;
                }
            }
        }

        // Print the shortest path between all pairs of vertices
        printSolution(cost, path, n);
        // Print 2d matrix for both cost and path
        printMatrix(cost);
        printMatrix(path);
    }
};


#endif //FLOYD_WARSHALL_ALGORITHM_FLOYD_WARSHALL_ALGORITHM_H
