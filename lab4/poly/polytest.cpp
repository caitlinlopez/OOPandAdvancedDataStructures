#include <iostream>
#include <iomanip>
#include "poly.h"
#include <stdio.h>

using namespace std;
using coen79_lab4::polynomial;

int main(int argc, const char * argv[])
{
	polynomial p1, p2;
	p1.assign_coef(7,29);		//MAXIMUM_DEGREE
	p1.assign_coef(6,28);		//MAXIMUM_DEGREE - 1
	p1.assign_coef(5,17);
	p1.assign_coef(4,1);
	p1.assign_coef(3,0);
	p2.assign_coef(-4.5,28);	//MAXIMUM_DEGREE - 1
	p2.assign_coef(-3,17);
	p2.assign_coef(-2.5,1);
	p2.assign_coef(-2,0);
	
	p1.add_to_coef(8, 1);
	p1.clear();
	p2.antiderivative();
	p2.coefficient(17);
	p2.definite_integral(0,5);
	p2.degree();
	p2.derivative();
	p2.eval(3);
	p2.is_zero();
	p2.next_term(10);
	p2.previous_term(29);
	p1 = p1 + p2;
	
	for(int i = 0; i < polynomial::CAPACITY; i++) {
		printf("%f\n", p1.coefficient(i));
	}
	cout << p1;
	return 0;
}