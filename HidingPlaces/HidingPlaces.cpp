#include <cstdio>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define FILECHAR_TO_FILENUM(x) ((x)-97)
#define RANKCHAR_TO_REVRANKNUM(x) (7 - ((x)-49))

#define REVRANK_FILE_NUMS_TO_VERTEX(nrr, nf) ((nrr)*8 + (nf))

#define VERTEX_TO_RANKCHAR(v) ( (7 - ((v) / 8)) + 49 )
#define VERTEX_TO_FILECHAR(v) ( (v) % 8 + 97 )
    
void KnightGraph_Init(vector<vector<int>> &G)
{
  // rank top to bottom (0 - 7) (this is reverse of input so that we can skip sorting step of the problem
  for(int rev_rank = 0; rev_rank < 8; ++rev_rank)
  {
    // file left to right (0(a) - 7(h))
    for(int file = 0; file < 8; ++file)
    {
      int curTile = REVRANK_FILE_NUMS_TO_VERTEX(rev_rank, file);
      
      if(file-2 >= 0)
      {
        if(rev_rank+1 < 8) // check left-down
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank+1, file-2));
        
        if(rev_rank-1 >= 0)  // check left-up
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank-1, file-2));
      }
      
      if(rev_rank-2 >= 0)
      {
        if(file-1 >= 0) // check up-left
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank-2, file-1));
        
        if(file+1 < 8)  // check up-right
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank-2, file+1));
      }
      
      if(file+2 < 8)
      {
        if(rev_rank-1 >= 0) // check right-up
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank-1, file+2));
        
        if(rev_rank+1 < 8)  // check right-down
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank+1, file+2));
      }
      
      if(rev_rank+2 < 8)
      {
        if(file+1 < 8) // check down-right
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank+2, file+1));
        
        if(file-1 >= 0)  // check down-left
          G[curTile].push_back(REVRANK_FILE_NUMS_TO_VERTEX(rev_rank+2, file-1));
      }
    }
  }
}

// populates hidingPlacesList and returns number of jumps
int KnightGraph_FindHidingPlaces(vector<vector<int>> &G, char startLoc[], vector<int> &hidingPlaces)
{
  int startVertex = REVRANK_FILE_NUMS_TO_VERTEX( RANKCHAR_TO_REVRANKNUM(startLoc[1]), FILECHAR_TO_FILENUM(startLoc[0]) );
  vector<bool> visited(64, false);
  vector<int> dist(64, INT_MAX);
  queue<int> bfsQ;
  int distValue = -1;

  visited[startVertex] = true;
  dist[startVertex] = 0;
  bfsQ.push(startVertex);
  while(!bfsQ.empty())
  {
    int curV = bfsQ.front();
    bfsQ.pop();
    for(int i = 0; i < G[curV].size(); ++i)
    {
      int adjV = G[curV][i];
      if(!visited[adjV])
      {
        visited[adjV] = true;
        dist[adjV] = dist[curV] + 1;
        bfsQ.push(adjV);
      }
    }
  }
  
  for(int i = 0; i < dist.size(); ++i)
  {
    if(dist[i] == distValue)
    {
      hidingPlaces.push_back(i);
    }
    else if(dist[i] > distValue)
    {
      hidingPlaces.clear();
      distValue = dist[i];
      hidingPlaces.push_back(i);
    }
  }
  
  return distValue;
}

int main()
{
  int n;
  char startLoc[3];
  vector<vector<int>> KnightGraph(64, vector<int>());
  vector<int> hidingPlaces;
  
  KnightGraph_Init(KnightGraph);
  
  scanf("%d\n", &n);
  for(int i = 0; i < n; ++i)
  {
    scanf("%s\n", startLoc);
    int numOfJumps = KnightGraph_FindHidingPlaces(KnightGraph, startLoc, hidingPlaces);
    
    printf("%d", numOfJumps);
    for(int i = 0; i < hidingPlaces.size(); ++i)
    {
      printf(" %c%c", VERTEX_TO_FILECHAR(hidingPlaces[i]), VERTEX_TO_RANKCHAR(hidingPlaces[i]));
    }
    putchar('\n');
    
    hidingPlaces.clear();
  }
  
  return 0;
}