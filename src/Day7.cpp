//
// Created by popaa on 07/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    string input;
    vector<int> positions;
    int sum = 0;
    int average = 0;
    int middle;
    int steps;

    ifstream fin("../src/input.txt");

    while(getline(fin, input, ',')) {
        positions.push_back(stoi(input));
    }
    sort(positions.begin(), positions.end());
    middle = positions.size() / 2;

    for (auto p: positions) {
        sum += abs(p - positions[middle]);
        average += p;
    }
    average /= positions.size();
    cout << sum << endl;
    sum = 0;
    for (auto p: positions) {
        steps = abs(p - average);
        steps = (2 + steps - 1) * steps / 2;
        sum += steps;
    }
    cout << sum << endl;
    return 0;
}