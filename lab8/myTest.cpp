#include <iostream>
#include "deque.h"

using namespace coen79_lab8;

int main(int argc, const char * argv[]) {

	// testing constructor
	std::cout << "Constructor Test\n";
	coen79_lab8::deque<int> testDeque;
	std::cout << "test completed\n\n";
	
	// testing push_front()
	std::cout << "push_front() Test\n";
	for(int i = 20; i > 0; --i){
		testDeque.push_front(i);
		std::cout << testDeque.front() << " ";
	}
	std::cout << "\n" << "test completed\n\n";
	
	// testing push_back()
	std::cout << "push_back() Test\n";
	for(int i = 0; i < 10; ++i){
		testDeque.push_back(i);
		std::cout << testDeque.back() << " ";
	}
	std::cout << "\n" << "test completed\n\n";
	
	// testing = operator
	std::cout << "Assignment Operator Test";
	coen79_lab8::deque<int> newDeque;
	newDeque = testDeque;
	std::cout << "\n" << "test completed\n\n";
	
	return 0;
}