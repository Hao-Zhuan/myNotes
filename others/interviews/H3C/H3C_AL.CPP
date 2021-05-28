#include <iostream>
#include <vector>
#include <stack>
struct node
{
  int val;
  bool unchanged;
  int stat;
  node *add;
  node *sub;
  node *stay;
  node(int val) : val(val), unchanged(true), stat(0), add(nullptr), sub(nullptr), stay(nullptr) {}
};

class Tree
{
public:
  node *root;
  std::vector<int> DFS(node *p);
};
std::vector<int> Tree::DFS(node *p)
{
  std::stack<node *> st;
  while (!st.empty() && p)
  {
    if(p->unchanged);
  }
}
