#include "Tree.h"
#include <iostream>

TreeNode::TreeNode(char symbol, int freq, TreeNode *left, TreeNode *right)
  : symbol_(symbol), freq_(freq), left_(left), right_(right) {}

TreeNode::~TreeNode()
{
  delete left_;
  delete right_;
}

bool TreeNode::isLeaf() const
{
  return left_ == nullptr;
}

Tree::Tree(TreeNode *root):
  root_(root) {}

Tree::~Tree()
{
  if (root_ == nullptr)
    return;

  delete root_;
}

void TreeNode::packTree(BitStream &stream)
{
  if (isLeaf())
  {
    stream.writeBit(1);
    stream.writeByte(symbol_);
    return;
  }
  stream.writeBit(0);
  left_->packTree(stream);
  right_->packTree(stream);
}

void TreeNode::printTree(std::ostream &out) const
{
  out << '(';
  if (left_)
    left_->printTree(out);
  out << symbol_;
  if (right_)
    right_->printTree(out);
  out << ')';
}

Tree::Tree(const int *frequencies) :
  root_(nullptr)
{

  PriorityQueue<TreeNode *, TreeNodeComparator> queue;
  for (std::size_t i = 0; i < ALPHABET_SIZE; i++)
  {
    if (frequencies[i] != 0)
    {
      TreeNode *node = new TreeNode((char)i, frequencies[i], nullptr, nullptr);
      queue.push(node);
    }
  }
  if (queue.size() < 2)
  {
    root_ = queue.top();
    queue.pop();
    return;
  }

  while (true)
  {
    TreeNode *left = queue.top();
    queue.pop();
    TreeNode *right = queue.top();
    queue.pop();
    root_ = new TreeNode((char)0, left->freq_ + right->freq_, left, right);

    if (queue.empty())
      return;

    queue.push(root_);
  }
}

ErrorCode Tree::unpack(BitStream &stream, char &c)  // getSymbol from encodedFile
{
  TreeNode *currNode = root_;
  while (!currNode->isLeaf())
  {
    int bit;
    if (stream.readBit(bit) == ErrorCode::ReadError)
      return ErrorCode::ReadError;

    currNode = (bit == 0 ? currNode->left_ : currNode->right_);
  }

  c = currNode->symbol_;
  return ErrorCode::NoError;
}

void Tree::printTree(std::ostream &out) const
{
  root_->printTree(out);
  out << '\n';
}

TreeNode * unpackTree(BitStream &stream)  // getTree from encodedFile
{
  int bit;
  if (stream.readBit(bit) == ErrorCode::ReadError)
    return nullptr;

  if (bit == 1)
  {
    unsigned char c;
    if (stream.readByte(c) == ErrorCode::ReadError)
      return nullptr;

    return new TreeNode(c, 0, nullptr, nullptr);
  }
  TreeNode *left = unpackTree(stream);
  TreeNode *right = unpackTree(stream);
  return new TreeNode(0, 0, left, right);
}
