#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void fillGraph(char graph[][51]);
void drawAxes(char graph[][51]);
void getCoefficients(int coefficients[], int degree);
void draw(int coefficients[], int degree, char graph[][51]);

int main() {
    char graph[51][51];
    fillGraph(graph);
    drawAxes(graph);
    
    int degree = 0;
    int coefficients[10];
    cout << "What is the degree of the function? ";
    cin >> degree;
    
    getCoefficients(coefficients, degree);
    draw(coefficients, degree, graph);
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

void getCoefficients(int coefficients[], int degree) {
    for (int i = 0; i < degree; ++i) {
        cout << "What is the coefficient of the term of degree " << i + 1 << "? ";
        int co = 0;
        cin >> co;
        coefficients[i] = co;
    }
}

void draw(int coefficients[], int degree, char graph[][51]) {
    for (int i = 0; i < 51; ++i) {
        int pos = 0;
        for (int j = 0; j < degree; ++j) {
            pos += coefficients[j] * pow(i - 25, j + 1);
        }
        if (pos < 26 && pos > -26) {
            graph[25 - pos][i] = '*';
        }
    }
    
    for (int k = 0; k < 51; ++k) {
        for (int l = 0; l < 51; ++l) {
            cout << graph[k][l];
        }
        cout << endl;
    }
}