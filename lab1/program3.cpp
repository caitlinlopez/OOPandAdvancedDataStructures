#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void three(string textFile){						//reads text file and erases non-alphabetical characters; converts words larger than 10 characters to uppercase and prints
	string word, tempWord;
	std::ifstream file;
	file.open(textFile.c_str());					//open file
	
	while(file && file.peek() != EOF){				//go through the whole file
		word = "";
		file >> tempWord;
		for(int i = 0; i < tempWord.size(); i++){	//loop through each character in a word
			if(isalpha(tempWord[i])) {				//if the character is alphabetical
				word += toupper(tempWord[i]);		//makes characters capitalized
			}
		}
		if(word.size() >= 10){						//if the word length is more than 10, print
			std::cout << word << '\n';
		}
	}
}

int main(int argc, char* argv[]) {
	if(argc > 1){
		std::string arg1(argv[1]);					//turns argv into a string
		three (arg1);								//passes the input text file into the three function
	}
	return 0;
}