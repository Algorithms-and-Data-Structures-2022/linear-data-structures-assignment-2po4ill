#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    capacity_ = capacity;
    data_ = new int[capacity_];
    for (int i = 0; i < capacity_; i++) {
      data_[i] = 0;
    }
  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;
    delete data_;
    data_ = nullptr;
  }


  void DynamicArray::Add(int value) {
    size_++;
    if (size_ > capacity_)
    {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }
    data_[size_ - 1] = value;
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index < size_ && index >= 0)
    {
      size_++;
      if (size_ > capacity_)
      {
        Resize(capacity_ + kCapacityGrowthCoefficient);
      }
      int* arr = new int[capacity_];
      for (int i = 0; i < size_; i++)
      {
        if (i > index)
        {
          arr[i] = data_[i+1];
        }
        else if (i == index)
        {
          arr[i] = value;
        }
        else
        {
          arr[i] = data_[i];
        }
      }
      int* data_ = new int[capacity_];
      for (int i = 0; i < size_; i++)
      {
        data_[i] = arr[i];
      }
      return true;
    }
    return false;
  }

  bool DynamicArray::Set(int index, int new_value) {
    for (int i = 0; i < size_; i++)
    {
      if (i == index)
      {
        data_[i] = new_value;
        return true;
      }
    }
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    int size1 = size_;
    int val;
    for (int i = index; i < size_; i++)
    {
      if (i = index)
      {
        val = data_[i];
        size_ -= 1;
      }
      data_[i] = data_[i+1];
    }
    if (size1 != size_)
    {
      return val;
    }
    return std::nullopt;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    for (int i = 0; i < size_; i++)
    {
      if (i == index) {
        return data_[i];
      }
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i++)
    {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; i++)
    {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    if (size_ == 0)
    {
      return true;
    }
    return false;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity > capacity_)
    {
      int* arr = new int[new_capacity];
      for (int i = 0; i < capacity_; i++) {
        arr[i] = data_[i];
      }
      for (int j = capacity_; j < new_capacity; j++) {
        arr[j] = 0;
      }
      int* data_ = new int[new_capacity];
      for (int x = 0; x < new_capacity; x++) {
        data_[x] = arr[x];
      }
      return true;
    }

    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment