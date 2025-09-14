// Include necessary header files.
#include <string>
#include <iostream>
#include "Person.h"

// Using the standard C++ namespace for convenience.
using namespace std;

// Implementation of the Person class methods.

// Constructor for the Person class.
Person::Person(const string &name)
{   
    // Initialize the 'name' attribute with the provided value.
    this->name = name;
    
    // Print a message indicating that the Person constructor has been called.
    cout << "Person constructor called" << endl;
}

// Getter method to retrieve the name of the person.
string Person::getName() const
{   
    // Return the 'name' attribute.
    return name;
}

// Method to change the name of the person.
void Person::changeName(const string &newName)
{   
    // Update the 'name' attribute with the new name.
    name = newName;
}
