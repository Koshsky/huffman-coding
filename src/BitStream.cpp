#include "BitStream.h"

BitStream::BitStream(std::fstream &file, bool log) :
  file_(file),
  data_(0),
  pos_(0),
  log_(log)
{}

BitStream::~BitStream()
{
  flush();
}

ErrorCode BitStream::readBit(std::int32_t &bit)
{
  if (pos_ == 0)
  {
    file_.read(reinterpret_cast<char *>(&data_), sizeof(data_));
    if (!file_)
      return ErrorCode::ReadError;
    pos_ = BUFFER_SIZE;
  }

  bit = (data_ >> --pos_) & 1;
  if (log_)
    std::cout << bit;
  return ErrorCode::NoError;
}

void BitStream::writeBit(std::int32_t bit)
{
  if (pos_ == BUFFER_SIZE)
  {
    file_.write(reinterpret_cast<const char *>(&data_), sizeof(data_));
    data_ = 0;
    pos_ = 0;
  }
  if (log_)
    std::cout << bit;
  data_ = bit | (data_ << 1);
  ++pos_;
}

ErrorCode BitStream::readByte(uint8_t &byte) {
  byte = 0;
  for (int i = 0; i < BUFFER_SIZE; ++i) {
    byte <<= 1;
    int bit;
    if (readBit(bit) == ErrorCode::ReadError) {
      return ErrorCode::ReadError;
    }
    byte |= bit;
  }

  return ErrorCode::NoError;
}

void BitStream::writeByte(std::uint8_t byte)
{
  std::bitset<BUFFER_SIZE> bits(byte);
  for (int i = BUFFER_SIZE - 1; i >= 0; --i)
  {
    writeBit(bits[i]);
  }
}

void BitStream::flush()
{
  data_ = data_ << (BUFFER_SIZE - pos_);
  file_.write(reinterpret_cast<const char *>(&data_), sizeof(data_));
}
