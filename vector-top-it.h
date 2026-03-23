#include <cstddef>
#include <stdexcept>
#ifndef VECTOR_TOP_IT_H
#define VECTOR_TOP_IT_H
namespace topit {
    template<class T>
    struct Vector {
        Vector();
        explicit Vector(size_t s);
        ~Vector();

        Vector(const Vector<T> &) = delete;
        Vector<T> &operator=(const Vector<T> &) = delete;

        bool isEmpty() const noexcept;
        size_t getSize() const noexcept;

        T& operator[](size_t i) noexcept;
        const T& operator[](size_t i) const noexcept;
        T& at(size_t i);
        const T& at(size_t i) const;

        private:
         T* data_;
         size_t size_;
         size_t capacity_;

    };

    template<class T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
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
    return static_cast < T& > (static_cast< const Vector * >(this)->at(i));
}

template<class T>
const T& topit::Vector<T>::at(size_t i) const
{
    if (i >= size_) {
        throw std::out_of_range("Index out of range");
    }

    return data_[i];
}

template< class T >
topit::Vector<T>::Vector(size_t s) :
    data_(s ? new T[s] : nullptr),
    size_(s),
    capacity_(s)
{}

template<class T>
topit::Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template<class T>
topit::Vector<T>::~Vector() {
    delete[] data_;
}
#endif