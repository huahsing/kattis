#include <bits/stdc++.h>

using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n, k, t, m, curPos;
  string cmdbuf;
  stack<int> posStack;
  
  posStack.push(0);
  
  cin >> n >> k;
  
  for(int i = 0; i < k; ++i)
  {
    cin >> cmdbuf;
    if(cmdbuf[0] != 'u')
    {
      t = stoi(cmdbuf);
      curPos = posStack.top();
      curPos = (((curPos + t) % n) + n) % n;
      posStack.push(curPos);
    }
    else
    {
      int undoIter = 0;
      cin >> m;
      while(!posStack.empty() && undoIter++ < m)
        posStack.pop();
    }
  }
  
  cout << (posStack.empty() ? 0 : posStack.top()) << endl;
  
  return 0;
}