#include <fstream>
#include <iostream>
#include <string>

typedef
std::basic_string<char>  str; // same typedef as std::string

const str hello = "Hello World";


int
print(str const &s)
{
	std::cout << s << std::endl;
	return 1;
}


int
main()
{
	// Literals (double-quoted text) denote C strings, but str
	// instances can be initialized from such literals.
	str foo = "fighters";
	str bar = "stool";

	// The operator != compares string contents for inequality. This is different
	// from != on char pointers to C strings, where != would compare the memory
	// addresses of the strings rather than their contents.
	if (foo != bar) {
		print("The strings are different.");
	}

	// Prints "stool fighters". The + operator denotes string concatenation.
	print(bar + " " + foo); // could be single-quoted as well
	// print(bar << " " << foo); // fails, using a string like a stream

	return 0;
}

