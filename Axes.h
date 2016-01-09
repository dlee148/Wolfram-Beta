#ifndef AXES_H
#define AXES_H

#include "globals.h"

class Function;

class Axes {
public:
    // Constructor and destructor
    Axes();
    ~Axes();
    // Mutators
    void fillGraph();
    void determineMax();
    void determineMin();
    void setScale();
    void drawAxes();
    void drawGraph();
    void displayGraph();
private:
    Function* m_function;
    char m_graph[GRAPH_DIMENSIONS][GRAPH_DIMENSIONS];
    double m_max;
    double m_min;
    double m_scale;
};

#endif /* AXES_H */
