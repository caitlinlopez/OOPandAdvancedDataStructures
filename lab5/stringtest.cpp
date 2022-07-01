#include <iostream>
#include "mystring.h"

using std::cout;
using std::cin;
using std::endl;
using coen79_lab5::string;

std::string boolString(bool b) {
	return (b) ? "true" : "false";
}

int main(int argc, char const *argv[]) {
	string s1, s2("Testing"), s3(s2);
     cout << "s1: " << s1 << endl;
     cout << "s2: " << s2 << endl;
     cout << "s3: " << s3 << endl;
    
     cout << "*** += Operator Tests ***" << endl;
     cout << "s1 length: " << s1.length() << endl;
     s1 += string("A");
     cout << "s1: " << s1 << endl;
     cout << "s1 length: " << s1.length() << endl;
     s1 += "B";
     cout << "s1: " << s1 << endl;
     cout << "s1 length: " << s1.length() << endl;
     s1 += 'C';
     cout << "s1: " << s1 << endl;
     cout << "s1 length: " << s1.length() << endl;
    
     cout << "*** [] Operator Test ***" << endl;
     cout << "s1[0]: " << s1[0] << endl;
     cout << "s1[1]: " << s1[1] << endl;
     cout << "s1[2]: " << s1[2] << endl;
    
     cout << "*** = Operator Test ***" << endl;
     s2 = string("= Test 1 Successful");
     cout << "s2: " << s2 << endl;
     cout << "s2: " << (s2 = string("= Test 2 Successful")) << endl;
    
     string A("A"), B("B");
     cout << "*** Logical Operator Tests ***" << endl;
     cout << "A == A: " << boolString(A == A) << endl;
     cout << "A == B: " << boolString(A == B) << endl;
     cout << "A != A: " << boolString(A != A) << endl;
     cout << "A != B: " << boolString(A != B) << endl;
     cout << "A > A: " << boolString(A > A) << endl;
     cout << "A > B: " << boolString(A > B) << endl;
     cout << "B > A: " << boolString(B > A) << endl;
     cout << "A >= A: " << boolString(A >= A) << endl;
     cout << "A >= B: " << boolString(A >= B) << endl;
     cout << "B >= A: " << boolString(B >= A) << endl;
     cout << "A < A: " << boolString(A < A) << endl;
     cout << "A < B: " << boolString(A < B) << endl;
     cout << "B < A: " << boolString(B < A) << endl;
     cout << "A <= A: " << boolString(A <= A) << endl;
     cout << "A <= B: " << boolString(A <= B) << endl;
     cout << "B <= A: " << boolString(B <= A) << endl;
    
     cout << "*** + Operator Tests ***" << endl;
     cout << "A + B: " << (A + B) << endl;
     cout << "A + C: " << (A + "C") << endl;
     cout << "B + A: " << (B + A) << endl;

     cout << "*** >> Operator Test ***" << endl;
     cout << "Enter a word: ";
     cin >> s1;
     cout << "You entered: " << s1 << endl;

	// Character constructor test
	cout << "*** Single Character Constructor Test ***" << endl;
	string C('C');
	cout << "C: " << C << endl;
	// Insertion tests
	cout << "*** Insert Tests ***" << endl;
	s1 = "ABCD";
	cout << "s1: " << s1 << endl;
	s1.insert("-",0);
	cout << "s1: " << s1 << endl;
	s1.insert("*",3);
	cout << "s1: " << s1 << endl;
	s1.insert(".",s1.length());
	cout << "s1: " << s1 << endl;
	// Delete tests
	cout << "*** Delete Tests ***" << endl;
	s1 = "1112233445555";
	cout << "s1: " << s1 << endl;
	s1.dlt(0,3);
	cout << "s1: " << s1 << endl;
	s1.dlt(2,2);
	cout << "s1: " << s1 << endl;
	s1.dlt(s1.length()-4,4);
	cout << "s1: " << s1 << endl;
	// Replace test
	cout << "*** Replace Tests ***" << endl;
	s1 = "abc";
	cout << "s1: " << s1 << endl;
	s1.replace('z',0);
	cout << "s1: " << s1 << endl;
	s1.replace('y',1);
	cout << "s1: " << s1 << endl;
	s1.replace('x',2);
	cout << "s1: " << s1 << endl;
	s1 = "ABCDEFGHIJKLMNOP";
	s2 = "123";
	s1.replace(s2, 0);
	cout << "s1: " << s1 << endl;
	s1.replace(s2, 5);
	cout << "s1: " << s1 << endl;
	s1.replace(s2, s1.length() - s2.length());
	cout << "s1: " << s1 << endl;

	cout << "*** Count Tests ***" << endl;
	s1 = "AABBBCDDDD";
	cout << "s1: " << s1 << endl;
	cout << "Number of A's: " << s1.count('A') << endl;
	cout << "Number of B's: " << s1.count('B') << endl;
	cout << "Number of C's: " << s1.count('C') << endl;
	cout << "Number of D's: " << s1.count('D') << endl;
	cout << "Number of E's: " << s1.count('E') << endl;

	cout << "*** Search Tests ***" << endl;
	cout << "s1: " << s1 << endl;
	cout << "First A: " << s1.search('A') << endl;
	cout << "First B: " << s1.search('B') << endl;
	cout << "First C: " << s1.search('C') << endl;
	cout << "First D: " << s1.search('D') << endl;
	cout << "First E: " << s1.search('E') << endl;
	s1 = "ABCDEFGHIJKLMNOP";
	cout << "s1: " << s1 << endl;
	cout << "Location of \"ABC\": " << s1.search(string("ABC")) << endl;
	cout << "Location of \"GHI\": " << s1.search(string("GHI")) << endl;
	cout << "Location of \"NOP\": " << s1.search(string("NOP")) << endl;
	cout << "Location of \"XYZ\": " << s1.search(string("XYZ")) << endl;

	return 0;
}