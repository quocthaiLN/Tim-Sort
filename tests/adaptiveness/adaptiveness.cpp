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

// Hàm load dữ liệu từ file
bool loadData(const string &fileName, vector<int> &data, int &n)
{
    string fullPath = FOLDER_PATH + fileName;
    ifstream inFile(fullPath);

    if (!inFile.is_open())
    {
        cerr << "[Error]: Can not open file " << fullPath << endl;
        return false;
    }

    inFile >> n;
    data.resize(n);
    for (int i = 0; i < n; ++i)
    {
        inFile >> data[i];
    }
    inFile.close();
    return true;
}

// Hàm benchmark
void benchmark(const string &caseName, const string &fileName)
{

    vector<int> data;
    int n;
    if (!loadData(fileName, data, n))
        return;

    cout << "Testing " << caseName << " (N=" << n << ")..." << flush;

    auto start = high_resolution_clock::now();

    timSort(data, n);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    double ms = duration.count() / 1000.0;

    cout << "\r";
    cout << left << setw(15) << caseName
         << "| Time: " << fixed << setprecision(3) << setw(8) << ms << " ms "
         << "| File: " << fileName << endl;
}

int main()
{
    cout << "================ TIMSORT BENCHMARK ================" << endl;
    cout << "Unit: milisecond (ms)\n"
         << endl;

    benchmark("BEST CASE", FILE_BEST);
    benchmark("AVERAGE CASE", FILE_AVG);
    benchmark("WORST CASE", FILE_WORST);

    cout << "==================================================================" << endl;
    return 0;
}