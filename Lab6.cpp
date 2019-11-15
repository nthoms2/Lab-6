/*
Nolan Thoms
C++ Fall Semester
Lab 6
Converting binary code
*/

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

/*preconditions: The only preconditions are that both ifstreams should have been declared.*/

/*postconditons: The postconditions are that both files should be opened and checked to make
sure that the are no problems when the files are opned.*/
void openFile(ifstream& inFile, ifstream& inFile2);

/*preconditions: The only precondition is that the first inFile must be valid in order
for this function to start reading in values.*/

/*postconditions: The postconditions are that after the loop is exited, the line of binary should
have been read in and values should have been assigned to validty, decCon, and digitCount.*/
void binaryConversion(ifstream& inFile, char& binaryIn, bool& validity, unsigned int& decCon, int& digitCount);

/*preconditions: The preconditions are that validity is true, because it needs to be true
in order to enter the output function where this function is called, and there needs to be a
value for digitCount.*/

/*postconditions: The post conditions are that this function should correctly calculate the
number of spaces needed, and output those spaces each time it is called.*/
void binaryDisplay(int digitCount);

/*preconditions: The preconditions are that validity is true so the output function can call this
function, and there needs to be a value for decCon.*/

/*post conditions: The post conditions are that a seconed number of spaces should be calculated
using the value of decCon and then that number of spaces should be outputed to the screen*/
void decimalDisplay(unsigned int decCon);

/*preconditions: The preconditions are that Validity needs to be defined so the function
knows which route to take and inFile2 must be in sync with the first inFile in order to
properly dislplay the outputs. Also all other functions must run smoothly in order for this
function work correctly.*/

/*Postconditions: The postconditions are that this function should have displayed "Bad digit on
input" if invalid, but if valid it should have read in the values from the file and outputted
them to the screen accordingly while also also calling both display functions to help with
centering.*/
void Output(bool validity, ifstream& inFile2, char& binaryIn2, int digitCount, unsigned int decCon);

int main()
{
	// This displays the headings in the output.
	cout << "         Binary Number          " << "\t" << "Decimal Equivalent" << endl;

	// This declares that an input file is being used, states the files name, and opens the file.
	ifstream inFile;
	ifstream inFile2;

	//Here, the openFile function is bein called and both files are opened.
	openFile(inFile, inFile2);

	// These are the charachters that will read in the data.
	char binaryIn;
	char binaryIn2;

	// Priming read.
	inFile >> binaryIn;

	// This is the main loop that runs until the end of the file.
	while (inFile)
	{
		// These are different variables in which their values should reset every time
		// the program loops.
		unsigned int decCon = 0; // This stands for decimal conversion.
		int digitCount = 0; // This int keeps track of how many binary digts there are in a line.
		bool validity = true; // This bool helps check to make sure the binary code is vallid.
		 
		// This calls the binaryConversion function which calculates the decimal equivelant 
		// of the binary code and checks to see if it is valid.
		binaryConversion(inFile, binaryIn, validity, decCon, digitCount);

		//This calls the output function witch outputs the binary input and decimal equivelant
		// as long as it is valid.
		Output(validity, inFile2, binaryIn2, digitCount, decCon);
		 
		//This reads in the next line of code.
		inFile >> binaryIn;
	}
	
	return 0;
}

// This is the openFile function described in the main.
void openFile(ifstream& inFile, ifstream& inFile2)
{
	// This states the location of the input file.
	string inFileName = "C:/Users/THOMS3/Documents/C++/Lab 6 Binary Code/BinaryIn.dat";
	
	//This opens the input file two different times.
	inFile.open(inFileName);
	inFile2.open(inFileName);

	// This checks to make sure the files can be found.
	assert(inFile);
	assert(inFile2);

}

