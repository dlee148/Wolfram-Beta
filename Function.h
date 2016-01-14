#ifndef FUNCTION_H
#define FUNCTION_H

#include "globals.h"

class Term;

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
};

#endif /* FUNCTION_H */
