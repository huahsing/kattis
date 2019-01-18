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

bool DFSVisit(unordered_map<string, Item> &itemList, string &itemName, string &list1, string &list2)
{
  Item &curItem = itemList[itemName];
  for(auto it = curItem.adjacentItems.begin(); it != curItem.adjacentItems.end(); ++it)
  {
    if(itemList[*it].color == curItem.color)
    {
      return false;
    }
    else if(itemList[*it].color == UNCOLORED) // unvisited
    {
      itemList[*it].color = getOppositeColor(curItem.color);
      switch(itemList[*it].color)
      {
        case RED:
          list1 = list1 + " " + *it;
          break;
          
        case BLUE:
          if(list2.size() == 0) 
          {
            list2 = *it;
          }
          else
          {
            list2 = list2 + " " + *it;
          }
      }
      // go deeper
      if(!DFSVisit(itemList, *it, list1, list2))
        return false;
    }
    // else already visited and in the other set so next
  }
  
  // all adjacent nodes visited
  
  return true;
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
        // start DFS
        if(!DFSVisit(itemList, it->second.name, list1, list2))
          return false;
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