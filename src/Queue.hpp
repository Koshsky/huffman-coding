#ifndef _QUEUE_HPP
#define _QUEUE_HPP

#include <cstddef>
#include <algorithm>  // std::swap
#include <stdexcept>
#include "Vector.hpp"

template <typename T, typename Comparator = std::less<T>>
class PriorityQueue
{
public:
  void push(T newNum);
  void pop();
  T top() const;
  bool empty() const;
  std::size_t size() const;

private:
  Vector<T> data_;
  void heapify(std::size_t i);
  Comparator comp;
};

template <typename T, typename Comparator>
std::size_t PriorityQueue<T, Comparator>::size() const
{
  return data_.size();
}

template <typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename Comparator>
T PriorityQueue<T, Comparator>::top() const
{
  if (empty())
    throw std::runtime_error("Queue is empty");

  return data_[0];
}
template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::heapify(std::size_t i)
{
  std::size_t size = data_.size();

  std::size_t least = i;
  std::size_t l = 2 * i + 1;
  std::size_t r = 2 * i + 2;
  if (r < size && comp(data_[r], data_[least]))
    least = r;
  if (l < size && comp(data_[l], data_[least]))
    least = l;


  if (least != i)
  {
    std::swap(data_[i], data_[least]);
    heapify(least);
  }
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(T newNum)
{
  std::size_t size = data_.size();
  if (size == 0)
  {
    data_.push_back(newNum);
  }
  else
  {
    data_.push_back(newNum);
    for (std::size_t i = size / 2; i != 0; --i)
      heapify(i - 1);
  }
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::pop()
{
  std::swap(data_[0], data_[data_.size() - 1]);

  data_.pop_back();
  for (std::size_t i = data_.size() / 2; i != 0; i--)
    heapify(i - 1);
}
#endif  // _QUEUE_HPP
