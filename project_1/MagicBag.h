#pragma once

//Programmer-tested
//Valgrind-approved

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>

#define DEFAULT_CAPACITY 10

template<class T> class MagicBag
{
public:

    MagicBag()
    {
        //seed the PRNG
        srand((unsigned int)time(nullptr));

        //set sane default values
        this->size = 0;
        this->capacity = DEFAULT_CAPACITY;
        contents = new T[DEFAULT_CAPACITY];
    }

    MagicBag(int initialCapacity)
    {
        //seed the PRNG
        srand((unsigned int)time(nullptr));

        //set initial values
        this->size = 0;
        this->capacity = initialCapacity;
        contents = new T[capacity];
    }
    
    MagicBag(const MagicBag& other)
    {
        //seed the PRNG
        srand((unsigned int)time(nullptr));

        //copy the bag contents
        size = other.size;
        capacity = other.capacity;
        contents = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            contents[i] = other.contents[i];
        }
    }
    
    ~MagicBag()
    {
        //we only need to clean up our array
        delete[] contents;
    }

    MagicBag& operator=(const MagicBag& other)
    {
        //copy-and-swap
        MagicBag copy(other);
        swap(*this, copy);

        return *this;
    }

    void swap(MagicBag& a, MagicBag& b)
    {
        //swap the member variables (just pointers/primitives)
        std::swap(a.size, b.size);
        std::swap(a.capacity, b.capacity);
        std::swap(a.contents, b.contents);
    }

    void insert(T item)
    {
        //check if we need to allocate more memory
        if (capacity < (size + 1)) {
            /*
             * This is the JDK's method of doing this in ArrayList
             * It's equivalent to 'capacity *= 1.5;'
             * (capacity >> 1) is the same as capacity/2, but faster to perform
             * than a division.
             * I trust the factor of 1.5 to be a good choice if the JDK
             * developers find that they believe it is after having many years
             * to try to optimize the ArrayList class.
             */
            capacity = capacity + (capacity >> 1);

            /*
             * I just want to make a quick note here that I'm really sad that
             * there isn't an equivalent to realloc in C++.
             */
            //create a new, larger array
            T *newContents = new T[capacity];
            //copy the array contents
            for (int i = 0; i < size; i++)
            {
                newContents[i] = contents[i];
            }
            //replace the old array with the new one
            delete[] contents; //leave no memory behind
            contents = newContents;
        }

        //insert the new item
        contents[size] = item;
        size++;
    }

    T draw()
    {
        if (size == 0) throw "Empty array";

        //choose a random item
        int index = rand() % size;
        T item = contents[index];

        //overwrite the drawn item with the item in the last slot
        size--;
        contents[index] = contents[size];

        return item;
    }

    int peek(T item) const
    {
        int count = 0;
        
        for (int i = 0; i < size; i++)
        {
            if (contents[i] == item) count++;
        }

        return count;
    }

    void print(std::ostream& os) const
    {
        os << *this;
    }

private:

    int size;
    int capacity;
    T *contents;

    friend std::ostream& operator<<(std::ostream& os, const MagicBag& mb)
    {
        os << "{";
        for (int i = 0; i < (mb.size - 1); i++) os << mb.contents[i] << ", ";
        return os << mb.contents[mb.size - 1] << "}";
    }
};
