#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void fillGraph(char graph[][51]);
void drawAxes(char graph[][51]);

int main() {
    char graph[51][51];
    fillGraph(graph);
    drawAxes(graph);
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 51; ++j) {
            cout << graph[i][j];
        }
        cout << endl;
    }
}

void fillGraph(char graph[][51]) {
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 51; ++j) {
            graph[i][j] = ' ';
        }
    }
}

void drawAxes(char graph[][51]) {
    // x-axis
    for (int i = 1; i < 50; ++i) {
        graph[25][i] = '-';
    }
    graph[25][0] = '<';
    graph[25][50] = '>';
    // y-axis
    for (int j = 0; j < 51; ++j) {
        graph[j][25] = '|';
    }
    graph[0][25] = '^';
    graph[50][25] = 'v';
}