#include "QuickSort.h"

static int partition(vector<int> &a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i + 1], a[high]);
    return i + 1;
}

static void quickSortRec(vector<int> &a, int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, low, high);
        quickSortRec(a, low, pi - 1);
        quickSortRec(a, pi + 1, high);
    }
}

void quickSort(vector<int> &a, int n)
{
    quickSortRec(a, 0, n - 1);
}
