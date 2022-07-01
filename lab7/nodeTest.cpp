// test cases for the node class

#include "node.h"

using namespace coen79_lab7;

int main(int argc, const char * argv[]) {
	
	std::cout << "\n-----Testing constructor and getName and getPrice-----\n";
	node myNode("Airpods", 159, NULL);
	std::cout << "Product: " << myNode->getName() << " | Price: $" << myNode->getPrice() << "\n";
	
	std::cout << "\n-----Testing setName and setPrice-----\n";
	myNode->setName("iPhone SE");
	myNode->setPrice(399);
	std::cout << "New Product: " << myNode->getName() << " | Price: $" << myNode->getPrice() << "\n";
	
	std::cout << "\n-----Testing list_tail_insert-----\n";
	list_init(myHead, myTail, "Wireless Mouse", 10);
	list_tail_insert(newTail, "Desk Lamp", 20);
	std::cout << "First Product: " << myHead->getName() << " | Price: $" << myHead->getPrice() << "\n";
	std::cout << "Last Product: " << myTail->getName() << " | Price: $" << myTail->getPrice() << "\n";
	
	
	
	return 0;
}