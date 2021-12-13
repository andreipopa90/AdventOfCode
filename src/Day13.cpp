//
// Created by popaa on 13/12/2021.
//
#include <iostream>
#include <fstream>
#include <map>
#include <chrono>

using namespace std;

void fold_y(int axis, map<pair<int, int>, int> &paper) {
    int difference;
    pair<int, int> new_coordinates;
    for (auto &entry: paper) {
        if (entry.first.second > axis && paper[entry.first] != 0) {
            difference = entry.first.second - axis;
            new_coordinates = make_pair(entry.first.first, axis - difference);
            paper[new_coordinates] = 1;
            paper[entry.first] = 0;
        }
    }
}

void fold_x(int axis, map<pair<int, int>, int> &paper) {
    int difference;
    pair<int, int> new_coordinates;
    for (auto entry: paper) {
        if (entry.first.first > axis && paper[entry.first] != 0) {
            difference = entry.first.first - axis;
            new_coordinates = make_pair(axis - difference, entry.first.second);
            paper[new_coordinates] = 1;
            paper[entry.first] = 0;
        }
    }
}

void print_paper(map<pair<int, int>, int> paper, int x, int y) {
    int grid[y][x];
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            grid[i][j] = 0;
        }
    }
    for (auto entry: paper) {
        if (entry.second  == 1)
            grid[entry.first.second][entry.first.first] = entry.second;
    }

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (grid[i][j] == 0) cout << "_ ";
            else cout << "* ";
        }
        cout << endl;
    }
}

int main() {
    ifstream fin("../src/input.txt");
    map<pair<int, int>, int> paper;
    string input = " ";
    pair<int, int> coordinate;

    auto time1 = chrono::high_resolution_clock::now();
    while (input != "") {
        getline(fin, input);
        if (input != "") {
            int index = input.find(',');
            coordinate = make_pair(stoi(input.substr(0, index)),
                                   stoi(input.substr(index + 1, input.size())));
            paper[coordinate] = 1;
        }
    }
    int axis;
    int last_y, last_x;

    while(getline(fin, input)) {
        int index = input.find('=');
        switch(input[index - 1]) {
            case 'y':
                axis = stoi(input.substr(index + 1, input.size()));
                fold_y(axis, paper);
                last_y = axis;
                break;
            case 'x':
                axis = stoi(input.substr(index + 1, input.size()));
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
