#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>

const std::size_t INITIAL_CAPACITY = 8;

template <typename T>
class Vector
{
public:
  Vector();
  Vector(Vector &&other);
  Vector &operator=(Vector &&other) = delete;
  Vector(const Vector &other);
  Vector &operator=(const Vector &other) = delete;
  virtual ~Vector();

  void push_back(T data);
  T pop_back();
  std::size_t find(const T &el) const;
  T &operator [](std::size_t index);
  const T &operator [](std::size_t index) const;
  std::size_t size() const;
  bool empty() const;
  std::size_t capacity() const;
  void resize(std::size_t new_size);

private:
  T *array_;
  std::size_t size_;
  std::size_t capacity_;
};

template <typename T>
std::size_t Vector<T>::find(const T &el) const
{
  for (std::size_t i = 0; i < size_; ++i)
  {
    if (array_[i] == T)
    {
      return i;
    }
  }
  return -1;
}

template <typename T>
Vector<T>::Vector() :
  size_(0),
  capacity_(INITIAL_CAPACITY),
  array_(new T[INITIAL_CAPACITY])
{
}

template<typename T>
inline Vector<T>::Vector(Vector &&other):
  size_(0),
  capacity_(0),
  array_(nullptr)
{
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(array_, other.array_);
}

template<typename T>
inline Vector<T>::Vector(const Vector &other):
  size_(other.size_),
  capacity_(capacity_),
  array_(new T[other.capacity_])
{
  for (size_t i = 0; i < size_; ++i)
    array_[i] = other.array_[i];
}

template <typename T>
Vector<T>::~Vector()
{
  if (array_ != nullptr)
  {
    delete[] array_;
  }
}

template <typename T>
void Vector<T>::push_back(T data)
{
  if (size_ == capacity_)
  {
    resize(capacity_ * 2);
  }
  if (size_ < capacity_)
  {
    array_[size_++] = data;
  }
}

template <typename T>
T Vector<T>::pop_back()
{
  if (empty())
  {
    throw std::runtime_error("Vector is empty");
  }
  return array_[--size_];
}

template <typename T> void Vector<T>::resize(std::size_t newSize) {
  if (newSize > capacity_) {
    T *tempPtr = new T[newSize];
    for (std::size_t i = 0; i < size_; ++i) {
      tempPtr[i] = array_[i];
    }
    capacity_ = newSize;
    std::swap(array_, tempPtr);
    delete[] tempPtr;
  }
  else {
    size_ = newSize;
  }
}

template <typename T>
T &Vector<T>::operator [](std::size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Index is out of range");
  }
  return array_[index];
}
template <typename T>
const T &Vector<T>::operator [](std::size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Index is out of range");
  }
  return array_[index];
}

template <typename T>
std::size_t Vector<T>::size() const
{
  return size_;
}
template <typename T>
bool Vector<T>::empty() const
{
  return size_ == 0;
}
template <typename T>
std::size_t Vector<T>::capacity() const
{
  return capacity_;
}
#endif  // _VECTOR_HPP
