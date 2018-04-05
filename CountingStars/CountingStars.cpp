#include <bits/stdc++.h>

using namespace std;

void _DFSVisit(int vertex, vector<vector<int>> &AL, vector<bool> &visited)
{
  visited[vertex] = true;
  for(int i = 0; i < AL[vertex].size(); ++i)
  {
    if(!visited[AL[vertex][i]])
      _DFSVisit(AL[vertex][i], AL, visited);
  }
}

int DFSCountCC(vector<vector<int>> &AL, vector<bool> &starMap)
{
  int numOfCC = 0;
  vector<bool> visited(AL.size(), false);
  for(int i = 0; i < AL.size(); ++i)
  {
    if(!visited[i]) {
      _DFSVisit(i, AL, visited);
    
      if(starMap[i])
        ++numOfCC;
    }
  }
  
  return numOfCC;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string line;
  int m, n, caseNum=1;
  
  while(!cin.eof())
  {
    getline(cin, line);
    if(line.empty()) break;
    stringstream strStream(line);
    strStream >> m >> n;
    
    vector<vector<int>> image(m*n, vector<int>()); // adjacency list
    vector<bool> starMap(m*n, false);
    
    // building the graph
    for(int row = 0; row < m; ++row) {
      getline(cin, line);
      for(int col = 0; col < n; ++col) {
        if(line[col] == '-') {
          int curVertexNum = row*n + col; // range from 0 to m*n-1, each vertex has a unique number
          int prevAboveVertexNum = (row>0) ? (row-1)*n + col : -1;
          int prevLeftVertexNum = (col>0) ? row*n + col - 1 : -1;
          starMap[curVertexNum] = true;
          if(prevAboveVertexNum >= 0 && starMap[prevAboveVertexNum]) {
            image[prevAboveVertexNum].push_back(curVertexNum);
            image[curVertexNum].push_back(prevAboveVertexNum);  
          }
          if(prevLeftVertexNum >= 0 && starMap[prevLeftVertexNum]) {
            image[prevLeftVertexNum].push_back(curVertexNum);
            image[curVertexNum].push_back(prevLeftVertexNum);  
          }
        }
      }
    }

    // count connected components
    int numOfStars = DFSCountCC(image, starMap);
    cout << "Case " << caseNum << ": " << numOfStars << "\n";
    ++caseNum;
  }
  
  return 0;
}