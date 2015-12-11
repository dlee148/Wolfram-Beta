#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void fillGraph(char graph[][50]);

int main() {
    char graph[50][50];
    fillGraph(graph);
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            cout << graph[i][j];
        }
        cout << endl;
    }
}

void fillGraph(char graph[][50]) {
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            graph[i][j] = '*';
        }
    }
}