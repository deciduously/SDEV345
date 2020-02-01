/**
* SDEV 345 Week 3
* Binary Search
* Sort list [4.5, 6, 1, 9.2, 4, 77, 1200, 16.4] via insertion sort
* Ben Lovy
* February 1, 2020
*/

/*
* Big-O analysis
* This sorting algorithm runs in quadratic time, which is O(n^2).
* The worst-case input for this algorithm is an array in reverse order, or an
* array wherein each element is no bigger than one of the receeding values.
* On such an input this algorithm's inner loop has to traverse the entire
* already sorted section to move it where it neeeds to be in order to
* properly insert a new element.  This multiplies the runtime on each iteration
* instead of merely adding to it, resulting in O(n^2).
*/

#include <iostream> // std::cout

// [4.5, 6, 1, 9.2, 4, 77, 1200, 16.4]
const int INPUT_LENGTH = 8;

/** OrderedArray is a template class holding an array of elements ordered via <
Required overloads: operator<(), operator==()*/
template <class T>
class Array
{
    T arr[INPUT_LENGTH] = {};
    int size;

public:
    /**Construct an empty orderded array*/
    Array()
    {
        size = 0;
    }

    /**Display current array to stdout*/
    void display();
    /**Insert value
    \param insert a value at the proper place*/
    void insert(T val)
    {
        // Unsorted - just pop it in
        arr[size] = val;
        size++;
    }
    /**Sort array in place via insertion sort*/
    void insertionSort()
    {
        // Outer loup - start at first unsorted element
        // Init to second element for first run
        for (int out = 1; out < size; out++)
        {
            // Snag the current
            T tmp = arr[out];

            // Begin shifting at current location
            int in = out;
            // Shift forward until you find a smaller one
            while(in > 0 && arr[in-1] >= tmp)
            {
                // Move it up
                arr[in] = arr[in-1];
                // Seek left
                --in;
            }
            // Found our spot, insert held item
            arr[in] = tmp;
        }
    }
    friend std::ostream &operator<<(std::ostream &s, const Array<T> &a)
    {
        s << "[ ";
        for (int i = 0; i < a.size; i++)
            s << a.arr[i] << " ";
        s << "]\n";
        return s;
    }
};

int main()
{
    using std::cout;

    // Initialize Array class
    Array<double> a = Array<double>();

    // Add data to array
    cout << "Adding inputs: " << "\n";
    double inputs[INPUT_LENGTH] = {4.5, 6, 1, 9.2, 4, 77, 1200, 16.4};
    for (auto n : inputs)
    {
        cout << "Inserting " << n << "\n";
        a.insert(n);
    }

    // Show results
    cout << "Unsorted: " << a;
    // Sort
    a.insertionSort();
    // Show again
    cout << "Sorted: " << a;

    return 0;
}
