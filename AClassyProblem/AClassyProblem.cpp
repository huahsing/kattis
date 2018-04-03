#include <bits/stdc++.h>

using namespace std;

string middle_pads[] =
{
  "2222222222",
  "222222222",
  "22222222",
  "2222222",
  "222222",
  "22222",
  "2222",
  "222",
  "22",
  "2"
};

struct Person
{
  string name;
  string classnumstr;
};

bool fncomp(const Person *lhs, const Person *rhs) 
{
  int compareVal = lhs->classnumstr.compare(rhs->classnumstr);
  if(compareVal != 0)
  {
    return compareVal > 0; // lhs comes before rhs if lhs's class is a 'greater' string
  }
  else
  {
    return lhs->name.compare(rhs->name) < 0; // if equivalent class, lhs comes before rhs if lhs's name is a 'lesser' string
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  set<Person*, bool(*)(const Person*, const Person*)> db(fncomp);

  int T;
  string classname(6*10 + 9 + 1, '\0'); // max length = 10x 'middle' + 9 hyphens + terminating null
  string classwordbuf(4 + 1, '\0');
  cin >> T;
  
  for(int i = 0; i < T; ++i)
  {
    int n;
    cin >> n;
    for(int j = 0; j < n; ++j)
    {
      Person *p = new Person;
      cin >> p->name >> classname >> classwordbuf;
      p->name.erase(p->name.size()-1);
      
      size_t firstpos;
      size_t lastpos = classname.size() - 1;
      bool done = false;
      while(!done)
      {
        firstpos = classname.rfind('-', lastpos);
        
        if(firstpos == string::npos)
        {
          done = true;
          firstpos = -1;
        }
        
        if(classname.substr(firstpos+1, lastpos - firstpos) == "upper")
          p->classnumstr += '3';
        else if(classname.substr(firstpos+1, lastpos - firstpos) == "middle")
          p->classnumstr += '2';
        else
          p->classnumstr += '1';
        
        lastpos = firstpos - 1;
      }
      
      // padding with middle class
      if(p->classnumstr.size() < 10);
        p->classnumstr += middle_pads[p->classnumstr.size()];

      db.insert(p);
    }
    
    for(auto it = db.begin(); it != db.end(); ++it)
    {
      cout << (*it)->name << "\n";
      delete *it;
    }
    
    cout << "==============================" << "\n";
    
    db.clear();
  }

  return 0;
}