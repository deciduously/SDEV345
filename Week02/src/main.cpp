/**
* SDEV 345 Week 2
* Binary Search
* Locates the value and index of 9.2 in list [4.5, 6, 1, 9.2, 4, 77, 1200, 16.4]
* Ben Lovy
* January 21, 2020
*/

#include <iostream> // std::cout

// [4.5, 6, 1, 9.2, 4, 77, 1200, 16.4]
const int INPUT_LENGTH = 8;

/** OrderedArray is a template class holding an array of elements ordered via <
Required overloads: operator<(), operator==()*/
template <class T>
class OrderedArray
{
    T arr[INPUT_LENGTH];
    int size;

public:
    /**Construct an empty orderded array*/
    OrderedArray();
    /**Display current array to stdout*/
    void display();
    /**Display result of searching for value in array
    \param value to search for*/
    void displayFind(T);
    /**Locate value, returning index
    \param value to search for*/
    int find(T);
    /**Insert value
    \param insert a value at the proper place*/
    void insert(T);
};

template <class T>
OrderedArray<T>::OrderedArray()
{
    size = 0;
}

template <class T>
void OrderedArray<T>::display()
{
    using std::cout;
    cout << "[ ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "]\n";
}

template <class T>
void OrderedArray<T>::displayFind(T val)
{
    using std::cout;

    cout << "Finding " << val << "...\n";
    cout << "index: " << find(9.2) << "\n";
}

template <class T>
int OrderedArray<T>::find(T val)
{
    // Initialize search range to beginning and end
    int l = 0;
    int h = size - 1;

    // Forever
    for (;;)
    {
        // Locate the middle
        int currIdx = (l + h) / 2;

        // Did we find it?
        if (arr[currIdx] == val)
            return currIdx;
        // did we overshoot?
        else if (l > h)
            return size; // cannot find
        else
        {
            // Binary search - restrict bounds for next iteration
            if (arr[currIdx] < val)
                l = currIdx + 1;
            else
                h = currIdx - 1;
        }
    }
}

template <class T>
void OrderedArray<T>::insert(T val)
{
    // Search for correct location
    int currIdx = 0;
    for (; currIdx < size; currIdx++)
    {
        if (arr[currIdx] > val)
            break;
    }
    // push everything up one, from the end
    for (int i = size; i > currIdx; i--)
        arr[i] = arr[i - 1];
    // insert val at currIdx
    arr[currIdx] = val;
    size++;
}

int main()
{
    using std::cout;

    // Initialize OrderedArray class
    OrderedArray<double> oa = OrderedArray<double>();

    // Add data to array
    cout << "Adding inputs: " << "\n";
    double inputs[INPUT_LENGTH] = {4.5, 6, 1, 9.2, 4, 77, 1200, 16.4};
    for (auto n : inputs)
    {
        cout << "Inserting " << n << "\n";
        oa.insert(n);
    }

    // Show results
    double needle = 9.2;
    cout << "Binary Search for " << needle << " in OrderedArray:\n";
    oa.display();
    oa.displayFind(needle);

    return 0;
}
