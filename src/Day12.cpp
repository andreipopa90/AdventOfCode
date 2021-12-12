//
// Created by popaa on 12/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <chrono>

using namespace std;

struct Cave {
    string name;
    int visited = 0;
    bool small;
    vector<Cave> neighbours;
};

map<string, Cave> caves;
bool twice = false;
int nb_of_paths = 0;

void walk(Cave &cave) {

    if (cave.name == "end") {
        nb_of_paths ++;
    } else if (((!twice) || (twice && cave.visited == 0)) || (!cave.small)) {

        cave.visited += 1;
        if (cave.visited == 2 && cave.small) {
            twice = true;
        }

        for (auto &n: cave.neighbours) {
            if (((!twice) || (twice && n.visited == 0)) || (!n.small)) {
                walk(caves[n.name]);
            }
        }

        cave.visited -= 1;
        if (cave.visited == 1 && cave.small) {
            twice = false;
        }
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

    auto time1 = chrono::high_resolution_clock::now();

    walk(caves["start"]);
    cout << nb_of_paths << endl;
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> ms_double = time2 - time1;
    cout << ms_double.count() << "ms" << endl;
    return 0;
}