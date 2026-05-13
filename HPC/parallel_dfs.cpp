#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX = 100;

vector<int> graph[MAX];

bool visited[MAX];

// Parallel DFS
void dfs(int start)
{
    stack<int> s;

    s.push(start);

    while(!s.empty())
    {
        int curr = s.top();
        s.pop();

        if(!visited[curr])
        {
            visited[curr] = true;

            cout << curr << " ";

            #pragma omp parallel for
            for(int i = 0; i < graph[curr].size(); i++)
            {
                int adj = graph[curr][i];

                if(!visited[adj])
                {
                    #pragma omp critical
                    {
                        s.push(adj);
                    }
                }
            }
        }
    }
}

int main()
{
    int n, m, start;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    cout << "Enter starting node: ";
    cin >> start;

    cout << "\nEnter edges:\n";

    for(int i = 0; i < m; i++)
    {
        int u, v;

        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Initialize visited array
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    cout << "\nDFS Traversal:\n";

    dfs(start);

    return 0;
}