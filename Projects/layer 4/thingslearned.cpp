#include <iostream>
#include <string>
#include <cctype>

//Module 0
int main(void)
{
	std::string hi; //we use std:: because namespace is not allowed

	std::cout << hi << std::endl; //cout is print, endl is end with newline


}

//hpp file for Module 0
class Contact
{
	public:
		std::string details[5];
		Contact (); //Default constructor (define in cpp file)
		Contact (const std::string details_to_add[5]); //Defined constructor, necessitates the above line
		~Contact ();

};

Contact::~Contact() //destructor
{
	//clean stuff
}



//hpp orthodox template

class MyClass {
	private:
		int* data;
	
	public:
		// Default constructor
		MyClass() : data(new int(0)) {
			// Initialize with default values
		}
	
		// Copy constructor
		MyClass(const MyClass& other) : data(new int(*other.data)) {
			// Create a deep copy of 'other'
		}
	
		// Copy assignment operator
		MyClass& operator=(const MyClass& other) {
			if (this != &other) {  // Self-assignment check
				delete data;       // Release old resources
				data = new int(*other.data);  // Acquire new resources
			}
			return *this;  // Return reference to this object
		}
	
		// Destructor
		~MyClass() {
			delete data;  // Release resources
		}
	};