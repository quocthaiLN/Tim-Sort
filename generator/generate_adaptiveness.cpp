#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

const int N = 10000;

const string BASE_PATH = "data/adaptiveness/";
const string PATH_BEST = "best_case.txt";
const string PATH_WORST = "worst_case.txt";
const string PATH_AVG = "avg_case.txt";

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
void genBest()
{
    vector<int> data(N);
    for (int i = 0; i < N; ++i)
    {
        data[i] = i;
    }
    saveToFile(PATH_BEST, data);
}

// Avg Case: Mảng ngẫu nhiên
void genAvg()
{
    vector<int> data(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100000);

    for (int i = 0; i < N; ++i)
    {
        data[i] = dis(gen);
    }
    saveToFile(PATH_AVG, data);
}

// Worst Case: Mảng xen kẽ
void genWorst()
{
    vector<int> data(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> noise(-5, 5);

    for (int i = 0; i < N; i += 2)
    {
        data[i] = (i * 10) + noise(gen);
        if (i + 1 < N)
        {
            data[i + 1] = (i * 10) - 20 + noise(gen);
        }
    }
    saveToFile("worst_case.txt", data);
}

int main()
{
    cout << "========== START TO GENERATE DATA ==========" << endl;

    genBest();
    genAvg();
    genWorst();

    cout << "========== COMPLETE ==========" << endl;
    return 0;
}