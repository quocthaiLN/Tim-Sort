#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "../../src/timSort.h"

using namespace std;

const string DATA_PATH = "data/correctiveness/";

const string FILE_EMPTY = "empty.txt";
const string FILE_ONE_VALUE = "one_value.txt";
const string FILE_SAME_VALUES = "same_values.txt";
const string FILE_DESCENDING_ORDER = "descending_order.txt";
const string FILE_ASCENDING_ORDER = "ascending_order.txt";
const string FILE_RANDOM = "random.txt";

// Hàm tải dữ liệu từ file
bool loadData(const string &fileName, vector<int> &data, int &n)
{
    ifstream inFile(DATA_PATH + fileName);

    if (!inFile.is_open())
    {
        cerr << "[Error]: Can not open file: " << (DATA_PATH + fileName) << endl;
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

// Hàm chạy test cho từng file
void runTest(const string &fileName)
{
    cout << "--------------------------------------------------" << endl;
    cout << "Handling file: " << fileName << "..." << endl;

    vector<int> originalData;
    int n;

    if (!loadData(fileName, originalData, n))
    {
        return;
    }

    // Kết quả của Tim Sort tự triển khai
    vector<int> arrTimSort = originalData;
    // Kết quả của std::sort
    vector<int> arrStdSort = originalData;

    timSort(arrTimSort, n);

    sort(arrStdSort.begin(), arrStdSort.end());

    bool isCorrect = (arrTimSort.size() == arrStdSort.size()) &&
                     equal(arrTimSort.begin(), arrTimSort.end(), arrStdSort.begin());

    if (isCorrect)
    {
        cout << ">> RESULT: [PASS] (Correct)" << endl;
    }
    else
    {
        cout << ">> RESULT: [FAIL] (Incorrect)" << endl;
        if (n <= 20)
        {
            cout << "   Expected: ";
            for (int x : arrStdSort)
                cout << x << " ";
            cout << "\n   Reality: ";
            for (int x : arrTimSort)
                cout << x << " ";
            cout << endl;
        }
    }
}

int main()
{
    cout << "===== CORRECTNESS TEST =====" << endl;

    runTest(FILE_EMPTY);
    runTest(FILE_ONE_VALUE);
    runTest(FILE_SAME_VALUES);
    runTest(FILE_DESCENDING_ORDER);
    runTest(FILE_ASCENDING_ORDER);
    runTest(FILE_RANDOM);

    cout << "--------------------------------------------------" << endl;
    cout << "===== CORRECTNESS TEST COMPLETE =====" << endl;
    return 0;
}