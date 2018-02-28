#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

string parseNextWord(string& line)
{
  size_t start=0, end=0;
  while(line[end] != '\0' && line[end] != ' ') ++end;
  string word = line.substr(start, end);
  while(line[end] != '\0' && line[end] == ' ') ++end;
  line.erase(start, end);
  return word;
}

void clearMap(map<string, set<string>*>& m)
{
  for(map<string, set<string>*>::iterator it = m.begin(); it != m.end(); ++it)
  {
    delete it->second;
  }
  m.clear();
}

int main()
{
  int n;
  string input, report = "";
  map<string, set<string>*> menuItemList;
  map<string, set<string>*>::iterator it;
  
  getline(cin, input);
  stringstream ss(input);
  ss >> n;
  
  while(n != 0)
  {
    clearMap(menuItemList);
    
    for(int i = 0; i < n; ++i)
    {
      getline(cin, input); // scan line with name and items
      
      string name = parseNextWord(input);
      
      // insert menu item (if not existent and corresponding name)
      while(!input.empty()) 
      {
        string menuItem = parseNextWord(input);
        it = menuItemList.find(menuItem); // check for existence of menu item (as key)
        if(it != menuItemList.end())
        {
          set<string>* s = it->second; // retrieve the set of names and insert current name
          s->insert(name);
        }
        else
        {
          set<string>* s = new set<string>; // create a new set and insert current name
          s->insert(name);
          menuItemList.insert(pair<string, set<string>*>(menuItem, s));
        }
      }
    }
    
    for(it = menuItemList.begin(); it != menuItemList.end(); ++it)
    {
      report += it->first;
      set<string>* s = it->second;
      for(set<string>::iterator it = s->begin(); it != s->end(); ++it)
      {
        report = report + ' ' + *it;
      }
      report += '\n';
    }
    
    report += '\n';
    
    getline(cin, input); // get next test case's n
    stringstream ss(input);
    ss >> n;
  }
  
  cout << report << endl;
  
  clearMap(menuItemList);
  
  return 0;
}