#ifndef _CODE_H
#define _CODE_H

#include <cstddef>
#include <iostream>
#include <bitset>
#include <string>
#include "BitStream.h"
#include "Tree.h"
#include "constants.h"

struct Code
{
  Code();
  Code(std::string c, std::uint8_t l);

  std::string code_;
  std::uint8_t length_;
};

class CodeTable
{
public:
  CodeTable(TreeNode *tree);
  void getCodes(TreeNode *root, std::string code, int cur_len);
  void pack(char c, BitStream &stream) const;
  void printTable(std::ostream &out) const;

private:
  Code codes_[ALPHABET_SIZE];
};

#endif // _CODE_H
