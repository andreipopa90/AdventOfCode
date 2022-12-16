//
// Created by popaa on 15/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

#define SIZE 10

using namespace std;

struct position {
    int value;
    bool visited;
    int risk = SIZE * SIZE * 9;
};

int direction_x[4] = {-1, 0, 1, 0};
int direction_y[4] = {0, -1, 0, 1};

void walk(vector<vector<position>> grid) {
    int start_x = 0, start_y = 0;
    grid[start_x][start_y].risk = grid[start_x][start_y].value;
    int x = start_x, y = start_y;
    vector<pair<int, int>> chosen_neighbours;

    while (true) {
        int minimum_risk = SIZE * SIZE * 9;
        for (int i = 0; i < 4; i++) {
            int pos_x, pos_y;
            pos_x = x + direction_x[i];
            pos_y = y + direction_y[i];
            if (pos_x >= 0 && pos_x < SIZE && pos_y >= 0 && pos_y < SIZE) {
                if (grid[x + pos_x][y + pos_y].risk < minimum_risk){}
            }
        }
    }
}

int main() {
    ifstream fin("../src/input.txt");
    vector<vector<position>> grid;
    vector<position> line;
    position pos;
    char input;

    while (fin>>input) {
        pos.value = input - '0';
        pos.visited = false;
        line.push_back(pos);
        if (line.size() == SIZE) {
            grid.push_back(line);
            line.clear();
        }
    }



    return 0;
}
