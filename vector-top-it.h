//
// Created by platon on 23.03.2026.
//

#ifndef INC_23_03_2026_VECTOR_TOP_IT_H
#define INC_23_03_2026_VECTOR_TOP_IT_H
namespace topit {
    template<class T>
    struct Vector {
        T* data;
        size_t size;
        size_t capacity;

    };
    template<class T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
}

#endif //INC_23_03_2026_VECTOR_TOP_IT_H