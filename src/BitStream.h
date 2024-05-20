#ifndef _BIT_STREAM_H
#define _BIT_STREAM_H

#include <fstream>
#include <bitset>
#include <iostream>
#include <stdexcept>
#include "constants.h"

class BitStream
{
public:
  BitStream(std::fstream &file);
  ~BitStream();

  ErrorCode readBit(std::int32_t &bit);
  void writeBit(std::int32_t bit);
  ErrorCode readByte(std::uint8_t &byte);
  void writeByte(std::uint8_t byte);

  void flush();

private:
  std::fstream &file_;
  std::uint8_t data_;
  int pos_;
};
#endif  // _BIT_STREAM_H
