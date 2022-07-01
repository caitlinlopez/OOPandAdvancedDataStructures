#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

void guess(){																//guesses a number between 1 & 20 that the user is thinking of
	string answer;															//user's response to number guess
	int tries = 0;															//how many steps it took to guess the answer
	
	std::cout << "Think of a number between 1 and 20. Press enter when you are ready." << '\n';
	cin.ignore();
	
	do{																		//repeat until the correct answer is guessed
		int number = rand() % 20 + 1;										//random number between 1 and 20
		std::cout << "Is the number: " << number << "? (y or n)" << '\n';	//asks if the number matches the answer
		std::cin >> answer;
		if (answer == "y" || answer == "n"){								//if user inputs "y" or "n", add one to # of tries counter
			tries++;
		} else {
			std::cout << "Please enter y or n" << '\n';						//tells user to input  "y" or "n" if they entered something else
		}	
	} while(answer != "y");
	
	std:cout << "I found the number in " << tries << " steps!" << '\n';		//stop loop when the answer is reached
}

int main(){
	guess ();
	return 0;
}