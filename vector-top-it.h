#include <cstddef>
#include <stdexcept>
#include <__functional/function.h>
#ifndef VECTOR_TOP_IT_H
#define VECTOR_TOP_IT_H

namespace topit {
    template<class T>
    struct Vector {
        Vector();
        explicit Vector(size_t s);
        Vector(size_t s, const T& val);
        ~Vector();

        Vector(const Vector &rhs);
        Vector& operator=(const Vector &rhs);
        Vector(Vector &&rhs) noexcept;
        Vector& operator=(Vector &&rhs) noexcept;
        void swap(Vector &rhs) noexcept;

        bool isEmpty() const noexcept;
        size_t getSize() const noexcept;
        size_t getCapacity() const noexcept;

        T& operator[](size_t i) noexcept;
        const T& operator[](size_t i) const noexcept;
        T& at(size_t i);
        const T& at(size_t i) const;

        void pushBack(const T& val);
        void pushFront(const T& val); // + тесты

        // классная работа (copy & swap) + тесты
        void insert(size_t pos, const T& val);
        void insert(size_t pos, const Vector<T> &rhs, size_t b, size_t e);
        void erase(size_t pos);

        // дз
        // Итераторы для вектора (итераторы без тестов)
        // По 3 штуки insert/erase c итераторами (в сумме 6)
        struct VectorIterator;
        void insert(VectorIterator pos, const T& val);
        void erase(VectorIterator pos);

        private:
         T* data_;
         size_t size_;
         size_t capacity_;

    };

    template<class T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);

    template<class T>
    bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);
}

template<class T>
topit::Vector<T>::Vector(const Vector& rhs) :
    Vector(rhs.getSize())
{
    for (size_t i = 0; i < rhs.getSize(); ++i) {
        data_[i] = rhs[i];
    }
}

template<class T>
topit::Vector<T>& topit::Vector<T>::operator=(const Vector &rhs)
{
    Vector cpy(rhs);
    swap(cpy);
    return *this;
}

template<class T>
topit::Vector<T>::Vector(Vector &&rhs) noexcept :
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
    rhs.data_ = nullptr;
}

template<class T>
topit::Vector<T> & topit::Vector<T>::operator=(Vector &&rhs) noexcept
{
    Vector cpy(rhs);
    swap(cpy);
    return *this;
}

template<class T>
void topit::Vector<T>::swap(Vector &rhs) noexcept
{
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
}

template<class T>
bool topit::Vector<T>::isEmpty() const noexcept
{
    return !size_;
}

template< class T >
size_t topit::Vector<T>::getSize() const noexcept
{
    return size_;
}

template< class T >
size_t topit::Vector<T>::getCapacity() const noexcept
{
    return capacity_;
}

template<class T>
T& topit::Vector<T>::operator[](size_t i) noexcept
{
    return data_[i];
}

template<class T>
const T& topit::Vector<T>::operator[](size_t i) const noexcept
{
    return data_[i];
}

template<class T>
T& topit::Vector<T>::at(size_t i)
{
    return const_cast < T& > (static_cast< const Vector < T > &>(*this).at(i));
}

template<class T>
const T& topit::Vector<T>::at(size_t i) const
{
    if (i >= size_) {
        throw std::out_of_range("Index out of range");
    }

    return data_[i];
}

template<class T>
void topit::Vector<T>::pushBack(const T &val)
{
    if (size_ == capacity_) {
        size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    data_[size_++] = val;
}

template<class T>
void topit::Vector<T>::pushFront(const T &val)
{
    Vector result(getSize() + 1);
    result[0] = val;
    for (size_t i = 0; i < getSize(); ++i) {
        result[i + 1] = (*this)[i];
    }
    swap(result);
}

template<class T>
bool topit::operator==(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs.getSize() != rhs.getSize()) {
        return false;
    }

    for (size_t i = 0; i < lhs.getSize(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }

    return true;
}

template<class T>
bool topit::operator!=(const Vector<T> &lhs, const Vector<T> &rhs)
{
    return !(lhs == rhs);
}

template< class T >
topit::Vector<T>::Vector(size_t s) :
    data_(s ? new T[s] : nullptr),
    size_(s),
    capacity_(s)
{}

template<class T>
topit::Vector<T>::Vector(size_t s, const T &val) :
    Vector(s)
{
    for (size_t i = 0; i < s; ++i) {
        data_[i] = val;
    }
}

template<class T>
topit::Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template<class T>
topit::Vector<T>::~Vector() {
    delete[] data_;
}
#endif
