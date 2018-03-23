#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, M;
  unordered_set<string> itemSet, redSet, blueSet;
  bool isBipartite = true;  
  string item1, item2, redList="", blueList="";
  
  cin >> N;
  
  for(int i = 0; i < N; ++i)
  {
    cin >> item1;
    itemSet.insert(item1);
  }
  
  cin >> M;
  for(int i = 0; i < M; ++i)
  {
    cin >> item1 >> item2;
    if(itemSet.find(item1) != itemSet.end())
    {
      itemSet.erase(item1);
      if(itemSet.find(item2) != itemSet.end())
      {
        redSet.insert(item1);
        redList = redList + " " + item1;
        itemSet.erase(item2);
        blueSet.insert(item2);
        blueList = blueList + " " + item2;
      }
      else
      {
        if(redSet.find(item2) != redSet.end())
        {
          blueSet.insert(item1);
          blueList = blueList + " " + item1;
        }
        else // item2 must be in blue set
        {
          redSet.insert(item1);
          redList = redList + " " + item1;
        }
      }
    }
    else if(itemSet.find(item2) != itemSet.end())
    {
      itemSet.erase(item2);
      if(redSet.find(item1) != redSet.end())
      {
        blueSet.insert(item2);
        blueList = blueList + " " + item2;
      }
      else // item1 must be in blue set
      {
        redSet.insert(item2);
        redList = redList + " " + item2;
      }
    }
    else
    {
      // both items already in colored sets
      if( (redSet.find(item1) != redSet.end() && redSet.find(item2) != redSet.end()) ||
          (blueSet.find(item1) != blueSet.end() && blueSet.find(item2) != blueSet.end()) )
      {
        // both items in same sets
        isBipartite = false;
        break; // don't waste time, just give up
      }
      else
      {
        // both items in different sets, nothing to do
      }
    }
  }
  
  if(isBipartite)
  {
    // populate redList with all those still in itemSet
    for(auto it = itemSet.begin(); it != itemSet.end(); ++it)
      redList = redList + " " + *it;
    
    auto leadingSpace = redList.find_first_not_of(" ");
    cout << redList.substr(leadingSpace, redList.size() - leadingSpace) << "\n";
    leadingSpace = blueList.find_first_not_of(" ");
    cout << blueList.substr(leadingSpace, blueList.size() - leadingSpace) << endl;
  }
  else
  {
    cout << "impossible" << endl;
  }
  
  return 0;
}