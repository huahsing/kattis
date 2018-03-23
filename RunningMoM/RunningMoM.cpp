#include <bits/stdc++.h>

using namespace std;

class FlightMap
{
private:
  unordered_map<string, vector<string>> fMap;
  unordered_map<string, bool> visited_initmap;
  
  bool _cycleExists(string &city, unordered_map<string, bool> &visited, unordered_map<string, bool> &currentPathNodes)
  {
    visited[city] = true;
    currentPathNodes[city] = true;
    for(int i = 0; i < fMap[city].size(); ++i)
    {
      string adjCity = fMap[city][i];
      if(!visited[adjCity])
      {
        if(_cycleExists(adjCity, visited, currentPathNodes))
          return true;
      }
      else
      {
        if(currentPathNodes[adjCity])
          return true;
      }
    }
    currentPathNodes[city] = false;
    return false;
  }
  
public:
  FlightMap() { fMap.max_load_factor(0.25); visited_initmap.max_load_factor(0.25); }
  
  void addFlight(string src, string dst)
  {
    fMap[src].push_back(dst);
  }
  
  void allFlightsAdded()
  {
    for(auto it = fMap.begin(); it != fMap.end(); ++it)
    {
      visited_initmap[it->first] = false;
    }
  }
  
  bool isSafe(string &city)
  {
    unordered_map<string, bool> visited(visited_initmap);
    unordered_map<string, bool> currentPathNodes(visited_initmap);
    return _cycleExists(city, visited, currentPathNodes);
  }
};

int main()
{
  FlightMap flight_map;
  int n;
  string o, d, city_to_inspect;
  
  cin >> n;
  
  for(int i = 0; i < n; ++i)
  {
    cin >> o >> d;
    flight_map.addFlight(o, d);
  }
  
  flight_map.allFlightsAdded();
  
  getline(cin, city_to_inspect); // get rid of newline
  getline(cin, city_to_inspect); // scan next line
  
  while(!cin.eof())
  {
    if(!city_to_inspect.empty())
    {
      if(flight_map.isSafe(city_to_inspect))
        cout << city_to_inspect << " " << "safe" << endl;
      else
        cout << city_to_inspect << " " << "trapped" << endl;
    }
    getline(cin, city_to_inspect);
  }
}