#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int main()
{
  vector<string> inputList;
  set<string> compoundWords;
  string inputLine;
  
  // scan input
  while(getline(cin, inputLine))
  {
    size_t pos1=0, pos2=0;
    while(pos1 < inputLine.length())
    {
      while(pos2 < inputLine.length() && inputLine[pos2] != ' ') ++pos2;
      inputList.push_back(inputLine.substr(pos1, pos2-pos1));
      while(pos2 < inputLine.length() && inputLine[pos2] == ' ') ++pos2;
      pos1 = pos2;
    }
  }
  
  // make words
  for(int i = 0; i < inputList.size(); ++i)
  {
    for(int j = 0; j < inputList.size(); ++j)
    {
      if(j != i) compoundWords.insert(inputList[i] + inputList[j]);
    }
  }
  
  for (set<string>::iterator it = compoundWords.begin(); it != compoundWords.end(); ++it)
    cout << *it << endl;
  
  return 0;
}