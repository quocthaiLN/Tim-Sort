#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>
#include "../../src/timSort.h"
#include "../../src/mergeSort.h"
#include "../../src/quickSort.h"
#include "../../src/heapSort.h"

using namespace std;
using namespace std::chrono;

const string BASE_PATH = "data/compare/";
const int START_N = 10000;
const int MAX_N = 163840000;

// Hàm load dữ liệu
vector<int> loadData(const string &fileName)
{
    ifstream inFile(BASE_PATH + fileName);
    int n;
    inFile >> n;
    vector<int> data(n);
    for (int i = 0; i < n; ++i)
        inFile >> data[i];
    return data;
}

// Hàm đo thời gian trả về mili giây
double measure(vector<int> &data)
{
    int n = data.size();
    auto start = high_resolution_clock::now();

    timSort(data, n); // Chạy thuật toán

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count() / 1000.0;
}

int main()
{
    cout << "=================== RESULT TABLE (Unit: ms) ===================" << endl;
    cout << left << setw(10) << "Size (N)"
         << " | " << setw(12) << "Tim Sort"
         << " | " << setw(12) << "Merge Sort"
         << " | " << setw(12) << "Quick Sort"
         << " | " << setw(12) << "Heap Sort" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int n = START_N; n <= MAX_N; n *= 2)
    {
        // Xây dựng tên file tương ứng với N
        string fileName = "size_" + to_string(n) + ".txt";

        // Đo Best, Avg, Worst Case
        vector<int> dTim = loadData(fileName);
        double tTim = measure(dTim);
        vector<int> dMerge = loadData(fileName);
        double tMerge = measure(dMerge);
        vector<int> dQuick = loadData(fileName);
        double tQuick = measure(dQuick);
        vector<int> dHeap = loadData(fileName);
        double tHeap = measure(dHeap);

        cout << left << setw(10) << n
             << " | " << setw(12) << tTim
             << " | " << setw(12) << tMerge
             << " | " << setw(12) << tQuick
             << " | " << setw(12) << tHeap << endl;
    }
    return 0;
}