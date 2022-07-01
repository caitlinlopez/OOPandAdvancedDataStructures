#include <iostream>
#include <cassert>
#include <cmath>                // to implement pow()
#include "poly.h"
#include <climits>              // to implement UINT_MAX
#include <iomanip>

using namespace std;

namespace coen79_lab4 {
    
    // constructor: creates a polynomial of all zero coefficients except for c which has a given exponent
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
        data[exponent] = c;
    }
    
    // sets the coefficient for a certain exponent
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] = coefficient;
    }
    
    // adds input number to the coefficient at exponent
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] += amount;
    }

    // sets the coefficients of "this" equal to zero
    void polynomial::clear() {
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
    }
    
    // returns the antiderivative of the polynomial
    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE);          // checks that the largest non-zero coefficient exponent is less than 29
        polynomial a(0,0);                          // empty, temporary polynomial
        a.data[0] = 0;                              
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            a.data[i+1] = (data[i]/(i+1));
        }
        return a;
    }
    
    // Returns coefficient at specified exponent
    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent > MAXIMUM_DEGREE)               // if exponent greater than 29 return 0
            return 0;
        else
            return data[exponent];                  // return coefficient at exponent
    }
    
    // returns the value of the definite integral from x0 to x1
    double polynomial::definite_integral(double x0, double x1) const {
        double upper, lower = 0.0;                  // initialize doubles
        polynomial a;                               // temporary polynomial
        a = antiderivative();                       
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {   // calculate value with input x0/x1 for each index value
            lower += (a.data[i] * pow(x0,i));       // calculate each lower bound with input x0
            upper += (a.data[i] * pow(x1,i));       // calculate each upper bound with input x1
        }
        return upper - lower;                       
    }
    
    // returns the largest exponent with a non-zero coefficient
    unsigned int polynomial::degree() const {
        for(int i = CAPACITY-1; i >= 0; i--) {  
            if(data[i] != 0)
                return i;
        }
        return 0;                               // return 0 if the polynomial is empty
    }
    
    // returns the polynomial of the first derivative of polynomial "this"
    polynomial polynomial::derivative() const {
        polynomial a;                                   // temporary polynomial
        for(int i = 1; i < MAXIMUM_DEGREE; ++i) {       // index starts at 1 because exponent 0 becomes 0
            a.data[i-1] = (data[i] * i);                
        }
        return a;
    }
    
    // returns the value of the polynomial for given x
    double polynomial::eval(double x) const {
        double sum = 0.0;
        for(int i = 0; i < CAPACITY; i++) {
            sum += (data[i] * pow(x, i));
        }
        return sum;
    }

    // returns true if polynomial is all zero
    bool polynomial::is_zero() const {
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            if(data[i] != 0) {
                return false;                   // returns false if there's a non-zero value
            }
        }
        return true;                            
    }
    
    // returns the next exponent that is larger than e with nonzero coefficient
    unsigned int polynomial::next_term(unsigned int e) const {
        for(int i = e+1; e < MAXIMUM_DEGREE; i++) {       
            if(data[i] != 0)                        // return i if there's a non-zero coefficient exponent 
                    return i;                       
        }
        return 0;                                   // return 0 if e is largest exponent
    }
    
    // returns the next exponent that is smaller than e with nonzero coefficient
    unsigned int polynomial::previous_term(unsigned int e ) const {
        for(int i = e-1; i >= 0; i--) {             // start at e-1 until i = 0
            if(data[i] != 0)                        // return i if there's a non-zero coefficient exponent
                return i;                           
        }
        return UINT_MAX;                            // return UINT_MAX if e is the smallest exponent
    }

    // same as eval member function
    double polynomial::operator()(double x) const {
        return eval(x);                             // calls eval function
    }
    
    /* NON MEMBER BINARY OPERATORS */

    // returns a polynomial with each coefficient equal to p1+p2
    polynomial operator+(const polynomial& p1, const polynomial& p2) {
        polynomial tmp;                                                 // temporary polynomial
        for(int i = 0; i < polynomial::CAPACITY; i++)                   // loop through 0 to CAPACITY
            tmp.assign_coef(p1.coefficient(i)+p2.coefficient(i), i);    // call coefficient() function on p1 and p2
        return tmp;
    }
    
    // returns a polynomial with each coefficient equal to p1-p2
    polynomial operator-(const polynomial& p1, const polynomial& p2) {
        polynomial tmp;
        for(int i = 0; i < polynomial::CAPACITY; i++)
            tmp.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);    // call coefficient() function on p1 and p2
        return tmp;
    }
    
    // returns a polynomial with each polynomial multiplication
    polynomial operator*(const polynomial& p1, const polynomial& p2) {
        assert( (p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE);  // highest degree of p1 and p2 smaller than 29
        polynomial tmp;                                                      // temporary polynomial
        for(int i = 0; i <= p1.degree(); i++)
            for(int j = 0; j <= p2.degree(); j++)
                tmp.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j); 	 
        return tmp;
    }
    
    // NONMEMBER OUTPUT FUNCTION
    // polynomial is printed to ostream
    std::ostream& operator<<(ostream& out, const polynomial& p) {
        unsigned int i = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        for(int i = p.degree(); i >= 0; i--) {              // start at highest exponent
            if(p.degree() == 0) 
                out << p.coefficient(0);
            else if(p.coefficient(i) != 0) {        
                if(i == p.degree())                             
                    out << p.coefficient(i) << "x^" << i << ' ';   // print as "(-/+)ax^i "
                else if(i < p.degree() && i > 1) {              // if not highest and not first coefficient
                    if(p.coefficient(i) < 0)
                        out << "- ";                            // if negative add "- "
                    else    
                        out << "+ ";                            // if positive add "+ "
                    out << fabs(p.coefficient(i)) << "x^" << i << ' ';   // print "ax^i "
                }
                else if(i == 1) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                            // if negative add "- "
                    else
                        out << "+ ";                            // if positive add "+ "
                    out << fabs(p.coefficient(i)) << "x ";             // print "ax "
                }
                else if(i == 0) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                            // if negative add "- "
                    else
                        out << "+ ";                            // if positive add "+ "
                    out << fabs(p.coefficient(i));                    // print "a"
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;
    }
}
