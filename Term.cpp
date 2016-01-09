#include "Term.h"

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