#include <iostream>

int partition(int arr[], int low, int high)
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

void quicksort(int arr[], int low, int high)
{
        if (low < high)
        {
            int partitionIdx = partition(arr, low, high);
            quicksort(arr, low, partitionIdx - 1);
            quicksort(arr, partitionIdx + 1, high);
        }
}

template <typename T>
void showArr(T arr[], int size)
{
    using std::cout;
    cout << "[";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i < size - 1)
        {
            cout << ", ";
        }
    }
    cout << "]";
}

int main()
{
    int nums[6] = {3, 6, 5, 2, 1, 4};
    showArr(nums, 6);
    quicksort(nums, 0, 5);
    showArr(nums, 6);
    return 0;
}