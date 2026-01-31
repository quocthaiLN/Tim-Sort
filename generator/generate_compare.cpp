#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

const string BASE_PATH = "data/compare/";
const int START_N = 10000;
const int NUM_ITERATIONS = 15;

void saveToFile(const string &fileName, const vector<int> &data)
{
    ofstream file(BASE_PATH + fileName);
    if (!file.is_open())
    {
        cerr << "[Error]: Cannot open file: " << fileName << endl;
        exit(1);
    }
    file << data.size() << "\n";
    for (int i = 0; i < data.size(); ++i)
    {
        file << data[i] << (i == data.size() - 1 ? "" : " ");
    }
    file.close();
    cout << ">> Generated: " << fileName << " (Size: " << data.size() << ")" << endl;
}

// Avg Case (Adaptive): Nhiều RUN tăng + nhiễu nhẹ
void genAvg(int n)
{
    vector<int> data;
    data.reserve(n);

    random_device rd;
    mt19937 gen(rd());

    const int MIN_RUN = 32; // Giá trị gần với minRun của TimSort
    uniform_int_distribution<> runLenDis(MIN_RUN, MIN_RUN * 2);
    uniform_int_distribution<> noiseDis(-5, 5);

    int currentValue = 0;

    while ((int)data.size() < n)
    {
        int runLength = runLenDis(gen);
        if (data.size() + runLength > n)
            runLength = n - data.size();

        // Tạo 1 RUN tăng
        for (int i = 0; i < runLength; ++i)
        {
            data.push_back(currentValue++);
        }

        // Phá nhẹ trật tự để tránh best-case tuyệt đối
        if (runLength >= 4)
        {
            int pos = data.size() - 2;
            data[pos] += noiseDis(gen);
        }

        // Nhảy giá trị để tránh các RUN liền kề quá đều
        currentValue += uniform_int_distribution<>(10, 50)(gen);
    }

    saveToFile("size_" + to_string(n) + ".txt", data);
}

int main()
{
    cout << "========== START TO GENERATE DATA ==========" << endl;

    long long current_n = START_N;

    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        cout << "[" << (i + 1) << "/15] Executing N = " << current_n << "..." << endl;
        genAvg(current_n);

        current_n *= 2;
    }

    cout << "========== COMPLETE ==========" << endl;
    return 0;
}