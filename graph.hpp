#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> topology = {
    {0, 1, 5, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 7, 5, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 7, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 3, 0, 0},
    {0, 0, 0, 0, 0, 3, 6, 9, 0},
    {0, 0, 0, 0, 0, 0, 0, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 2, 7},
    {0, 0, 0, 0, 0, 0, 0, 0, 4},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

vector<string> points = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"};

vector<vector<int>> transform(const vector<vector<int>>& src, vector<int> ids) {
    vector<vector<int>> ret;
    for (int i : ids) {
        vector<int> arr;
        for (int j : ids) {
            arr.push_back(src[i][j]);
        }
        ret.push_back(arr);
    }
    return ret;
}

void showMatrix(const vector<vector<int>>& metrix) {
    for (auto arr : metrix) {
        for (int j : arr) {
            cout << j << " ";
        }
        cout << endl;
    }
}