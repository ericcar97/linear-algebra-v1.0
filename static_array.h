#ifndef STATIC_ARRAY
#define STATIC_ARRAY


#include<iostream>
#include "iterator.h"

template<typename T, std::size_t ... Sizes> class Array;
template<typename T, std::size_t Size>
class Array<T,Size>{
    public:
        using size_type = std::size_t;
        using index_type = std::size_t;
        using value_type = T;
        using array_type = T[Size];
        using pointer = value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using initializer = std::initializer_list<T>;
        using iterator = Iterator<Array<T,Size>>;
        
        iterator begin();
        iterator end();

        size_type size() const {return Size;}

        Array();
        Array(initializer list);

        reference operator[](index_type index);
        const_reference operator[](index_type index) const;

    private:
        array_type data_ = {};
};

template<typename T, std::size_t Size>
typename Array<T,Size>::iterator Array<T,Size>::begin(){
    return data_;
}

template<typename T, std::size_t Size>
typename Array<T,Size>::iterator Array<T,Size>::end(){
    return data_ + Size;
}
template<typename T, std::size_t Size>
Array<T,Size>::Array(){} 

template<typename T, std::size_t Size>
Array<T,Size>::Array(initializer list){
    std::copy(list.begin(), list.end(), data_);
}

template<typename T, std::size_t Size>
typename Array<T,Size>::reference Array<T,Size>::operator[](index_type index){
    return *(data_ + index);
}

template<typename T, std::size_t Size>
typename Array<T,Size>::const_reference Array<T,Size>::operator[](index_type index) const{
    return *(data_ + index);
}

template<typename T, std::size_t Rows, std::size_t Columns>
class Array<T,Rows,Columns>{
    public:
        using size_type = std::size_t;
        using index_type = std::size_t;
        using value_type = T;
        using row_type = typename Array<T,Columns>::array_type;
        using array_type = row_type[Rows];
        using nested_initializer = std::initializer_list<std::initializer_list<T>>;
        using iterator = Iterator<Array<T,Rows,Columns>>;

        iterator begin() const;
        iterator end() const;

        size_type rows() const {return Rows;}
        size_type columns() const {return Columns;}

        Array();
        Array(nested_initializer list);
        row_type& operator[](index_type index){return *(data_ + index);}
        const row_type& operator[](index_type index) const {return *(data_ + index);}
    private:
        array_type data_ = {};
};

template<typename T, std::size_t Rows, std::size_t Columns>
typename Array<T,Rows,Columns>::iterator Array<T,Rows,Columns>::begin() const{
    return *data_;
}

template<typename T, std::size_t Rows, std::size_t Columns>
typename Array<T,Rows,Columns>::iterator Array<T,Rows,Columns>::end() const{
    return *(data_ + Rows);
}

template<typename T, std::size_t Rows, std::size_t Columns>
Array<T,Rows,Columns>::Array(){}

template<typename T, std::size_t Rows, std::size_t Columns>
Array<T,Rows,Columns>::Array(nested_initializer list){
    index_type row = 0;
    for(auto line : list){
        std::copy(line.begin(), line.end(), data_[row++]);
    }
}

template<typename T, std::size_t First, std::size_t Second, std::size_t ... Rest>
struct Array<T, First, Second, Rest...>{
        using size_type = std::size_t;
        using squeezed_array = typename Array<T,Second,Rest...>::array_type;
        using array_type = squeezed_array[First];
        using iterator = Iterator<Array<T,First,Second,Rest...>>;

        iterator begin(){return *data;}
        iterator end(){return *(data + Second);}

        squeezed_array& operator[](size_type index) {return *(data + index);}
        const squeezed_array& operator[](size_type index) const {return *(data + index);}
        array_type data = {};
};

////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Matrix////////////////////////////


#endif