#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
  unordered_set<int> catalog;
  int N, M, cnt = 0, input;
  
  cin >> N >> M;
  while(N > 0 && M > 0)
  {
    for(int i = 0; i < N; ++i)
    {
      cin >> input;
      catalog.insert(input);
    }
    
    for(int i = 0; i < M; ++i)
    {
      cin >> input;
      if(catalog.count(input) == 1) ++cnt;
    }    
   
    cout << cnt << endl;
    
    catalog.clear();
    cnt = 0;
    
    cin >> N >> M;
  }

  return 0;
}