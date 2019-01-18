#include <bits/stdc++.h>

using namespace std;

const int K_UNCOLORED = -1;
const int K_RED = 0; // even
const int K_BLUE = 1; // odd

struct Item
{
  string unique_name;
  int color;
  vector<string> suspicious_pairs;
  
  Item(string n = "") { unique_name = n; color = K_UNCOLORED; }
};

bool isBipartite(unordered_map<string, Item*> &items, queue<string> resultLists[])
{
  for(auto it = items.begin(); it != items.end(); ++it)
  {
    if(it->second->color == K_UNCOLORED)
    {
      it->second->color = K_RED;
      resultLists[it->second->color].push(it->second->unique_name);
      queue<string> q;
      q.push(it->second->unique_name);
      while(!q.empty())
      {
        Item *curItem = items[q.front()];
        q.pop();
        for(int i = 0; i < curItem->suspicious_pairs.size(); ++i)
        {
          Item *adjItem = items[curItem->suspicious_pairs[i]];
          if(adjItem->color == curItem->color)
            return false;
          
          if(adjItem->color == K_UNCOLORED)
          {
            adjItem->color = (curItem->color + 1) % 2;
            resultLists[adjItem->color].push(adjItem->unique_name);
            q.push(adjItem->unique_name);
          }
        }
      }
    }
  }
  
  return true;
}

int main()
{
  int N, M;
  string item1, item2;
  queue<string> resultLists[2];
  unordered_map<string, Item*> items;
  
  items.max_load_factor(0.5);

  cin >> N;
  
  for(int i = 0; i < N; ++i)
  {
    cin >> item1;
    items[item1] = new Item(item1);
  }
  
  cin >> M;
  for(int i = 0; i < M; ++i)
  {
    cin >> item1 >> item2;
    items[item1]->suspicious_pairs.push_back(item2);
    items[item2]->suspicious_pairs.push_back(item1);
  }
  
  if(isBipartite(items, resultLists))
  {
    for(int i = 0; i < 2; ++i)
    {
      if(!resultLists[i].empty())
      {
        cout << resultLists[i].front();
        resultLists[i].pop();
        while(!resultLists[i].empty())
        {
          cout << " " << resultLists[i].front();
          resultLists[i].pop();
        }
        cout << endl;
      }
    }
  }
  else
  {
    cout << "impossible" << endl;
  }
  
  for(auto it = items.begin(); it != items.end(); ++it)
  {
    delete it->second;
  }
  
  return 0;
}