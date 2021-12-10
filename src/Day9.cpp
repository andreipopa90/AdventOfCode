//
// Created by popaa on 09/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct location {
    int value;
    bool visited;
};

int find_basin(int x, int y, vector<vector<location>> &grid) {
    if (x >= 0 && x <= grid.size() - 1 && y >= 0 && y <= grid[x].size() - 1) {
        if (grid[x][y].value != 9 && !grid[x][y].visited) {
            int sum = 1;
            grid[x][y].visited = true;
            sum += find_basin(x + 1, y, grid);
            sum += find_basin(x - 1, y, grid);
            sum += find_basin(x, y + 1, grid);
            sum += find_basin(x, y - 1, grid);
            return sum;
        }
    }
    return 0;
}

int main() {
    ifstream fin("../src/input.txt");
    string input;
    vector<location> line;
    vector<vector<location>> grid;
    vector<pair<int, int>> locations;

    while (getline(fin, input)) {
        for (auto i: input) {
            location point;
            point.value = i - '0';
            point.visited = false;
            line.push_back(point);
        }
        grid.push_back(line);
        line.clear();
    }

    vector<int> lowestPoints;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            pair<int, int> p;
            if (i == 0 && j == 0) {
                if (grid[i][j].value < grid[i + 1][j].value && grid[i][j].value < grid[i][j + 1].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i == 0 && j == grid[i].size() - 1) {
                if (grid[i][j].value < grid[i + 1][j].value && grid[i][j].value < grid[i][j - 1].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i == 0 && j < grid[i].size() - 1) {
                if (grid[i][j].value < grid[i + 1][j].value && grid[i][j].value < grid[i][j - 1].value
                && grid[i][j].value < grid[i][j + 1].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i == grid.size() - 1 && j == 0) {
                if (grid[i][j].value < grid[i - 1][j].value && grid[i][j].value < grid[i][j + 1].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i == grid.size() - 1 && j == grid[i].size() - 1) {
                if (grid[i][j].value < grid[i - 1][j].value && grid[i][j].value < grid[i][j - 1].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i == grid.size() - 1 && j < grid[i].size() - 1) {
                if (grid[i][j].value < grid[i - 1][j].value && grid[i][j].value < grid[i][j - 1].value
                && grid[i][j].value < grid[i][j + 1].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i > 0 && j == 0) {
                if (grid[i][j].value < grid[i + 1][j].value && grid[i][j].value < grid[i][j + 1].value
                && grid[i][j].value < grid[i - 1][j].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i > 0 && j == grid[i].size() - 1) {
                if (grid[i][j].value < grid[i + 1][j].value && grid[i][j].value < grid[i][j - 1].value
                && grid[i][j].value < grid[i - 1][j].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            } else if (i > 0 && j < grid[i].size() - 1) {
                if (grid[i][j].value < grid[i + 1][j].value && grid[i][j].value < grid[i][j + 1].value &&
                grid[i][j].value < grid[i - 1][j].value && grid[i][j].value < grid[i][j - 1].value) {
                    lowestPoints.push_back(grid[i][j].value);
                    p.first = i;
                    p.second = j;
                    locations.push_back(p);
                }
            }
        }
    }
    int sum = 0;
    for (auto l: lowestPoints) {
        sum += (1 + l);
    }
    vector<int> basin_sizes;
    for (auto p: locations){
        basin_sizes.push_back(find_basin(p.first, p.second, grid));
    }
    sort(basin_sizes.begin(), basin_sizes.end());
    unsigned long long result;
    int lastIndex = basin_sizes.size() - 1;
    result = basin_sizes[lastIndex] * basin_sizes[lastIndex - 1] * basin_sizes[lastIndex - 2];
    cout << result << endl;
    cout << sum << endl;
    return 0;
}
