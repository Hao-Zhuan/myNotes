#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
//一面大题：n个数对 将其分集
//二面：用vector初始化list&&简单排序

int count = 0;
std::vector<std::vector<int>> MergeSet(std::vector<std::pair<int, int>> input)
{
  std::vector<std::vector<int>> res;
  std::map<int, int> mp;
  for (auto i : input)
  {
    if ((i.first == -1 &&mp[i.second] == 0)||(i.second==-1&&mp[i.first]==0))
    {
      ++count;
      if (i.first == -1)
        mp[i.second] = count;
      else
        mp[i.first] = count;
    }
    if ((i.first == -1 &&mp[i.second] != 0)||(i.second==-1&&mp[i.first]!=0)){
      //do nothing
    }

    else if (mp[i.first] == 0 && mp[i.second] == 0)
    {
      ++count;
      mp[i.first] = mp[i.second] = count;
    }

    else if (mp[i.first] == 0 || mp[i.second] == 0)
    {
      mp[i.first] == 0 ? mp[i.first] = mp[i.second] : mp[i.second] = mp[i.first];
    }

    else 
    {
      int m=std::max(mp[i.first], mp[i.second]);
      int s=std::min(mp[i.first], mp[i.second]);
      for (auto&j : mp)
      {
        if (j.second == m)
        {
          j.second = s;

        }
      }
    }
  }

  std::vector<int> once;
  for (auto i : mp)
  {
    static int temp = 1;
    if (i.second == temp)
      once.emplace_back(i.first);
    else
    {
      if (!once.empty())
        res.emplace_back(once);
      once.clear();
      temp = i.second;
      once.emplace_back(i.first);
    }
  }
  res.emplace_back(once);
  for (auto i : res)
  {
    for (auto j : i)
      std::cout << j << " ";
    std::cout << "\n";
  }
  return res;
}

int main()
{
  std::vector<std::pair<int, int>> test = {{1, 2}, {4, 5}, {10, 4},{-1,10},{2,4}};
  MergeSet(test);
  return 0;
}
