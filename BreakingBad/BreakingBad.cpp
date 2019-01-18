#include <bits/stdc++.h>

using namespace std;

enum eCOLOR_STATE
{
  UNCOLORED,
  RED,
  BLUE
};

struct Item
{
  eCOLOR_STATE color;
  string name;
  vector<string> adjacentItems;

  Item(string name="") { this->name = name; color = UNCOLORED; }
};

eCOLOR_STATE getOppositeColor(eCOLOR_STATE &color)
{
  eCOLOR_STATE ret = UNCOLORED;
  if(color == RED) ret = BLUE;
  else if(color == BLUE) ret = RED;
  return ret;
}

bool isBipartite(unordered_map<string, Item> &itemList, string &list1, string &list2)
{
  for(auto it = itemList.begin(); it != itemList.end(); ++it)
  {
    if(it->second.color == UNCOLORED)
    {
      it->second.color = RED;
      
      if(list1.size() == 0) 
      {
        list1 = it->second.name;
      }
      else
      {
        list1 = list1 + " " + it->second.name;
      }
      
      if(it->second.adjacentItems.size() != 0)
      {
        // start BFS
        queue<string> BFSQueue;
        BFSQueue.push(it->second.name);
        while(!BFSQueue.empty())
        {
          Item &curItem = itemList[BFSQueue.front()];
          BFSQueue.pop();
          for(auto it2 = curItem.adjacentItems.begin(); it2 != curItem.adjacentItems.end(); ++it2)
          {
            if(itemList[*it2].color == curItem.color)
            {
              return false;
            }
            else if(itemList[*it2].color == UNCOLORED)
            {
              itemList[*it2].color = getOppositeColor(curItem.color);
              switch(itemList[*it2].color)
              {
                case RED:
                  list1 = list1 + " " + *it2;
                  break;
                  
                case BLUE:
                  if(list2.size() == 0) 
                  {
                    list2 = *it2;
                  }
                  else
                  {
                    list2 = list2 + " " + *it2;
                  }
              }
              BFSQueue.push(*it2);
            }
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
  unordered_map<string, Item> itemList;
  string list1, list2;
  
  itemList.max_load_factor(0.5);
  
  cin >> N;
  
  for(int i = 0; i < N; ++i)
  {
    cin >> item1;
    itemList[item1] = Item(item1);
  }
  
  cin >> M;
  for(int i = 0; i < M; ++i)
  {
    cin >> item1 >> item2;
    itemList[item1].adjacentItems.push_back(item2);
    itemList[item2].adjacentItems.push_back(item1);
  }
  
  if(isBipartite(itemList, list1, list2))
  {
    cout << list1 << "\n" << list2 << endl;
  }
  else
  {
    cout << "impossible" << endl;
  }
  
  return 0;
}