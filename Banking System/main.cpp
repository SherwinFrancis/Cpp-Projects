#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include "Person.h"

using namespace std;

void updateFile(const string &PersonFile, const Person &authorizedUser)//This method is used to update the file after a transaction
{
    ::ifstream originalFile(PersonFile);//This line of code is used to open the file
    ::ofstream tempFile("TempAccount.txt");//This line of code is used to create a temporary file
    string line;//This line of code is used to store the line of the file
    while (getline(originalFile, line))//This while loop is used to read the file 
    {
        vector<std::string> userInfo;//This line of code is used to store the information of the user
        stringstream TextInfo(line);//This line of code is used to store the information of the user
        string Objects;

        while (getline(TextInfo, Objects, ','))//This while loop is used to store the information of the user
        {
            userInfo.push_back(Objects);//This line of code is used to store the information of the user
        }

        if (userInfo[0] + userInfo[1] == authorizedUser.getName() + authorizedUser.getPassword())//This if statement is used to check if the user is authorized
        {
            tempFile << authorizedUser.getName() << "," << authorizedUser.getPassword() << "," << authorizedUser.getAge() << ","
                     << authorizedUser.getPlaceOfBirth() << "," << authorizedUser.getBalance() << ",";//This and the above line of code will get the details of the user
            for (const auto &transaction : authorizedUser.getTransactions())//This for loop is used to store the transaction of the user
            {
                tempFile << transaction << ",";//This line is used to store the transaction of the user in the tempory file
            }
            tempFile << endl;//This line is used to move to the next line of the file
        }
        else
        {
            tempFile << line << '\n';//This line of code is used to store the information of the user in the temporary file
        }
    }
    originalFile.close();//This line of code is used to close the original file
    tempFile.close();//This line of code is used to close the temporary file

    filesystem::remove(PersonFile.c_str());//This line of code is used to remove the original 
    filesystem::rename("TempAccount.txt", PersonFile.c_str());//This line of code will rename the tempory file to the personfile
}

static void saveToFile(const Person &person, const string &filename)//This method will save the details of the person to the file
{
    ofstream outFile(filename, ios::app); // Open the file in append mode

    if (outFile.is_open())//This if statement will check if the file is open
    {
        outFile << person.getName() << "," << person.getPassword() << "," << person.getAge() << ","
                << person.getPlaceOfBirth() << "," << person.getBalance() << ",";// Write person's information to the file in a single line  

        
        for (const auto &transaction : person.getTransactions())// This for loop will write transactions to the file
        {
            outFile << transaction << ",";
        }

        outFile << endl; // Move to the next line for the next person
        outFile.close();
    }
    else
    {
        cerr << "Error when opening" << filename << std::endl;//This line will print the error message
    }
}

