//
// Created by popaa on 12/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Cave {
    string name;
    bool visited;
    bool small;
    vector<Cave> neighbours;
};

vector<Cave> path;
vector<string> cave_names;
vector<Cave> cave_system;
map<string, int> visited;
bool twice = false;
int nb_of_paths = 0;

void print_path() {
    nb_of_paths ++;
}

void walk(Cave &cave) {
    int index;

    if (!cave.visited) {
        if (cave.small) {
            visited[cave.name] += 1;
            if (twice) {
                cave.visited = true;
            }
            if (visited[cave.name] == 2) {
                cave.visited = true;
                twice = true;
                for (auto &c: visited) {
                    index = distance(cave_names.begin(), find(cave_names.begin(), cave_names.end(), c.first));
                    cave_system[index].visited = c.second > 0;
                }
            }
        }
        path.push_back(cave);

        if (cave.name == "end") {
            print_path();
        }

        for (auto &n: cave.neighbours) {
            index = distance(cave_names.begin(), find(cave_names.begin(), cave_names.end(), n.name));
            walk(cave_system[index]);
        }
        if (cave.small) {
            visited[cave.name] -= 1;
            if (visited[cave.name] == 1) {
                twice = false;
                for (auto &c: cave_system) c.visited = false;
            }
            cave.visited = false;
        }
        path.pop_back();
    }
}

int main() {
    ifstream fin("../src/input.txt");

    string input;
    Cave link1, link2;
    char delim = '-';
    vector<pair<string, string>> links;

    while (getline(fin, input)) {
        link1.name = input.substr(0, input.find(delim));
        link1.visited = false;
        link1.small = 'a' <= link1.name[0] && link1.name[0] <= 'z';
        link2.name = input.substr(input.find(delim) + 1, input.size());
        link2.visited = false;
        link2.small = 'a' <= link2.name[0] && link2.name[0] <= 'z';

        links.push_back(make_pair(link1.name, link2.name));

        if (find(cave_names.begin(), cave_names.end(), link1.name) == cave_names.end()) {
            cave_names.push_back(link1.name);
            cave_system.push_back(link1);
        }

        if (find(cave_names.begin(), cave_names.end(), link2.name) == cave_names.end()) {
            cave_names.push_back(link2.name);
            cave_system.push_back(link2);
        }
    }

    for (auto pair: links) {
        int index1 = distance(cave_names.begin(), find(cave_names.begin(), cave_names.end(), pair.first));
        int index2 = distance(cave_names.begin(), find(cave_names.begin(), cave_names.end(), pair.second));

        if (cave_names[index1] != "end" && cave_names[index2] != "start") {
            cave_system[index1].neighbours.push_back(cave_system[index2]);
        }
        if (cave_names[index2] != "end" && cave_names[index1] != "start") {
            cave_system[index2].neighbours.push_back(cave_system[index1]);
        }
    }

    for (auto c: cave_names) {
        if (c != "start" and c != "end") {
            visited[c] = 0;
        }
    }

    walk(cave_system[distance(cave_names.begin(), find(cave_names.begin(), cave_names.end(), "start"))]);
    cout << nb_of_paths << endl;
    return 0;
}