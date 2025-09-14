//The following four lines import classes that are required
#include "ReadWords.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

using namespace std;//This line makes it so that we can use cout and cin without having to write std::cout and std::cin.

string removePunct(string word)//This function removes punctuation from the front and back of the word.
{
    while (word.empty() == false && ispunct(word.front() == true))//This while loop removes punctuation from the front of the word.
    {
        word.erase(word.begin());//This line erases the first character of the word as it will be a punctuation mark.
    }

    while (word.empty() == false && ispunct(word.back()  == true))//This while loop removes punctuation from the back of the word.
    {
        word.pop_back();//This line removes the last character of the word as it will be a punctuation mark.
    }

    return word;//This line returns the word.
}

ReadWords::ReadWords(const char *fname)//This constructor takes in a file name and opens it.
{
    word_file.open(fname); // This line opens the file

    if (!word_file)//This if statement checks if the file is open.
    {
        cout << "Failed to open " << fname << endl;//This line prints out a message if the file is not open.
        exit(1);//This line exits the program with error code 1 as there has been a problem
    }

    word_file >> next_word;//This line reads the first word from the file and stores it in the next_word variable.
    end_of_file_or_not = false;//This line sets the end_of_file_or_not flag to false as there is still a word to be read.
}

string ReadWords::get_Next()//This function returns the next word from the file.
{
    string word = next_word;//This line stores the next word in the word variable.
    word_file >> next_word;//This line reads the next word from the file and stores it in the next_word variable.

    if (word_file.eof() == true)
        end_of_file_or_not = true;//This line sets the end_of_file_or_not flag to true to signify end of the file has been reached.
        word = removePunct(word);//This line removes punctuation from the front and back of the word.
        bool isWord = false;//This line initializes the isWord flag to false.
        
    for (char c : word)//This for loop checks if the word contains any letters.
    {
        if (isalpha(c) == true)//This if statement checks if the character is a letter.
        {
            isWord = true;//This line sets the isWord flag to true if a letter is found.
            break;
        }
    }
    

    if (isWord == true)//This if statement converts the word to lowercase if it contains any letters.
    {
        for (char &c : word)//This for loop converts the all the letters in the word to lowercase.
        {
            c = tolower(c);//This line converts the letter to lowercase.
        }
    }
    else
    {
        word = ""; //This line sets the word to an empty string if it does not contain any letters.
    }

    return word;
}

bool ReadWords::is_Next()//This function checks if there is a next word in the file.It returns true if there is a next word, false otherwise.
{
    return !end_of_file_or_not;//This line returns the value of the end_of_file_or_not flag.
}

void ReadWords::close()//This function closes the file.
{
    word_file.close(); //This line closes the file.
}
