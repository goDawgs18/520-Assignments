#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);
    TypedArray(const TypedArray& other, const int length);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;
    int size() const;
    //make sure to add size testing on these methods
    ElementType &pop();
    ElementType &pop_front();

    int getcapacity() const;
    int getorigin() const;
    int getend() const;

    // Setters
    void set(int index, ElementType value);
    void push(ElementType value);
    void push_front(ElementType value);

private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};

template <typename ElementType>
int TypedArray<ElementType>::getcapacity() const {
    return this->capacity;
}

template <typename ElementType>
int TypedArray<ElementType>::getorigin() const {
    return this->origin;
}

template <typename ElementType>
int TypedArray<ElementType>::getend() const {
    return this->end;
}




template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other, const int length) {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;
    for (int i = 0; i < length; i++) {
        set(i, other.get(i));
    }
    destory(other);
}

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

// Assignment operator: i.e TypedArray b = a 
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    } 
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

template <typename ElementType>
ElementType& TypedArray<ElementType>::pop() {
    if (size() == 0) {
        throw std::range_error("Empty array");
    }
    ElementType &value = get(size()-1);
    end--;
    //need to figure out how to delete it after
    return value;
}

template <typename ElementType>
ElementType &TypedArray<ElementType>::pop_front() {
    if (size() == 0) {
        throw std::range_error("Empty array");
    }
    ElementType& e = get(0);
    //need to figure out how to delete it after
    origin++;
    return e;
}


// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

template <typename ElementType>
void TypedArray<ElementType>::push(ElementType value) {
    if (size() == this->capacity) {
        extend_buffer();
    }
    set(size(), value);
}

template <typename ElementType>
void TypedArray<ElementType>::push_front(ElementType value) {
    // assert(da->buffer != NULL);
    // while ( da->origin == 0 ) {
    //     extend_buffer(da);
    // }
    // da->origin--;
    
    while (this->origin == 0) {
        this->extend_buffer();
    }
    this->origin--;
    set(0, value);
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}

// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}

#endif