#include "Huffman.h"

#include <fstream>
#include <iostream>
#include <string>

void processEncode();
void processDecode();

int main(void) {

  char mode;
  std::cin >> mode;
  switch (mode)
  {
  case 'e':
    processEncode();
    break;
  case 'd':
    processDecode();
    break;
  default:
    std::cerr << "Invalid mode" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
void processEncode()
{
  std::string inputFileName;
  std::cout << "Enter inputFileName: ";
  std::cin >> inputFileName;
  std::string encodedFileName;
  std::cout << "Enter encodedFileName: ";
  std::cin >> encodedFileName;

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

void processDecode()
{
  std::string encodedFileName;
  std::cout << "Enter encodedFileName: ";
  std::cin >> encodedFileName;
  std::string outputFileName;
  std::cout << "Enter outputFileName: ";
  std::cin >> outputFileName;

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
