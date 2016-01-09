#ifndef TERM_H
#define TERM_H

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

#endif /* TERM_H */
