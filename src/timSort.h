#pragma once
#include <vector>
#include <bits/stdc++.h>
using namespace std;

static const int GALLOP_THRESHOLD = 7; // Chỉ là heraustic

struct Run
{
    int start;
    int length;
};

int computeMinRun(int n);

void insertionSort(vector<int> &a, int left, int right);

int gallopLeft(const vector<int> &a, int key, int base, int len);

void mergeRuns(vector<int> &a, Run left, Run right);

void mergeCollapse(vector<int> &a, vector<Run> &st);

void timSort(vector<int> &a, int n);