//
// Created by popaa on 13/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

void fold_y(int axis, vector<pair<int, int>> &paper) {
    int difference;
    for (auto &entry: paper) {
        if (entry.second > axis) {
            difference = entry.second - axis;
            entry = make_pair(entry.first, axis - difference);
        }
    }
}

void fold_x(int axis, vector<pair<int, int>> &paper) {
    int difference;
    for (auto &entry: paper) {
        if (entry.first > axis) {
            difference = entry.first - axis;
            entry = make_pair(axis - difference, entry.second);
        }
    }

}

void print_paper(const vector<pair<int, int>> &paper, int x, int y) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (find(paper.begin(), paper.end(), make_pair(j, i)) != paper.end()) cout << "* ";
            else cout << "_ ";
        }
        cout << endl;
    }
}

int main() {
    ifstream fin("../src/input.txt");
    vector<pair<int, int>> paper;
    string input = " ";
    pair<int, int> coordinate;

    int axis;
    int last_y, last_x;

    auto time1 = chrono::high_resolution_clock::now();
    while (input != "") {
        getline(fin, input);
        if (input != "") {
            int index = input.find(',');
            coordinate = make_pair(stoi(input.substr(0, index)),
                                   stoi(input.substr(index + 1, input.size())));
            paper.push_back(coordinate);
        }
    }


    while(getline(fin, input)) {
        int index = input.find('=');
        axis = stoi(input.substr(index + 1, input.size()));
        switch(input[index - 1]) {
            case 'y':
                fold_y(axis, paper);
                last_y = axis;
                break;
            case 'x':
                fold_x(axis, paper);
                last_x = axis;
                break;
        }
    }

    print_paper(paper, last_x, last_y);
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> ms_double = time2 - time1;
    cout << ms_double.count() << "ms" << endl;
    return 0;
}
