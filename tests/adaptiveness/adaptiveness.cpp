#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "../../src/timSort.h"

using namespace std;
using namespace std::chrono;

const string FOLDER_PATH = "data/adaptiveness/";
const string FILE_BEST = "best_case.txt";
const string FILE_AVG = "avg_case.txt";
const string FILE_WORST = "worst_case.txt";

// Hàm load dữ liệu
vector<int> loadData(const string &fileName)
{
    ifstream inFile(fileName);
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
    cout << left
         << " | " << setw(12) << "Best Case"
         << " | " << setw(12) << "Avg Case"
         << " | " << setw(12) << "Worst Case" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Xây dựng tên file tương ứng với N
    string fBest = FOLDER_PATH + "best_case.txt";
    string fAvg = FOLDER_PATH + "avg_case.txt";
    string fWorst = FOLDER_PATH + "worst_case.txt";

    // Đo Best, Avg, Worst Case
    vector<int> dBest = loadData(fBest);
    double tBest = measure(dBest);

    vector<int> dAvg = loadData(fAvg);
    double tAvg = measure(dAvg);

    vector<int> dWorst = loadData(fWorst);
    double tWorst = measure(dWorst);

    cout << left
         << " | " << setw(12) << tBest
         << " | " << setw(12) << tAvg
         << " | " << setw(12) << tWorst << endl;
    return 0;
}