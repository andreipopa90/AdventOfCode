//
// Created by popaa on 05/12/2021.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int gridSize;

void addCoordinates(string const line, vector<pair<int, int>> &coordinates) {
    int x, y;
    char delim = ',';
    pair<int, int> coordinate;
    x = stoi(line.substr(0, line.find(delim)));
    y = stoi(line.substr(line.find(delim) + 1, line.size()));
    coordinate.first = x;
    coordinate.second = y;
    coordinates.push_back(coordinate);
    if (x > gridSize) gridSize = x;
    if (y > gridSize) gridSize = y;
}

int main() {

    ifstream fin("../src/input.txt");
    string inputLine;
    string input;
    string firstDelim = " -> ";
    string left;
    string right;
    int x1,x2,y1,y2;
    vector<pair<int, int>> coordinates;
    vector<vector<int>> grid;
    vector<int> line;

    while (getline(fin, inputLine)) {
        left = inputLine.substr(0, inputLine.find(firstDelim));
        right = inputLine.substr(inputLine.find(firstDelim) + firstDelim.size(), inputLine.size());

        addCoordinates(left, coordinates);
        addCoordinates(right, coordinates);
    }

    for (int i = 0; i <= gridSize; i++) {
        for (int j = 0; j <= gridSize; j++) {
            line.push_back(0);
        }
        grid.push_back(line);
        line.clear();
    }

    for (int i = 0; i < coordinates.size(); i+=2) {
        x1 = coordinates[i].first;
        y1 = coordinates[i].second;
        x2 = coordinates[i + 1].first;
        y2 = coordinates[i + 1].second;
        if (x1 == x2) {
            if (y1 > y2) {
                swap(y2, y1);
            }
            for (int j = y1; j <= y2; j++) {
                grid[j][x1] += 1;
            }
        }
        else if (y1 == y2) {
            if (x1 > x2) swap(x2, x1);
            for (int j = x1; j <= x2; j++) {
                grid[y1][j] += 1;
            }
        }
        else if (abs(x1 - x2) == abs(y1 - y2)) {
            if (y2 - y1 == x2 - x1) {
                if (y1 > y2) swap(y2, y1), swap(x1, x2);
                if (x1 > x2) swap(x2, x1), swap(y2, y1);
                while (x1 <= x2 && y1 <= y2) {
                    grid[y1][x1] += 1;
                    x1++;
                    y1++;
                }
            } else if (y2 - y1 == x1 - x2) {
                if (y1 > y2) swap(y2, y1), swap(x1, x2);
                if (x1 < x2) swap(x2, x1), swap(y2, y1);
                while (x1 >= x2 && y1 <= y2) {
                    grid[y1][x1] += 1;
                    x1--;
                    y1++;
                }
            }
        }
    }

    int count = 0;

    for (int i = 0; i <= gridSize; i++) {
        for (int j = 0; j <= gridSize; j++) {
            count = (grid[i][j] >= 2) ? count + 1 : count;
        }
    }
    cout << count << endl;

    return 0;
}
