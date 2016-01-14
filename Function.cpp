#include "Function.h"
#include "Term.h"
#include "globals.h"
#include <cmath>
#include <iostream>
using namespace std;

Function::Function() {
    m_nTerms = 0;
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
    for (int i = 0; i < GRAPH_DIMENSIONS; ++i) {
        double value = 0;
        for (int j = 0; j < m_nTerms; ++j) {
            value += (m_terms[j]->coeff() * pow(m_startingIndex + i - 25, m_terms[j]->degree()));
        }
        m_values[i] = value;
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

void Function::findStartingIndex() {
    for (int i = 0; i < GRAPH_DIMENSIONS; ++i) {
        double value = 0;
        for (int j = 0; j < m_nTerms; ++j) {
            value += m_terms[j]->coeff() * pow(i - 25, m_terms[j]->degree());
        }
        if (!isnan(value)) {
            m_startingIndex = i;
            return;
        }
    }
    cout << "No real values on graph." << endl;
    exit(1);
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