#include "Floyd_Warshall_Algorithm.h"

int main() {

    int number_of_vertices, number_of_edges;
    cin >> number_of_vertices >> number_of_edges;


    vector<vector<int>> cost = Solution::buildAdjMatrix(number_of_vertices, number_of_edges);

    int n = cost.size();

    vector<vector<int>> path(n, vector<int>(n));
    Solution::setPath(path, cost, n); //build a default path according to adjacency matrix (cost matrix)

    Solution::floydWarshall(cost, path, n);
    cout << endl;
    Solution::showPath(cost,path,1,2);
    return 0;
}