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
    bool small;
    vector<Cave> neighbours;
};

vector<Cave> path;
map<string, Cave> caves;
map<string, int> visited;
bool twice = false;
int nb_of_paths = 0;

void walk(const Cave &cave) {

    if (cave.name == "end") {
        nb_of_paths ++;
    } else if (((!twice) || (twice && visited[cave.name] == 0))) {

        if (cave.small) {
            visited[cave.name] += 1;
            if (visited[cave.name] == 2) {
                twice = true;
            }
        }
        path.push_back(cave);

        for (auto &n: cave.neighbours) {
            walk(caves[n.name]);
        }

        if (cave.small) {
            visited[cave.name] -= 1;
            if (visited[cave.name] == 1) {
                twice = false;
            }
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
        link1.small = 'a' <= link1.name[0] && link1.name[0] <= 'z';

        link2.name = input.substr(input.find(delim) + 1, input.size());
        link2.small = 'a' <= link2.name[0] && link2.name[0] <= 'z';

        links.push_back(make_pair(link1.name, link2.name));

        if (caves.find(link1.name) == caves.end()) {
            caves[link1.name] = link1;
        }

        if (caves.find(link2.name) == caves.end()) {
            caves[link2.name] = link2;
        }
    }

    fin.close();

    for (auto pair: links) {

        if (pair.first != "end" && pair.second != "start") {
            caves[pair.first].neighbours.push_back(caves[pair.second]);
        }
        if (pair.second != "end" && pair.first != "start") {
            caves[pair.second].neighbours.push_back(caves[pair.first]);
        }
    }

    for (auto c: caves) {
        if (c.first != "start" and c.first != "end") {
            visited[c.first] = 0;
        }
    }

    walk(caves["start"]);
    cout << nb_of_paths << endl;
    return 0;
}