#include "Code.h"

Code::Code() :
  code_(" "), length_(0) {}

Code::Code(std::string c, std::uint8_t l) :
  code_(c), length_(l) {}

CodeTable::CodeTable(TreeNode *root)
{
  getCodes(root, "", 0);
}
void CodeTable::getCodes(TreeNode *root, std::string code, int cur_len)
{
  if (root->isLeaf())
  {
    codes_[(std::size_t)(root->symbol_)].code_ = code;
    codes_[(std::size_t)(root->symbol_)].length_ = cur_len;
    return;
  }
  getCodes(root->left_, code + "0", cur_len + 1);
  getCodes(root->right_, code + "1", cur_len + 1);
}
void CodeTable::pack(char c, BitStream &stream) const
{
  Code code = codes_[(std::size_t)c];
  for (char ch : code.code_)
  {
    stream.writeBit((int)(ch - '0'));
  }
}

void CodeTable::printTable(std::ostream &out) const
{
  std::cout << "========================\n";
  std::cout << "   Huffman code table   \n";
  std::cout << "========================\n";
  std::cout << "char\tlength\tcode\n";
  for (std::size_t i = 0; i < ALPHABET_SIZE; ++i)
  {
    if (codes_[i].length_ != 0)
    {
      out << (char)i << '\t' << (int)codes_[i].length_ << '\t' << codes_[i].code_ << '\n';
    }
  }
  std::cout << "========================\n";
}
