#include <bits/stdc++.h>

using namespace std;

class TradeUnion
{
private:
  struct Country
  {
    int origNumOfTradingPartners;
    unordered_set<int> partners;
    Country() 
    { 
      origNumOfTradingPartners = 0; 
      partners.max_load_factor(0.5f);
    }
  };
  
  unordered_map<int, Country> countryList;

public:
  TradeUnion() { countryList.max_load_factor(0.5f); }
  void addTradePartnership(int A, int B)
  {
    countryList[A].partners.insert(B);
    countryList[B].partners.insert(A);
    ++countryList[A].origNumOfTradingPartners;
    ++countryList[B].origNumOfTradingPartners;
  }
  
  // returns true if my country should leave too, else false
  bool leave(int myCountry, int firstCountryToLeave)
  {
    if(myCountry == firstCountryToLeave) return true;
    
    bool retVal = false;
    queue<int> q;
    vector<bool> inQueue(countryList.size(), false);
    
    int curCountryToProcess;
    
    // initial insertion into queue
    for(auto it = countryList[firstCountryToLeave].partners.begin();
            it != countryList[firstCountryToLeave].partners.end();
            ++it)
    {
      countryList[*it].partners.erase(firstCountryToLeave);
      q.push(*it);
      inQueue[*it] = true;
    }
    
    // remove first country from union
    countryList.erase(firstCountryToLeave);
    
    while(!q.empty())
    {
      curCountryToProcess = q.front();
      q.pop();
      inQueue[curCountryToProcess] = false;
      
      if(countryList.find(curCountryToProcess) != countryList.end() && 
      countryList[curCountryToProcess].partners.size() <= countryList[curCountryToProcess].origNumOfTradingPartners / 2)
      {
        // curCountryToProcess will leave, update its trading partners' partner list (or return true if it's my country)
        if(curCountryToProcess == myCountry)
        {
          retVal = true; // no further processing needed
          break;
        }
        
        // update partners (by removing curCountry)
        for(auto it = countryList[curCountryToProcess].partners.begin();
            it != countryList[curCountryToProcess].partners.end();
            ++it)
        {
          if(countryList.find(*it) != countryList.end()) {
          countryList[*it].partners.erase(curCountryToProcess);
        
          // possible to have duplicates in queue (waiting to be examined, due to multiple partners leaving after its first 
          // partner has left and I have yet to examine it) so we avoid that unnecessary overhead of duplicate work,
          if(!inQueue[*it])
          {
            q.push(*it);
            inQueue[*it] = true;
          }
          }
        }
        
        // completely remove curCountry from union
        countryList.erase(curCountryToProcess);
      }
    }
    
    return retVal;
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  TradeUnion tradeUnion;
  int C, P, X, L, A, B;
  cin >> C >> P >> X >> L;
  
  // build graph
  for(int i = 0; i < P; ++i)
  {
    cin >> A >> B;
    tradeUnion.addTradePartnership(A, B);
  }
  
  if(tradeUnion.leave(X, L))
    cout << "leave\n";
  else
    cout << "stay\n";
  
  return 0;
}