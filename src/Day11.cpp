//
// Created by popaa on 11/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const vector<int> direction_x = {-1, -1, -1, 0, 0, 1, 1, 1};
const vector<int> direction_y = {-1, 0, 1, -1, 1, -1, 0, 1};

struct octopus{
    int timer;
    bool flashed;
};

void increase(vector<vector<octopus>> &grid, int x, int y) {
    for (int i = 0; i < 8; i++) {
        if (x + direction_x[i] >= 0 && x + direction_x[i] < grid.size() &&
            y + direction_y[i] >= 0 && y + direction_y[i] < grid.size()) {
            if (grid[x + direction_x[i]][y + direction_y[i]].timer > 0) {
                grid[x + direction_x[i]][y + direction_y[i]].timer =
                        (grid[x + direction_x[i]][y + direction_y[i]].timer + 1) % 10;
            }
        }
    }
}

void chain_reaction(vector<vector<octopus>> &grid, int x, int y) {
    if (x >= 0 && x < grid.size() && y >= 0 && y < grid.size()) {
        if (!grid[x][y].flashed && grid[x][y].timer == 0) {
            grid[x][y].flashed = true;
            increase(grid, x, y);
            for (int i = 0; i < 8; i++) {
                chain_reaction(grid, x + direction_x[i], y + direction_y[i]);
            }
        }
    }
}

int count_flashes(const vector<vector<octopus>> &grid) {
    int flashes = 0;
    for (auto const line: grid) {
        for (auto const l: line) {
            flashes = (l.timer == 0) ? flashes + 1 : flashes;
        }
    }
    return flashes;
}

bool all_zero(const vector<vector<octopus>> &grid) {
    for (auto line: grid) {
        for (auto l: line) {
            if (l.timer != 0) return false;
        }
    }
    return true;
}

void flash_octopuses(vector<vector<octopus>> &grid) {
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            grid[x][y].timer = (grid[x][y].timer + 1) % 10;
            grid[x][y].flashed = false;
        }
    }
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            if (grid[x][y].timer == 0) {
                chain_reaction(grid, x, y);
            }
        }
    }
}

int main() {
    vector<vector<octopus>> grid;
    vector<octopus> line;
    string input;
    octopus o;
    int nb_flashes = 0;
    int steps = 0;

    ifstream fin("../src/input.txt");

    while(getline(fin, input)) {
        for (auto ch: input) {
            o.flashed = false;
            o.timer = ch - '0';
            line.push_back(o);
        }
        grid.push_back(line);
        line.clear();
    }

    while (!all_zero(grid)) {
        flash_octopuses(grid);
        steps += 1;
        if (steps <= 100) {
            nb_flashes += count_flashes(grid);
        }
    }

    cout << nb_flashes << endl;
    cout << steps << endl;
    return 0;
}
