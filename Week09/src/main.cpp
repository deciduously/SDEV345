/**
* SDEV 345 Week 9
* Quicksort
* Populate an array of 250 values and quicksort them
* Ben Lovy
* March 18, 2020
*/

#include <random>
#include <iostream>

const int INPUT_LENGTH = 250;

/** Array is a template class holding an array of elements*/
class IntArray
{
    int arr[INPUT_LENGTH] = {};
    int size = 0;

    /*Perform quicksort partitioning using final element as pivot*/
    static int partition(int arr[], int low, int high)
    {
        using std::swap;
        // Select highest element
        int pivot = arr[high];
        // Index of smaller element
        int i = low - 1;
        // Traverse
        for (int j = low; j <= high - 1; j++)
        {
            // check against pivot
            if (pivot > arr[j])
            {
                // increment smaller idx
                i++;
                // swap i and j
                swap(arr[i], arr[j]);
            }
        }
        int ret = i + 1;
        swap(arr[ret], arr[high]);
        return ret;
    }

    /*perform quicksort on an array section*/
    static void quicksort(int arr[], int low, int high)
    {
        if (low < high)
        {
            int partitionIdx = partition(arr, low, high);
            quicksort(arr, low, partitionIdx - 1);
            quicksort(arr, partitionIdx + 1, high);
        }
    }

public:
    /**Randomly populate an array*/
    IntArray() = default;
    /**Insert value
    \param insert a value at the proper place*/
    void insert(int val)
    {
        // Unsorted - just pop it in
        arr[size] = val;
        size++;
    }
    /*Sorts stored array in place*/
    void sort()
    {
        quicksort(arr, 0, INPUT_LENGTH - 1);
    }
    friend std::ostream &operator<<(std::ostream &s, const IntArray &ia)
    {
        s << "[ ";
        for (int i = 0; i < ia.size; i++)
            s << ia.arr[i] << " ";
        s << "]\n";
        return s;
    }
};

int main()
{
    // Init array
    IntArray ia;

    // Populate array
    /*random seed*/
    std::random_device rd;
    /*seed rng*/
    std::mt19937 rng(rd());
    /*rng dist*/
    std::uniform_int_distribution dist(1, 999);
    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        ia.insert(dist(rng));
    }

    // Show unsorted
    std::cout << ia;

    // Sort
    std::cout << "Sorting...\n";
    ia.sort();

    // Show sorted
    std::cout << ia << "\n";

    // Output worst runtime info
    std::cout << "The worst case for this algorithm occurs when performed on an already sorted array, as the maximum number of swaps are performed.  If array were already sorted, this algorithms' time complexity is O(n^2).\n";
}