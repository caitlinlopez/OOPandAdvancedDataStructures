#include <iostream>
#include <string>
using namespace std;

void reverseNumbers() {									//prints string in reverse
	string numbers = "", reverse = "";
	std::cout << "Enter a string with 10 numbers: ";	//asks user to input 10 numbers
	std::cin >> numbers;
	
	if(numbers.size() == 10){							//makes sure string is 10 numbers
		for(int i = 0; i < numbers.size(); i++) {
			if(numbers[i] == ' '){
				return;									//stop program if the string has a space
			}
			reverse += numbers[numbers.size()-i-1];		//reverses the number string
		}
		//prints numbers in given format
		std::cout << numbers << "    " << reverse << '\n' << " " << numbers << "     " << reverse << '\n' << "  " << numbers << "      " << reverse << '\n' << "   " << numbers << "       " << reverse << '\n' << "    " << numbers << "        " << reverse << '\n';
	} else {
		return;
	}	
}

int main() {
	reverseNumbers ();
	return 0;
}