//
// Created by popaa on 12/4/2021.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#define SIZE 5

using namespace std;

struct boardNumber {
    int value;
    bool chosen;
};

struct bingo {
    vector<boardNumber> board;
    int place;
};

bool has_line(vector<boardNumber> board) {
    int amount;
    for (int i = 0; i <= SIZE * (SIZE - 1); i += SIZE) {
        amount = 0;
        for (int j = i; j < SIZE + i; j++) {
            if (board[j].chosen) amount += 1;
        }
        if (amount == SIZE) return true;
    }
    return false;
}

bool has_column(vector<boardNumber> board) {
    int amount;
    for (int i = 0; i < SIZE; i++) {
        amount = 0;
        for (int j = i; j <= SIZE * (SIZE - 1) + i; j += SIZE) {
            if (board[j].chosen) amount += 1;
        }
        if (amount == SIZE) return true;
    }
    return false;

}

int main() {

    ifstream fin("../src/partOne.txt");
    ifstream rin("../src/partTwo.txt");
    string inputNumbers;
    string number;
    char delim = ',';
    vector<int> drawn;
    vector<bingo> boards;
    vector<boardNumber> line;
    int place = 1;
    vector<boardNumber> result;
    vector<boardNumber> loser;
    int loserCall;
    int finalCall;
    bool found = false;

    if (fin.is_open()) {
        getline(fin, inputNumbers);
        stringstream ss(inputNumbers);
        while (getline(ss, number, delim)) {
            drawn.push_back(stoi(number));
        }

        while (getline(fin, inputNumbers)) {
            istringstream iss(inputNumbers);
            vector<string> input((istream_iterator<string>(iss)),
                                 istream_iterator<string>());
            for (string i: input) {
                boardNumber n;
                n.value = stoi(i);
                n.chosen = false;
                line.push_back(n);
            }
            if (line.size() == SIZE * SIZE) {
                bingo bingoBoard;
                bingoBoard.board = line;
                bingoBoard.place = -1;
                boards.push_back(bingoBoard);
                line.clear();
            }
        }

        for (int d: drawn) {
            for (auto &board: boards) {
                if (board.place == -1) {
                    for (auto &number: board.board) {
                        if (number.value == d) {
                            number.chosen = true;
                        }
                    }
                    if (has_line(board.board) || has_column(board.board)) {
                        board.place = place;
                        if (board.place == boards.size()) {
                            loserCall = d;
                            loser = board.board;
                            found = true;
                            break;
                        }
                        place += 1;
                        if (board.place == 1) {
                            result = board.board;
                            finalCall = d;
                        }
                    }
                }
            }
            if (found) break;
        }
        int sum = 0;
        for (auto value: result) {
            sum = (value.chosen) ? sum : sum + value.value;
        }
        cout << sum * finalCall << endl;
        sum = 0;
        for (auto value: loser) {
            sum = (value.chosen) ? sum : sum + value.value;
        }
        cout << sum * loserCall << endl;
    }
    fin.close();
    return 0;
}
