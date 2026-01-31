#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

const string BASE_PATH = "data/performance/";
const int START_N = 10000;
const int NUM_ITERATIONS = 10;

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

// Best Case: Mảng đã sắp xếp
void genBest(int n)
{
    vector<int> data(n);
    for (int i = 0; i < n; ++i)
        data[i] = i;
    saveToFile("best_" + to_string(n) + ".txt", data);
}

// Avg Case: Mảng ngẫu nhiên
void genAvg(int n)
{
    vector<int> data(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10000000); // Tăng range số lên để tránh trùng lặp quá nhiều ở N lớn
    for (int i = 0; i < n; ++i)
        data[i] = dis(gen);
    saveToFile("avg_" + to_string(n) + ".txt", data);
}

// Worst Case: Mảng xen kẽ
void genWorst(int n)
{
    vector<int> data(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> noise(-5, 5);

    for (int i = 0; i < n; i += 2)
    {
        data[i] = (i * 10) + noise(gen);
        if (i + 1 < n)
        {
            data[i + 1] = (i * 10) - 20 + noise(gen);
        }
    }
    saveToFile("worst_" + to_string(n) + ".txt", data);
}

int main()
{
    cout << "========== START TO GENERATE DATA ==========" << endl;

    long long current_n = START_N;

    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        cout << "[" << (i + 1) << "/10] Executing N = " << current_n << "..." << endl;
        genBest(current_n);
        genAvg(current_n);
        genWorst(current_n);

        current_n *= 2;
    }

    cout << "========== COMPLETE ==========" << endl;
    return 0;
}