// This is the binaryConversion function described in the main.
void binaryConversion(ifstream& inFile, char& binaryIn, bool& validity, unsigned int& decCon, int& digitCount)
{
	// This while loop checks all the inputs before one and if those inputs are not zero
	// then validity becomes false, because there is a bad digit.
	while (inFile && binaryIn != '1') // (runs untill the character 1, then next loop starts)
	{
		if (binaryIn != '0')
		{
			validity = false;
			break;
		}

		inFile >> binaryIn;
	}

	// This while loop calculates the value of the decimal equivalent.
	while (inFile && binaryIn != '\n') // (reads in charachters until new line)
	{
		decCon *= 2; // This multiplies the decimal conversion value by two every loop.
		digitCount++; // This counts the binary digits in a line by adding value every loop.

		//This switch statement adds one to the decCon if the binary input is one and nothing
		//if it is zero, also if it is anything besides those two, validity is changed to false.
		switch (binaryIn)
		{
		case '0': decCon += 0;
			break;
		case '1': decCon += 1;
			break;
		default: validity = false;
			break;
		}

		// This reads in the next character. (.get allows it to read the new line character
		// and exit the loop.)
		inFile.get(binaryIn);
	}

}

// This is the Bianary display function, it calculates the number of space to put in front of
// and behind of the binary digits when they are displayed, in order for them to be centered.
void binaryDisplay(int digitCount)
{
	// Since the largest value that could be used is 32 this creates an int the represents
	// the spaces on either side of the binary digits. 
	int numSpaces = ((32 - digitCount) / 2); 

	// This loop outputs the spaces needed.
	for (int count = 1; count <= numSpaces; count++)
	{
		cout << " ";
	}
}

// This is the decimalDisplay function, since no decimal outputs values can be larger than the
// heading "Decimal Equivalent" which 18 spaces wide, this function determines the amount
// of spaces needed to center the decimal number underneath "Decimal Equivalent".
void decimalDisplay(unsigned int decCon)
{
	int decimalDigits = 1; // This int is used when determing the number of digits in decCon.

	// This for loop determines the number of digit in decCon by continously dividing it by ten
	// until its value is less than ten, adding vaule to decimalDigits each time.
	for (decCon; decCon > 10; decCon /= 10)
	{
		decimalDigits++;
	}

	// Like befor in the previous function, this caluclates the number of space needed
	// in order to center the decimal value.
	int numSpaces2 = ((18 - decimalDigits)/2);

	// This loop displays the calculated amount of spaces.
	for (int count2 = 1; count2 <= numSpaces2; count2++)
	{
		cout << " ";
	}
}

// This is the output function described in the main.
void Output(bool validity, ifstream& inFile2, char& binaryIn2, int digitCount, unsigned int decCon)
{
	// This checks to make sure the binary read in was valid.
	if (validity)
	{
		// This calls the binaryDisplay function.
		binaryDisplay(digitCount);

		// priming read #2
		inFile2 >> binaryIn2;

		// This loop checks to see if the first value is zero and if it is, it is skipped until a
		// one is read in.
		while (inFile2 && binaryIn2 != '1')
		{
			inFile2 >> binaryIn2;
		}
		// This loop read untill there is a new line and outputs each character.
		while (inFile2 && binaryIn2 != '\n')
		{
			switch (binaryIn2)
			{
			case '0': cout << '0'; // (outputs zero)
				break;
			case '1': cout << '1'; // (outputs one)
				break;
			default: // (nothing happens)
				break;
			}

			// This read in the next character and allows it to detect a new line.
			inFile2.get(binaryIn2);
		}

		// This displays the number of spaces after the binary numbers, if the amount of digits 
		// is even then is displays the same amount of spaces as before, but if it is oddd than
		// one extra space needs to be outputed to get the total number of spaces to equal 32.
		if (digitCount % 2 == 0)
		{
			binaryDisplay(digitCount);
		}
		else
		{
			binaryDisplay(digitCount);
			cout << " "; // This is the extra space.
		}

		// This section tabs over than calls the decimalDispaly function in order to 
		// center deCon.
		cout << "\t";
		decimalDisplay(decCon);
		cout << decCon << endl;
	}

	// This else statement is what happens when validity is false.
	else
	{
		// This is another priming read and loop, this is used because if validity is false
		// inFile2 needs to be read so it can be caught back up to the first infile.
		inFile2 >> binaryIn2;
		while (inFile2 && binaryIn2 != '\n')
		{
			inFile2.get(binaryIn2);
		}
		// This outputs the error message.
		cout << "       Bad digit on input       " << endl;
	}
}