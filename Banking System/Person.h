#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <string>

using namespace std; // Use the entire std namespace

class Person//This class represents a person with their name, password, age, place of birth, balance, and transactions.
{
private://These are the private members of the class.They can only be accessed within the class.
    string name;
    string password;
    int age;
    string placeOfBirth;
    float balance;
    vector<string> transactions;

public://These are the public members of the class.They can be accessed outside the class.
    // Constructor overloading
    Person(const string name, const string password, int age, const string placeOfBirth, float balance);
    Person(const string name, const string password, int age, const string placeOfBirth, float balance, const vector<string> &transactions);

    //Below are the methods that return the private members of the class.
    string getName() const;
    string getPassword() const;
    int getAge() const;
    string getPlaceOfBirth() const;
    float getBalance() const;
    const vector<string> &getTransactions() const; // Return const reference

    //Below are the methods that modify the private members of the class.
    void appendTransaction(const string &line);
    void changeBalance(int modifyer, float value);
    friend ostream &operator<<(ostream &o, const Person &person);
};

#endif
