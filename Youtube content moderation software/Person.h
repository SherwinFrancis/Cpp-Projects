// include your own comments

#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

using namespace std;//

class Person
{   public:
		Person();
    	Person(const string &name);//This constructor will initialise the 'name' attribute
	    string getName() const;//This method will return the 'name' attribute.This is also known as a getter method.
	    void changeName(const string &newName);//This method will update the 'name' attribute with a new name.
    protected:
	    string name;//This is the attribute that will store the person's name
};

#endif
