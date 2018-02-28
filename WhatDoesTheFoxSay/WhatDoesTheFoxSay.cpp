#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
  unordered_set<string> db;
  string buffer, recording, foxOutput;
  vector<string> foxOutputs;
  int T, itercnt=0;
  const string lastline = "what does the fox say?";
  size_t pos, pos2;
  
  getline(cin, buffer);
  stringstream ss(buffer);
  ss >> T;
  while(itercnt < T)
  {
    foxOutput = "";
    db.clear();
    
    // get recorded sounds;
    getline(cin, recording);
    
    // start scanning
    getline(cin, buffer);
    while(buffer.find(lastline) == string::npos)
    {
      // search for sound in current line
      pos = buffer.find("goes");
      pos += 4;
      while(buffer[pos] == ' ') ++pos;
      buffer.erase(0, pos); // strip '<animal>' and 'goes' and any spaces in between up until '<sound>'
      
      // now we need to strip any trailing spaces (just in case)
      pos = 0;
      while(pos < buffer.length() && buffer[pos] != ' ') ++pos;
      pos2 = pos;
      while(pos2 < buffer.length() && buffer[pos2] == ' ') ++pos2;
      if(pos2 - pos > 0) buffer.erase(pos, pos2);
      
      db.insert(buffer); // insert sound into hash table
      
      getline(cin, buffer);
    }
    
    pos = 0;
    pos2 = 0;
    while(pos < recording.length())
    {
      while(pos2 < recording.length() && recording[pos2] != ' ') ++pos2;
      string word = recording.substr(pos, pos2-pos);
      if(db.count(word) == 0) 
        if(foxOutput.length() > 0) foxOutput = foxOutput + ' ' + word;
        else foxOutput = word;
      while(pos2 < recording.length() && recording[pos2] == ' ') ++pos2;
      pos = pos2;
    }
    
    foxOutputs.push_back(foxOutput);
        
    ++itercnt;
  }
  
  for(int i = 0; i < foxOutputs.size(); ++i)
  {
    cout << foxOutputs[i] << endl;
  }
  
  return 0;
}