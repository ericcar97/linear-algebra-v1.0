#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include<iostream>
#include "iterator.h"

template<typename T, std::size_t ... Sizes> class Array;
template<typename T>
class Array<T>{
    public:
        using size_type = std::size_t;
        using index_type = std::size_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using initializer = std::initializer_list<T>;
        using iterator = Iterator<Array<T>>;

        size_type size() const;
        size_type capacity() const;

        iterator begin() const;
        iterator end() const;

        Array();
        Array(size_type size);
        Array(initializer list);
        
        Array(const Array& other);
        Array(Array&& other);

        virtual ~Array();

        Array& operator = (const Array& other);
        Array& operator = (Array&& other) noexcept;

        reference operator[](index_type index);
        const_reference operator[](index_type index) const;

        void append(const_reference element);
        void append(value_type&& element);


    private:
        size_type size_;
        size_type capacity_;
        pointer data_;

        void reallocate(size_type capacity);
    
    //////////////////////////////////////////
    template<typename U>
    friend void swap(Array<U>& lhs, Array<U> rhs);

};

template<typename T>        
typename Array<T>::size_type Array<T>::size() const{
    return size_;
}

template<typename T>
typename Array<T>::size_type Array<T>::capacity() const {
    return capacity_;
}

template<typename T>
typename Array<T>::iterator Array<T>::begin() const{
    return data_;
}

template<typename T>
typename Array<T>::iterator Array<T>::end() const{
    return data_ + size_;
}

template<typename T>
Array<T>::Array()
    : size_(0)
    , capacity_(10)
    , data_(nullptr) {}

template<typename T>
Array<T>::Array(size_type size)
    : size_(size)
    , capacity_(size)
    , data_(new value_type[size]()) {} 

template<typename T>
Array<T>::Array(initializer list)
    : size_(list.size())
    , capacity_(list.size())
    , data_(new value_type[size_]()) {
        std::copy(list.begin(), list.end(), this->begin());
    }


//Copy and move constructor

template<typename T>
Array<T>::Array(const Array<T>& other)
    : size_(other.size_)
    , capacity_(other.capacity_)
    , data_(new value_type[other.size_]()){
        std::copy(other.data_, other.data_ + size_, data_);
        //std::cout << "copy constructor"<< std::endl;

}

template<typename T>
Array<T>::Array(Array<T>&& other)
    : size_(std::move(other.size_))
    , capacity_(std::move(other.capacity_))
    , data_(std::move(other.data_)){
        //std::cout << "move constructor"<< std::endl;
    }


template<typename T>
Array<T>::~Array(){
    delete[] data_;
    //std::cout << "destructor"<< std::endl;
}

//Copy and move assignment 

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other){
    swap(*this,other);
    //std::cout << "copy assignment" << std::endl;
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept{
    size_ = std::move(other.size_);
    capacity_ = std::move(other.capacity_);
    data_ = std::move(other.data_);
    //std::cout << "move assignment"<< std::endl;
    return *this;
}


// subscript operators

template<typename T>
typename Array<T>::reference Array<T>::operator[](index_type index){
    return *(data_ + index);
}

template<typename T>
typename Array<T>::const_reference Array<T>::operator[](index_type index) const{
    return *(data_ + index);
}

template<typename T>
void Array<T>::reallocate(size_type capacity){
    pointer data = new value_type[capacity]();
    size_type size = size_;

    if(capacity < size){
        size_ = capacity;
    }

    for(index_type index = 0; index < size; index++){
        data[index] = std::move(data[index]);
    }
        
    delete[] data_;

    capacity_ = capacity;
    data_ = data;
}

template<typename T>
void Array<T>::append(const_reference element){
    if(size_ == capacity_){
        reallocate(2*capacity_);
    }
    data_[size_++] = element;
}


template<typename T>
void Array<T>::append(value_type&& element){
    if(size_ == capacity_){
        reallocate(2*capacity_);
    }
    data_[size_++] = std::move(element);
}


template<typename U>
void swap(Array<U>& lhs, Array<U> rhs){
        std::swap(lhs.size_, rhs.size_);
        std::swap(lhs.data_, rhs.data_);
}

#endif
