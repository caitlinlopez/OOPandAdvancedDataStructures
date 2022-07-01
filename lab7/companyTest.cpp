//test cases for the company class

#include "company.h"

using namespace coen79_lab7;

int main(int argc, const char * argv[]) {
	
	std::cout << "\n-----Testing constructor and get_name-----\n";
	company myCompany("Apple");
	std::cout << "Company Name: " << myCompany->get_name() << "\n";
	
	
	
	return 0;
}