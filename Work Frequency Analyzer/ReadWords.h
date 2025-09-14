//Importing the required classes
#include <string>
#include <fstream>

//Defining the class "Readwords"
class ReadWords
{
public://The public keyword signifies that the members of this class are accessible from outside the class.
    ReadWords(const char *filename);//This constructor is used to initialize the object of the class.It takes a filename as a parameter and then opens that fiile.
    void close();//This line makes sure that the file is closed ensuring most efficient use of available resources
    std::string get_Next();//This function is used to get the next word from the file.It returns the next word as a string of characters.
    bool is_Next();//This function checks if there is a next word in the file.It returns true if there's a next word and false if there is no next word.

private://The private keyword signifies that the members of this class are only accessible from within the class.
    std::ifstream word_file;//This line declares a variable of type ifstream called wordfile.This variable will be used to read the words from the file.
    std::string next_word;//This method is used for storing the next word in the file. 
    bool end_of_file_or_not;//This method checks if the end of the file has been reached.It returns true if the end of the file has been reached and false otherwise.
};

ReadWords::ReadWords(const char *filename)//This constructor is used to initialize the object of the class.It takes a filename as a parameter and then opens that fiile.
{
    word_file.open(filename);//This line opens the file with the filename that is passed to the constructor.
    switch(word_file.is_open())//This switch statement checks if the file is open.If it is, it sets the end_of_file_or_not flag to false.If it is not, it sets the end_of_file_or_not flag to true.
    {
    case true://This case is executed if the file is open.
        end_of_file_or_not = false;//This line sets the end_of_file_or_not flag to false.
        break;
    case false://This case is executed if the file is not open.
        std::cerr << "Error opening file." << std::endl;//This line prints an error message to the console.
        exit(1);//This line exits the program with an error code of 1 to signify that the code has run with an error
        break;
    }
}

void ReadWords::close()//This method closes the file.
{
    word_file.close();
}

std::string ReadWords::get_Next()//This method reads the next word from the file and returns it as a string of characters.
{
    std::string word;//This line declares a string variable called word.This variable will be used to store the next word.
    char c;//This line declares a character variable called c.This variable will be used to store the next character from the file.

    while (word_file.get(c))//This while loop reads the next character from the file until it finds a non-alphabetic character.
    {
        if (std::isalpha(c))//This if statement checks if the character is alphabetic.If it is, it breaks out of the loop.
        {
            word += std::tolower(c); //This line converts the character to lowercase and appends it to the word string.
            break;
        }
    }

    while (word_file.get(c))//This while loop reads the next character from the file until it finds a non-alphabetic character.
    {
        if (std::isalpha(c))//This if statement checks if the character is an alphabetic character.If it is, it appends it to the word string.
        {
            word += std::tolower(c);//This line converts the character to lowercase and appends it to the word string.
        }
        else
        {
            break; // Reached non-alphabetic character, stop reading hence breaks out of the while loop.
        }
    }

    
    if (word.empty())// This if statement is used to check if the word is empty (no letters)
    {
        end_of_file_or_not = true;//This line sets the end_of_file_or_not flag to true.
    }

    return word;
}

bool ReadWords::is_Next()//This method checks if there is a next word in the file.It returns true if there's a next word and false if there is no next word.
{
    if (end_of_file_or_not || !word_file)//This if statement checks if the end of the file has been reached or if the file is not open.If either of these conditions are true, it returns false.
    {
        return false;//This line returns false as the new flag as there is no next word. 
    }

    char c;//This line declares a character variable called c.This variable will be used to store the next character from the file.
    while (word_file.get(c))//This while loop reads the next character from the file until it finds a non-alphabetic character(which will be used as a delimiter).
    {
        if (std::isalpha(c))//This if statement checks if the character is alphabetic.If it is, it returns true.
        {
            word_file.putback(c); // This line puts the character back into the file stream.
            return true;//This line returns true as there is a next word.
        }
    }

    
    if (!word_file)//This if statement checks if the file is empty.If it is, it sets the end_of_file_or_not flag to true.
    {
        end_of_file_or_not = true;//This line sets the end_of_file_or_not flag to true.
    }

    return false;
}
