#include "Person.h"

//Below are the overloading constructors
Person::Person(const string name, const string password, int age, const string placeOfBirth, float balance)
    : name(name), password(password), age(age), placeOfBirth(placeOfBirth), balance(balance) {}

Person::Person(const string name, const string password, int age, const string placeOfBirth, float balance, const vector<string> &transactions)
    : name(name), password(password), age(age), placeOfBirth(placeOfBirth), balance(balance), transactions(transactions) {}

// Below are the getter methods for the members
string Person::getName() const
{
    return name;
}
string Person::getPassword() const
{
    return password;
}

int Person::getAge() const
{
    return age;
}

string Person::getPlaceOfBirth() const
{
    return placeOfBirth;
}

float Person::getBalance() const
{
    return balance;
}

const vector<string> &Person::getTransactions() const
{
    return transactions;
}

// The methods below are used to modify the members of the class
void Person::appendTransaction(const string &line)
{
    transactions.push_back(line);
}

void Person::changeBalance(int modifyer, float value)//This line of code is used to modify the balance of the user
{
    if (modifyer == 1)//This if statement is used to modify the balance of the user 
    {
        balance += value;
    }
    else if (modifyer == 2)
    {
        balance -= value;
    }
}

ostream &operator<<(ostream &o, const Person &AuthorizedUser)//This line of code is used to print the user information
{

    o << "Welcome " << AuthorizedUser.getName() << "!\n";
    o << "Your age is " << AuthorizedUser.getAge() << "\n";
    o << "You were born in " << AuthorizedUser.getPlaceOfBirth() << "\n";
    o << "Your current Balance is " << AuthorizedUser.getBalance() << " pounds\n";
    o << "---> Your latest Transactions are\n";

    const vector<string> &transactions = AuthorizedUser.getTransactions();//This line of code is used to print the user information
    int latestPosition = max(0, static_cast<int>(transactions.size()) - 3);//This line of code is used to print the user information

    for (int i = latestPosition; i < transactions.size(); ++i)//This for loop is used to print the user information
    {
        o << "[" << transactions[i] << "]\n";//This line of code is used to print the user information 
    }
    return o;
}
