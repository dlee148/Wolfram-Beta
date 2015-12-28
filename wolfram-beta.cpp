/*
 =========================================================
 
 Things to implement:
 
 1. Create graph
 2. Scale graph according to output
 
 =========================================================
 
 Eventual:
 Dealing with parentheses
 Logarithmic functions
 Trig functions
 Compute derivatives and integrals
 
 =========================================================
*/

const int MAX_TERMS = 10;
const int GRAPH_DIMENSIONS = 51;

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

/*
 ======================================
 Class definitions and member functions
 ======================================
*/

// Term class definition and member functions

class Term {
public:
    // Constructor
    Term(double degree, double coeff);
    // Accessor
    double degree();
    double coeff();
    // Mutator
    void addCoeff(double coeff);
private:
    double m_degree;
    double m_coeff;
};

Term::Term(double degree, double coeff) {
    m_degree = degree;
    m_coeff =  coeff;
}

double Term::degree() {
    return m_degree;
}

double Term::coeff() {
    return m_coeff;
}

void Term::addCoeff(double coeff) {
    m_coeff += coeff;
}

// Function class definition and member functions

class Function {
public:
    // Constructor/destructor
    Function();
    ~Function();
    // Mutators
    void takeInput();
    void sortTerms();
    void combineLikeTerms();
    void findStartingIndex();
    void calculateValues();
    void changeAddress(int startingIndex, int endingIndex);
    // Accessors
    Term* terms(int index);
    double* values();
    int nTerms();
    void displayFunction();
    int startingIndex();
private:
    Term* m_terms[MAX_TERMS];
    double m_values[GRAPH_DIMENSIONS];
    int m_userTerms;
    int m_nTerms;
    int m_startingIndex;
    bool m_skipZero;
};

Function::Function() {
    m_nTerms = 0;
    m_skipZero = false;
    m_startingIndex = 0;
    cout << "How many terms are in your function? ";
    cin >> m_userTerms;
    takeInput();
    sortTerms();
    combineLikeTerms();
    findStartingIndex();
    calculateValues();
    displayFunction();
}

Function::~Function() {
    for (int i = 0; i < m_nTerms; ++i) {
        delete m_terms[i];
    }
}

void Function::takeInput() {
    for (int i = 0; i < m_userTerms; ++i) {
        double degree = 0;
        double coeff = 0;
        
        cout << "What is the degree of term " << i + 1 << "? ";
        cin >> degree;
        
        cout << "What is the coefficient of term " << i + 1 << "? ";
        cin >> coeff;
        
        if (coeff != 0) {
            m_terms[i] = new Term(degree, coeff);
            ++m_nTerms;
        }
    }
}

void Function::calculateValues() {
    for (int i = m_startingIndex; i < GRAPH_DIMENSIONS; ++i) {
        if (m_skipZero && i == 25) {
            continue;
        }
        else {
            double value = 0;
            for (int j = 0; j < m_nTerms; ++j) {
                    value += (m_terms[j]->coeff() * pow(i - 25, m_terms[j]->degree()));
            }
            m_values[i] = value;
        }
    }
}

void Function::sortTerms() {
    int counter = 0;
    while (counter < m_nTerms - 1) {
        counter = 0;
        for (int i = 0; i < m_nTerms - 1; ++i) {
            if (m_terms[i]->degree() < m_terms[i + 1]->degree()) {
                Term* tmp = m_terms[i];
                m_terms[i] = m_terms[i + 1];
                m_terms[i + 1] = tmp;
            }
            else {
                ++counter;
            }
        }
    }
}

void Function::combineLikeTerms() {
    int counter = 1;
    while (counter > 0) {
        counter = 0;
        for (int i = 0; i < m_nTerms - 1; ++i) {
            if (terms(i)->degree() == terms(i + 1)->degree()) {
                ++counter;
                terms(i)->addCoeff(terms(i + 1)->coeff());
                delete terms(i + 1);
                for (int j = i + 1; j < m_nTerms - 1; ++j) {
                    changeAddress(j, j + 1);
                }
                --m_nTerms;
                break;
            }
        }
    }
}

//needs work

void Function::findStartingIndex() {
    double maxDegree = 0;
    if (m_terms[0]->degree() > m_terms[m_nTerms - 1]->degree()) {
        maxDegree = m_terms[0]->degree();
    }
    else {
        maxDegree = m_terms[m_nTerms - 1]->degree();
    }
    
    if (maxDegree < 0) {
        m_skipZero = true;
    }
    
    if (maxDegree < 1 && maxDegree > 0) {
        string decimal = to_string(maxDegree);
        char lastNonzero = '\0';
        int index = (int)decimal.length() - 1;
        while (index >= 2) {
            if ((int)decimal[index] != 0) {
                lastNonzero = (char)decimal[index];
            }
            --index;
        }
        if ((int)lastNonzero % 2 != 0) {
            m_startingIndex = 25;
        }
    }
}

void Function::changeAddress(int startingIndex, int endingIndex) {
    m_terms[startingIndex] = m_terms[endingIndex];
}

Term* Function::terms(int index) {
    return m_terms[index];
}

double* Function::values() {
    return m_values;
}

int Function::nTerms() {
    return m_nTerms;
}

void Function::displayFunction() {
    for (int i = 0; i < m_nTerms; ++i) {
        if (i != 0) {
            cout << "+ ";
        }
        if (terms(i)->coeff() == 1 && terms(i)->degree() == 0) {
            cout << "1";
        }
        if (terms(i)->coeff() == -1) {
            if (terms(i)->degree() != 0) {
                cout << "-";
            }
            else {
                cout << "-1";
            }
        }
        if (terms(i)->coeff() != 1 && terms(i)->coeff() != -1) {
            cout << terms(i)->coeff();
        }
        if (terms(i)->degree() != 0) {
            cout << "x";
        }
        if (terms(i)->degree() != 1 && terms(i)->degree() != 0) {
            cout << "^" << terms(i)->degree();
        }
        if ( i != m_nTerms - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int Function::startingIndex() {
    return m_startingIndex;
}

// Axes class definition and member functions

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
        int index = round(m_function->values()[i] - (m_min / m_scale));
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

/*
 ====================================
 Auxiliary functions and main routine
 ====================================
*/

int main() {
    Axes axes;
}