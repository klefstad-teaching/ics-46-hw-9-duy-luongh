#include <algorithm>
#include "dijkstras.h"

struct Node
{
    int vertex;
    int weight;

    Node(int v, int w) : vertex(v), weight(w) {}
};

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous)
{
    int n = G.numVertices;
    vector<int> distance;
    vector<int> visited;

    distance.resize(n, INF);
    previous.resize(n, -1);
    visited.resize(n, false);

    auto cmp = [](const Node &u, const Node &v)
    { return u.weight > v.weight; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    pq.push(Node(source, 0));
    distance[source] = 0;

    while (!pq.empty())
    {
        int u = pq.top().vertex;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        for (Edge neighbor : G[u])
        {
            int v = neighbor.dst;
            int weight = neighbor.weight;

            if (!visited[v] && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int> &, const vector<int> &previous, int destination)
{
    vector<int> result;
    int u = destination;

    while (u != -1)
    {
        result.push_back(u);
        u = previous[u];
    }

    reverse(result.begin(), result.end());
    return result;
}

void print_path(const vector<int> &v, int total)
{
    for (int i : v)
        cout << i << " ";

    cout << endl
         << "Total cost is " << total << endl;
}