int main()
{
    int option_number;
    cout << "Welcome\nPlease select a number for the option of :\n"
         << endl;

    while (true)//This while loop will run until the user enters a valid input
    {
        cout << "1.Login" << endl;
        cout << "2.Register" << endl;
        cout << "3.Make a transaction" << endl;
        cout << "4.Exit" << endl;
        cin >> option_number;
        if (option_number == 1 || option_number == 2 || option_number == 3 || option_number == 4)//This if statement will check if the user entered a valid input or not
            break;
        else
        {
            cout << "Please try again by entering a valid input : " << endl;
            continue;//If the user entered an invalid input, the loop will continue until the user enters a valid input
        }
    }

    if (option_number == 1)//This is the option that will be invoked if the user would like to login
    {
        string firstname;
        string surname;
        string password;
        int errorMode = 0;

        cout << "Enter your first name: ";
        cin >> firstname;

        cout << "Enter your surname: ";
        cin >> surname;
        string username = firstname + " " + surname;

        cout << "Please enter your password: ";
        cin >> password;

        ifstream accountFile("persons.txt");// This line of code will look at the persons.txt file and read it 
        string UserInformation;
        vector<string> AuthenticatedUser;

        if (accountFile)//This if statement will check if the file is open or not
        {

            while (getline(accountFile, UserInformation))//This while loop will read the file
            {
                AuthenticatedUser.clear();//This line will clear the vector
                stringstream authentcate(UserInformation);//This line will read the file

                string FileInfo;
                while (getline(authentcate, FileInfo, ','))//This while loop will read the file
                {
                    AuthenticatedUser.push_back(FileInfo);//This line will read the file
                }
                if (AuthenticatedUser[0] + AuthenticatedUser[1] == username + password)//This if statement will check if the user is authenticated or not
                {
                    errorMode = 1; // In this line the default error mode is changed to stop the error message as the user is authenticated
                    string name = AuthenticatedUser[0];
                    string passKey = AuthenticatedUser[1];
                    int age = stoi(AuthenticatedUser[2]);
                    string placeOFBirth = AuthenticatedUser[3];
                    float balance = stof(AuthenticatedUser[4]);

                    Person AutherizedUser(name, passKey, age, placeOFBirth, balance);//This line will create a person object

                    for (int i = 5; i < AuthenticatedUser.size(); i++)//This for loop will read the file
                    {
                        AutherizedUser.appendTransaction(AuthenticatedUser[i]);//This line will read the file
                    }
                    cout << AutherizedUser << endl;//This line will print the person object
                    accountFile.close();//This line will close the file
                }
            }
            if (errorMode == 0)
            {
                cout << "Your login details are incorrect!" << endl;//This line will print the error message
            }
        }
    }
    else if (option_number == 2) //This is the option that will be invoked if the user would like to register
    {

        string firstname;
        string surname;
        string password;
        string place_of_birth;
        string currentbal;
        int age;
        int number_of_transactions;
        float balance;

        cout << "Enter your first name: ";//This line will print the message
        cin >> firstname;//This line will read the input

        cout << "Enter your surname: ";//This line will print the message
        cin >> surname;//This line will read the input
        string username = firstname + " " + surname;//This line will create a username
        ifstream existingUsers("persons.txt");// Check if the user already exists
        string line;//This line of code will store the line of the file
        bool userExists = false;//This sets the userExists variable to false

        while (getline(existingUsers, line))//This while loop will read the file 
        {
            stringstream ss(line);//This line of code will store the line of the file
            string firstToken;//This line of code will store the first token of the line
            getline(ss, firstToken, ',');//This line of code will store the first token of the line

            // Check if the first token (the first string) matches the desired username
            if (firstToken == username)//This if statement will check if the user already exists
            {
                userExists = true;//This line of code will set the userExists variable to true
                cout << "User with this username already exists. Please choose a different username." << endl;//This line will print the error messag
                existingUsers.close();//This line of code will close the file
                break;
            }
        }

        existingUsers.close();//This line of code will close the file

        if (userExists)//This if statement will check if the user already exists
        {
            return 0;//This line of code will return 0 to signify that the code has run without an error
        }
        cout << "Please enter your password: ";
        cin >> password;
        cout << "Please enter your place of birth: ";
        cin >> place_of_birth;
        cout << "Please enter your age: ";
        cin >> age;
        cout << "set your Initial Balance: ";
        cin >> currentbal;
        balance = stof(currentbal);

        Person user(username, password, age, place_of_birth, balance);//This line will create a new person object

        cout << "Please enter the number of transactions that you are initially going to add: ";
        cin >> number_of_transactions;
        for (int i = 0; i < number_of_transactions; i++)//This for loop will allow the user to enter the number of transactions that the user desires
        {
            int send_or_received;
            while (true)//This while loop will run until the user enters a valid input
            {
                cout << "Please enter 1 if you are receiving the money, Please enter 2 if you are sending money:  ";
                cin >> send_or_received;
                if (send_or_received == 1 || send_or_received == 2)//This if statement will check if the user entered a valid input or not
                    break;
                else
                {
                    cout << "plese enter a valid number:";
                    continue;//This continue statement will continue the loop until the user enters a valid input
                }
            }
            float amount;
            string counterParty;
            string TempAmount;

            cout << "Please enter the amount of the transaction: ";
            cin >> TempAmount;
            amount = stof(TempAmount);//This line will convert the string to a float

            if (send_or_received == 1)
            {
                cout << "Please enter the name of the recipient that you are recieving money from: ";
                cin >> counterParty;
                user.changeBalance(1, amount);//This line will change the balance of the user if they are going to gain money
                string TMessage = " from " + counterParty + " you recieved " + to_string(amount) + " pounds.";
                user.appendTransaction(TMessage);//This line will append the transaction to the user object
            }
            else if (send_or_received == 2)
            {
                cout << "Please enter the name of the recipient that you are sending money to: ";
                cin >> counterParty;
                user.changeBalance(2, amount);//This line will change the balance of the user if they are going to lose money
                string TMessage = "To " + counterParty + " you paid " + to_string(amount) + " pounds.";
                user.appendTransaction(TMessage);//This line will append the transaction to the user object
            }
            else
            {
                cout << "Please enter a valid number" << endl;
                cin >> send_or_received;
            }
        }

        saveToFile(user, "persons.txt");//This line will save the user to the file
    }
    else if (option_number == 3)//This is the option that will be invoked if the user would like to make a transaction
    {
        string firstname;
        string surname;
        string password;
        int errorMode = 0;

        cout << "Enter your first name: ";
        cin >> firstname;

        cout << "Enter your surname: ";
        cin >> surname;
        string username = firstname + " " + surname;

        cout << "Please enter your password: ";
        cin >> password;

        ifstream accountFile("persons.txt");//This line of code will look at the persons.txt file and read it
        string UserInformation;
        vector<string> AuthenticatedUser;
        int number_of_transactions;

        if (accountFile)//This if statement will check if the file is open or not
        {

            while (getline(accountFile, UserInformation))//This while loop will read the file line by line
            {
                AuthenticatedUser.clear();//This line will clear the vector
                stringstream authentcate(UserInformation);//This line will read the file

                string FileInfo;
                while (getline(authentcate, FileInfo, ','))//This while loop will get the line and authenticate the user
                {
                    AuthenticatedUser.push_back(FileInfo);//The line will read the file to authenticate the user 
                }
                if (AuthenticatedUser[0] + AuthenticatedUser[1] == username + password)//This if statement will check if the user is authenticated or not
                {
                    errorMode = 1; // default error mode is changed to stop the error message as the user is authenticated
                    string name = AuthenticatedUser[0];
                    string passKey = AuthenticatedUser[1];
                    int age = stoi(AuthenticatedUser[2]);
                    string placeOFBirth = AuthenticatedUser[3];
                    float balance = stof(AuthenticatedUser[4]);

                    Person AutherizedUser(name, passKey, age, placeOFBirth, balance);//This line is basically a constructor

                    for (int i = 5; i < AuthenticatedUser.size(); i++)//This for loop will append all the transactions to the user object
                    {
                        AutherizedUser.appendTransaction(AuthenticatedUser[i]);
                    }
                    accountFile.close();//This line will close the file
                    cout << "Please enter the number of transactions that you are initially going to add: ";
                    cin >> number_of_transactions;
                    for (int i = 0; i < number_of_transactions; i++)//This for loop will allow the user to enter the number of transactions that the user desires
                    {
                        int send_or_received;
                        while (true)//This while loop will run until the user enters a valid input
                        {
                            cout << "Please enter 1 if you are receiving the money, Please enter 2 if you are sending money:  ";
                            cin >> send_or_received;
                            if (send_or_received == 1 || send_or_received == 2)//This if statement checks if the user has wants to send or receive
                                break;
                            else
                            {
                                cout << "plese enter a valid number:";
                                continue;
                            }
                        }
                        float amount;
                        string counterParty;
                        string TempAmount;

                        cout << "Please enter the amount of the transaction: ";
                        cin >> TempAmount;
                        amount = stof(TempAmount);

                        if (send_or_received == 1)//This if statement checks if the user wants to send or receive money
                        {
                            cout << "Please enter the name of the recipient that you are recieving money from: ";

                            cin >> counterParty;
                            AutherizedUser.changeBalance(1, amount);//This line will change the balance of the user if they are going to gain money
                            string TMessage = " from " + counterParty + " you recieved " + to_string(amount) + " pounds.";
                            AutherizedUser.appendTransaction(TMessage);//This line will append the transaction to the user object
                        }
                        else if (send_or_received == 2)
                        {
                            cout << "Please enter the name of the recipient that you are sending money to: ";
                            cin >> counterParty;
                            AutherizedUser.changeBalance(2, amount);//This line will change the balance of the user if they are going to lose money
                            string TMessage = "To " + counterParty + " you paid " + to_string(amount) + " pounds.";
                            AutherizedUser.appendTransaction(TMessage);//This line will append the transaction to the user object
                        }
                        else//If the user does not enter a valid then this else statement will be invoked
                        {
                            cout << "Please enter a valid number" << endl;
                            cin >> send_or_received;
                        }

                        updateFile("persons.txt", AutherizedUser);//This line will update the file
                    }
                }
            }
            if (errorMode == 0)
            {
                cout << "Your login details are incorrect!" << endl;
            }
        }
    }
    else if (option_number == 4)
    {
        cout << "Thanks for using the service have a great day!" << endl;
        cout << "Exiting the Service" << endl;//Exiting the code cleanly
        return 0;
    }

    return 0;
}
