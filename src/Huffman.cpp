#include "Huffman.h"

Vector<std::pair<char, int>> createFrequencyTable(std::fstream &in)
{
  Vector<std::pair<char, int>> frequencies;

  char c;
  while (in.peek() != EOF)
  {
    in.get(c);
    bool hasKey = false;
    for (size_t i = 0; i < frequencies.size(); ++i)
    {
      if (frequencies[i].first == c)
      {
        ++frequencies[i].second;
        hasKey = true;
        break;
      }
    }
    if (!hasKey)
    {
      frequencies.push_back({ c, 1 });
    }
  }

  in.seekg(0, std::ios::beg);
  in.clear();
  return frequencies;
}

int getFileSize(std::fstream &file) {
  file.seekg(0, std::ios::end);
  std::streampos fileSize = file.tellg();
  std::streamsize intermediate = fileSize;
  int fileSizeInt = static_cast<int>(intermediate);
  return fileSizeInt;
}

void encode(std::fstream &inputFile, std::fstream &outputFile)
{
  inputFile.seekg(0, std::ios_base::beg);
  outputFile.seekp(0, std::ios::beg);

  BitStream stream(outputFile);
  Vector<std::pair<char, int>> frequencies(createFrequencyTable(inputFile));
  Tree tree(frequencies);
  TreeNode *root = tree.root_;
  CodeTable codes(root);
  codes.printTable(std::cout);

  int length = root->freq_;
  outputFile.write(reinterpret_cast<const char *>(&length), sizeof(int));

  std::cout << "PACKING TREE\n";
  root->packTree(stream);

  std::cout << "ENCODING TEXT:\n";
  while (inputFile.peek() != EOF)
  {
    char c;
    inputFile.get(c);
    codes.pack(c, stream);
  }

  int inputFileSize = getFileSize(inputFile);
  int outputFileSize = getFileSize(outputFile);
  std::cout << "\nInput fileSize: " << inputFileSize << '\n';
  std::cout << "Encoded fileSize: " << outputFileSize << '\n';
  std::cout << "Compression ratio: " << (double)inputFileSize / outputFileSize << '\n';
}

void decode(std::fstream &inputFile, std::fstream &outputFile)
{
  if (inputFile.peek() == EOF)
    return;

  BitStream stream(inputFile);
  int length;
  inputFile.read(reinterpret_cast<char *>(&length), sizeof(int));

  TreeNode *root = unpackTree(stream);
  if (!root)
    throw std::runtime_error("Failed to unpack tree");
  Tree tree(root);

  char c = 0;
  for (int i = 0; i < length; ++i)
  {
    if (tree.unpack(stream, c) == ErrorCode::ReadError)
      throw std::runtime_error("Failed to unpack data");
    outputFile.write(reinterpret_cast<const char *>(&c), sizeof(unsigned char));
  }
}
