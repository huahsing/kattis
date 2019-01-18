#include <bits/stdc++.h>

using namespace std;

class City
{
private:
  vector<vector<int>> adjList;
  
  void DFSVisit(int vertex, vector<bool> &visited)
  {
    visited[vertex] = true;
    for(auto it = adjList[vertex].begin(); it != adjList[vertex].end(); ++it)
    {
      if(!visited[*it])
        DFSVisit(*it, visited);
    }
  }
  
  int numOfConnectedComponents()
  {
    vector<bool> visited(adjList.size(), false);
    int connectedComponentsCnt = 0, vertex = 0;
    
    for(auto it = adjList.begin(); it != adjList.end(); ++it)
    {
      if(!visited[vertex])
      {
        DFSVisit(vertex, visited);
        ++connectedComponentsCnt;
      }
      
      ++vertex;
    }
    
    return connectedComponentsCnt;
  }
  
public:
  City(int numOfEndPoints) 
  { 
    adjList = vector<vector<int>>(numOfEndPoints, vector<int>()); 
  }
  
  void addEdge(int src, int dst)
  {
    adjList[src].push_back(dst);
    adjList[dst].push_back(src);
  }
  
  int minRoadsNeeded() { return numOfConnectedComponents() - 1; }
};

int main()
{
  int n, m, r, src, dst;
  
  cin >> n;
  
  for(int i = 0; i < n; ++i)
  {
    cin >> m;
    City C(m);
    cin >> r;
    for(int j = 0; j < r; ++j)
    {
      cin >> src >> dst;
      C.addEdge(src, dst);
    }
    cout << C.minRoadsNeeded() << endl;
  }
  
  return 0;
}