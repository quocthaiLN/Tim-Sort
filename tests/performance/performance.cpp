#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>
#include "../../src/timSort.h"

using namespace std;
using namespace std::chrono;

const string BASE_PATH = "data/performance/";
const int START_N = 10000;
const int MAX_N = 5120000;

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
         << " | " << setw(12) << "Best Case"
         << " | " << setw(12) << "Avg Case"
         << " | " << setw(12) << "Worst Case" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int n = START_N; n <= MAX_N; n *= 2)
    {
        // Xây dựng tên file tương ứng với N
        string fBest = "best_" + to_string(n) + ".txt";
        string fAvg = "avg_" + to_string(n) + ".txt";
        string fWorst = "worst_" + to_string(n) + ".txt";

        // Đo Best, Avg, Worst Case
        vector<int> dBest = loadData(fBest);
        double tBest = measure(dBest);

        vector<int> dAvg = loadData(fAvg);
        double tAvg = measure(dAvg);

        vector<int> dWorst = loadData(fWorst);
        double tWorst = measure(dWorst);

        cout << left << setw(10) << n
             << " | " << setw(12) << tBest
             << " | " << setw(12) << tAvg
             << " | " << setw(12) << tWorst << endl;
    }
    return 0;
}