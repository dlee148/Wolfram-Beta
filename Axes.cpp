#include "Axes.h"
#include "Function.h"
#include "globals.h"
#include <iostream>
#include <cmath>
using namespace std;

Axes::Axes() {
    m_function = new Function;
    fillGraph();
    determineMax();
    determineMin();
    setScale();
    drawAxes();
    drawGraph();
    displayGraph();
}

Axes::~Axes() {
    delete m_function;
}

void Axes::fillGraph() {
    for (int i = 0; i < GRAPH_DIMENSIONS; ++i) {
        for (int j = 0; j < GRAPH_DIMENSIONS; ++j) {
            m_graph[i][j] = ' ';
        }
    }
}

void Axes::determineMax() {
    double max = m_function->values()[m_function->startingIndex()];
    for (int i = m_function->startingIndex() + 1; i < GRAPH_DIMENSIONS; ++i) {
        if (m_function->values()[i] > max) {
            max = m_function->values()[i];
        }
    }
    m_max = max;
}

void Axes::determineMin() {
    double min = m_function->values()[m_function->startingIndex()];
    for (int i = m_function->startingIndex() + 1; i < GRAPH_DIMENSIONS; ++i) {
        if (m_function->values()[i] < min) {
            min = m_function->values()[i];
        }
    }
    m_min = min;
}

void Axes::setScale() {
    m_scale = ((fabs(m_max) + fabs(m_min)) / 50);
}

void Axes::drawAxes() {
    //vertical axis
    m_graph[0][25] = '^';
    for (int i = 1; i < GRAPH_DIMENSIONS - 1; ++i) {
        m_graph[i][25] = '|';
    }
    m_graph[50][25] = 'v';
    
    //horizontal axis
    int index = round((m_min / m_scale) + 50);
    
    m_graph[index][0] = '<';
    for (int k = 1; k < GRAPH_DIMENSIONS - 1; ++k) {
        m_graph[index][k] = '-';
    }
    m_graph[index][50] = '>';
}

void Axes::drawGraph() {
    for (int i = 0; i < GRAPH_DIMENSIONS; ++i) {
        int index = round((m_function->values()[i] - m_min) / m_scale);
        m_graph[50 - index][i] = '*';
        
    }
}

void Axes::displayGraph() {
    for (int i = 0; i < GRAPH_DIMENSIONS; ++i) {
        for (int j = 0; j < GRAPH_DIMENSIONS; ++j) {
            cout << m_graph[i][j];
        }
        cout << endl;
    }
}