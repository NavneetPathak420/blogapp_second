#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        int minIndex = i;
        for (int j = i+1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Insertion Sort
double insertionSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count() /1000000.0; // Convert to seconds
}

// Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSortHelper(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSortHelper(arr, l, m);
    mergeSortHelper(arr, m + 1, r);
    merge(arr, l, m, r);
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

// Function to measure time consumption
double measureTime(void (*sortFunction)(vector<int>&), vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count() / 1000000.0; // Convert to seconds
}

// Function to generate arrays for best, average, and worst cases
vector<int> generateSortedArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = i;
    return arr;
}

vector<int> generateReverseSortedArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = n - i;
    return arr;
}

vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % n;
    return arr;
}

int main() {
    srand(time(nullptr));
    const int n = 90000; // Size of array
    vector<int> bestCase = generateSortedArray(n);
    vector<int> worstCase = generateReverseSortedArray(n);
    vector<int> averageCase = generateRandomArray(n);

    // Measure time for each algorithm and each case
    cout << "Algorithm\tBest Case\tAverage Case\tWorst Case\n";
    cout << "Bubble Sort\t" << measureTime(bubbleSort, bestCase) << "\t" << measureTime(bubbleSort, averageCase) << "\t" << measureTime(bubbleSort, worstCase) << endl;
    cout << "selection sort\t"<< measureTime(selectionSort, bestCase)<<"\t"<< measureTime(selectionSort, averageCase)<<"\t" << measureTime(selectionSort, worstCase) << endl;
    cout << "Insertion Sort\t" << insertionSort(bestCase) << "\t" << insertionSort(averageCase) << "\t" << insertionSort(worstCase) << endl;
    cout << "Merge Sort\t" << measureTime(mergeSort, bestCase) << "\t" << measureTime(mergeSort, averageCase) << "\t" << measureTime(mergeSort, worstCase) << endl;
    cout << "Quick Sort\t" << measureTime(quickSort, bestCase) << "\t" << measureTime(quickSort, averageCase) << "\t" << measureTime(quickSort, worstCase) << endl;

    return 0;
}
