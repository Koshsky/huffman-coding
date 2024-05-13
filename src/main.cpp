#include "Huffman.h"

#include <fstream>
#include <iostream>
#include <string>

void processEncode(const std::string &inputFileName, const std::string &encodedFileName);
void processDecode(const std::string &encodedFileName, const std::string &outputFileName);

int main(void) {
  std::string inputFileName("in.txt");
  std::string encodedFileName("out.txt");

  //std::cout << "Enter inputFileName: ";
  //std::cin >> inputFileName;
  //std::cout << "Enter outputFileName: ";
  //std::cin >> outputFileName;

  char mode;
  std::cin >> mode;
  if (mode == 'c')
  {
    processEncode(inputFileName, encodedFileName);
  }
  else if (mode == 'd')
  {
    processDecode(encodedFileName, inputFileName);
  }
  else
  {
    std::cerr << "Invalid mode" << std::endl;
    return 1;
  }
  std::cout << "\nCOMPLETE\n";

  return 0;
}
void processDecode(const std::string &encodedFileName, const std::string &outputFileName)
{
  std::fstream encodedFile(encodedFileName, std::ios::in | std::ios::binary);
  std::fstream outputFile(outputFileName, std::ios::out | std::ios::binary | std::ios::trunc);


  if (!encodedFile.is_open() || !outputFile.is_open())
  {
    std::cerr << "Failed to open file" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Decoding " << encodedFileName << " ...\n";
  decode(encodedFile, outputFile);
}
void processEncode(const std::string& inputFileName, const std::string &encodedFileName)
{
  std::fstream inputFile(inputFileName, std::ios::in | std::ios::binary);
  std::fstream encodedFile(encodedFileName, std::ios::out | std::ios::binary | std::ios::trunc);


  if (!inputFile.is_open() || !encodedFile.is_open())
  {
    std::cerr << "Failed to open file" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Encoding " << inputFileName << " ...\n";
  encode(inputFile, encodedFile);
}