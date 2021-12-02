#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("../src/partOne.txt");
    char *line;
    int maxSize = 10;
    while (fin.getline(line, maxSize)) {
        string str(line);
        cout << str << " ";
        string answer = str.substr(0, str.find(" "));
        cout << answer << endl;
    }
    return 0;
}
