#include <cstdio>
#include <vector>
#include <map>
#include <climits>

using namespace std;

struct AdjNode
{
  int adj_v;
  int weight;
  AdjNode(int v, int w) { adj_v = v; weight = w; }
};

struct Node
{
  int self_u;
  int dist;
  Node(int u, int d) { self_u = u; dist = d; }
};

class NodeDistLess
{
public:
  bool operator() (const Node& lhs, const Node&rhs) const
  {
    return (lhs.dist < rhs.dist);
  }
};

int main()
{
  int n, m, q, s;
  int u, v, w, queried_node;
  
  scanf("%d %d %d %d\n", &n, &m, &q, &s);
  while(n || m || q || s)
  {
    vector<vector<AdjNode>> adjList(n, vector<AdjNode>());
    
    // build adjacency list
    for(int i = 0; i < m; ++i)
    {
      scanf("%d %d %d\n", &u, &v, &w);
      adjList[u].push_back(AdjNode(v, w));
    }
    
    vector<int> dist(n, INT_MAX);
    priority_queue<Node, vector<Node>, NodeDistLess> unsolved;
    dist[s] = 0;
    unsolved.push(Node(s, 0));
    while(!unsolved.empty())
    {
      int currentNode = unsolved.top().self_u;
      unsolved.pop();
      
      if(dist[currentNode] < unsolved.top().dist) continue;
      
      // relax each edge
      for(int i = 0; i < adjList[currentNode].size(); ++i)
      {
        if(dist[adjList[currentNode][i].adj_v] > dist[currentNode] + adjList[currentNode][i].weight)
        {
          dist[adjList[currentNode][i].adj_v] = dist[currentNode] + adjList[currentNode][i].weight;
          unsolved.push(Node(adjList[currentNode][i].adj_v, dist[adjList[currentNode][i].adj_v]));
        }
      }
    }
    
    for(int i = 0; i < q; ++i)
    {
      scanf("%d\n", &queried_node);
      if(dist[queried_node] != INT_MAX)
        printf("%d\n", dist[queried_node]);
      else
        printf("Impossible\n");
    }
    
    putchar('\n');
    
    scanf("%d %d %d %d\n", &n, &m, &q, &s);
  }
  
  return 0;
}