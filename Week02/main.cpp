/*
* SDEV 345 Week 2
* Binary Search
* Locates the value and index of 9.2 in list [4.5,6,1,9.2,4,77,1200,16.4]
* Ben Lovy
* January 21, 2020
*/

#include <iostream>

const int INPUT_LENGTH = 8;

template <class T>
class OrderedArray
{
    T *arr;
    int size;

public:
    OrderedArray();
    void display();
    void insert(T);
};

template <class T>
OrderedArray<T>::OrderedArray()
{
    arr = nullptr;
    size = 0;
}

template <class T>
void OrderedArray<T>::display()
{
    using std::cout;
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

template <class T>
void OrderedArray<T>::insert(T val)
{
    // TODO search for right location
    arr[size] = val;
    size++;
}

int main()
{
    using std::cout;

    // Initialize OrderedArray class
    OrderedArray<double> oa = OrderedArray<double>();

    // Add data - TODO move to method?
    double inputs[INPUT_LENGTH] = {4.5, 6, 1, 9.2, 4, 77, 1200, 16.4};
    for (auto n : inputs)
        oa.insert(n);

    cout << "Binary Search\n";
    oa.display();
}
