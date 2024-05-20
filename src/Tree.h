#ifndef _TREE_H
#define _TREE_H

#include <cstddef>
#include <iostream>
#include "constants.h"
#include "BitStream.h"
#include "Queue.hpp"

class TreeNode {
public:
  char symbol_;
  int freq_;
  TreeNode *left_;
  TreeNode *right_;

  TreeNode(char symbol, int freq, TreeNode *left = nullptr, TreeNode *right = nullptr);
  ~TreeNode();

  bool isLeaf() const;
  void packTree(BitStream &stream);
};

class Tree {
public:
  Tree(const Vector<std::pair<char, int>> frequencies);
  Tree(TreeNode *root);
  ~Tree();

  ErrorCode unpack(BitStream &stream, char &c);

  TreeNode *root_;
};

struct TreeNodeComparator
{
  bool operator()(TreeNode *lhs, TreeNode *rhs) const
      { return lhs->freq_ < rhs->freq_; }
};

TreeNode * unpackTree(BitStream &stream);

#endif // _TREE_H
