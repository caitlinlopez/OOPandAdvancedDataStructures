//count input characters
#include <iostream>
#include <string>
using namespace std;

void countChar() {
	string text = "";
	int alpha = 0;								//alphanumeric character counter
	int nonAlpha = 0;							//non alphanumeric character counter
	std::cout << "Please type something: ";		//asks user to input text
	getline(cin, text);
	
	for(int i = 0; i < text.size(); i++){		//loop through each character
		if(text[i] != ' '){						//doesn't count spaces
			if(isalnum(text[i])){
				alpha++;						//if character is alphanumeric, add to counter
			}
			else {
				nonAlpha++;						//add to non alphanumeric character counter
			}
		}
	}
	//prints how many alphanumeric and non-alphanumeric characters there are
	std::cout << text << ": has " << alpha << " alphanumeric characters and " << nonAlpha << " non-alphanumeric characters." << '\n';
}

int main(){
	countChar ();
	return 0;
}