//
// Created by popaa on 11/30/2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main() {
    int a;
    int increases = 0;
    int previous = 0;
    ifstream fin("../src/partOne.txt");
    if (fin.is_open()) {
        while (fin >> a) {
            if (previous > 0) {
                if (a > previous) increases += 1;
            }
            previous = a;
        }
        cout << increases << endl;
    }
    fin.close();
    ifstream rin("../src/partTwo.txt");
    if (rin.is_open()) {
        vector<int> sums;
        while (rin >> a) {
            sums.push_back(a);
        }
        int number;
        previous = 0;
        increases = 0;
        for (int i = 0; i < sums.size(); i++) {
            if (i + 2 < sums.size()) {
                number = sums[i] + sums[i + 1] + sums[i + 2];
            } else if (i + 1 < sums.size()) {
                number = sums[i] + sums[i + 1];
            } else {
                number = sums[i];
            }
            if (number > previous && previous > 0) increases += 1;
            previous = number;
        }
        cout << increases << endl;
    }
    rin.close();
    return 0;
}
