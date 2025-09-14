#include "User.h"
#include <iostream>

// Constructor that initialises name and registration number using arguments
// The score map is implicitly initialised to be empty since it's not mentioned here
User::User(const string &name, int regNo) : Person(name), regNo(regNo)
{
    std::cout << "User constructor called" << endl;  
}
int User::getRegNo() const
{
    return regNo;
}