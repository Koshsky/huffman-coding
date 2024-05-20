#include "CodeTable.h"

CodeTable::CodeTable(TreeNode *root)
{
  getCodes(root, "", 0);
}
void CodeTable::getCodes(TreeNode *root, std::string code, int cur_len)
{
  if (root->isLeaf())
  {
    codes_.push_back({ root->symbol_, code });
    return;
  }
  getCodes(root->left_, code + "0", cur_len + 1);
  getCodes(root->right_, code + "1", cur_len + 1);
}
void CodeTable::pack(char c, BitStream &stream) const
{
  std::string code;
  for (size_t i = 0; i < codes_.size(); ++i)
  {
    if (codes_[i].first == c)
      code = codes_[i].second;
  }
  for (char ch : code)
  {
    stream.writeBit((int)(ch - '0'));
  }
}

void CodeTable::printTable(std::ostream &out) const
{
  std::cout << "========================\n";
  std::cout << "   Huffman code table   \n";
  std::cout << "========================\n";
  std::cout << "char\tcode\n";
  for (std::size_t i = 0; i < codes_.size(); ++i)
  {
    out << codes_[i].first << '\t' << codes_[i].second << '\n';
  }
  std::cout << "========================\n";
}
