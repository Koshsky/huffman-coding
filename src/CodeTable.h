#ifndef _CODE_H
#define _CODE_H

#include <cstddef>
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include "BitStream.h"
#include "Tree.h"
#include "constants.h"

class CodeTable
{
public:
  CodeTable(TreeNode *tree);
  void getCodes(TreeNode *root, std::string code, int cur_len);
  void pack(char c, BitStream &stream) const;
  void printTable(std::ostream &out) const;

private:
  std::vector<std::pair<char, std::string>> codes_;
};

#endif // _CODE_H
