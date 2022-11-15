#ifndef ITERATOR_H
#define ITERATOR_H

#include<iostream>

template<class Object> 
class Iterator{
    public:
        using size_type = std::size_t;
        using index_type = std::size_t;
        using value_type = typename Object::value_type;
        using pointer = value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;

        Iterator();
        Iterator(pointer address);

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        reference operator[](index_type index);
        const_reference operator[](index_type index) const;

        pointer operator->();
        reference operator*();

        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);


    private:
        pointer address_;
};

template<class Object>
Iterator<Object>::Iterator()
    : address_(nullptr) {}

template<class Object>
Iterator<Object>::Iterator(pointer address)
    : address_(address) {}


template<class Object> 
Iterator<Object>& Iterator<Object>::operator++(){
    ++address_;
    return *this;
}

template<class Object>
Iterator<Object> Iterator<Object>::operator++(int){
    Iterator copy = *this;
    ++(*this);
    return copy;
}

template<class Object>
Iterator<Object>& Iterator<Object>::operator--(){
    --address_;
    return *this;
}

template<class Object>
Iterator<Object> Iterator<Object>::operator--(int){
    Iterator copy = *this;
    --(*this);
    return copy;
}

template<class Object>
typename Iterator<Object>::reference Iterator<Object>::operator[](index_type index){
    return *(address_ + index);
}


template<class Object>
typename Iterator<Object>::const_reference Iterator<Object>::operator[](index_type index) const{
    return *(address_ + index);
}

template<class Object>
typename Iterator<Object>::pointer Iterator<Object>::operator->(){
    return address_;
}

template<class Object>
typename Iterator<Object>::reference Iterator<Object>::operator*(){
    return *address_;
}

template<class Object>
bool Iterator<Object>::operator == (const Iterator<Object>& other){
    return address_ == other.address_;
}

template<class Object>
bool Iterator<Object>::operator != (const Iterator<Object>& other){
    return !(*this == other);
}

#endif