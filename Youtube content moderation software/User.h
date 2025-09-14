// include your own comments

#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <stdexcept>
#include "Person.h"

using namespace std;

class User: public Person
{   public:
        // constructor should initialise name and registration number using arguments
        // and initialise score map to be empty
        User(const string &name, int regNo);
        // method to return registration number
        int getRegNo() const;
    private:
	   int regNo;
	   string name;    
};

#endif
