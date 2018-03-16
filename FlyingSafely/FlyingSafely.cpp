#include <iostream>

using namespace std;

int main()
{
  int TC, n, m, a, b;
  
  cin >> TC;
  
  for(int i = 0; i < TC; ++i)
  {
    cin >> n >> m;
    for(int j = 0; j < m; ++j)
    {
      cin >> a >> b;
    }
    
    cout << n - 1 << endl; // minimum edges in connected graph is always (total vertices - 1)
  }
  
  return 0;
}