#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <fstream>
#include <memory>
#include <filesystem>
#include <iostream>
#include <utility>
#include <vector>
#include "BitStream.h"
#include "CodeTable.h"
#include "Tree.h"
#include "constants.h"

void encode(std::fstream &inputFile, std::fstream &outputFile);
void decode(std::fstream &inputFile, std::fstream &outputFile);

#endif  // _HUFFMAN_H
