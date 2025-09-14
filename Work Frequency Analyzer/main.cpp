//Including all of the libraries and the header files
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "ReadWords.h"
#include <algorithm>
#include <cctype>



using namespace std;//This line of code will make the coding process slightly easier as we do not need to type in std :: before every instance of cout and cerr,etc

void generateBarGraph(const vector<string>& words, const vector<int>& occurrences, int totalWords,string outputfile)//This function will generate a bar graph
{
    ofstream outputFile(outputfile);//This line of code will open the output file
    bool isFileOpen = outputFile.is_open();//This line of code will check if the file is open

    switch (isFileOpen)//This switch statement will check if the file is open and if it is open it will print the word occurrence of and if it is not open it will print an error message
    {
        case true://If the case is true it will print the word occurrence 
            std::cout << "Word Occurrence of:" << std::endl;
            outputFile << "Word Occurrence of:" << std::endl;
            break;
        case false://If the case is false it will print an error message with the cerr method
            std::cerr << "Error opening output file." << std::endl;
            break;

    }

    for (size_t i = 0; i < words.size(); i++)//This for loop will iterate through the words vector
    {
        if (occurrences[i] != 1)//This if statement will check if the occurrence of the word is not 1, this has been created because if a word occurs once we need to say it as ocurrence as opposed to occurences
        {
            float percentage = (static_cast<float>(occurrences[i]) / totalWords) * 100;//This line calculates what percentage of the total amount of words is the current/given word
            cout << setw(8) << setfill(' ') << left << words[i] <<  setfill('=') << setw(occurrences[i] + 1) << right  << " " << occurrences[i] << " Occurences " << setprecision(3) << fixed << "("<< percentage << "%)" << endl;//This line will output the whole bar grah along with the percentage and the number of occurences
            outputFile << setw(8) << setfill(' ') << left << words[i] << setfill('=') << setw(occurrences[i] + 1) << right  << " " << occurrences[i] << " Occurences " << setprecision(3) << fixed << "("<< percentage << "%)" << endl;//This line will basically put the output of the previous line in the file that has been chosen by the user
        }
        else
        {
            float percentage = (static_cast<float>(occurrences[i]) / totalWords) * 100;//This line calculates what percentage of the total amount of words is the current/given word
            cout << setw(8) << setfill(' ') << left << words[i]  << setfill('=') << setw(occurrences[i] + 1) << right  << " " << occurrences[i] << " Occurence " << setprecision(3) << fixed <<"(" <<percentage << "%)" << endl;//This line will output the whole bar grah along with the percentage and the number of occurences
            outputFile << setw(8) << setfill(' ') << left << words[i] << setfill('=') << setw(occurrences[i] + 1) << right  << " " << occurrences[i] << " Occurence " << setprecision(3) << fixed<<"(" << percentage << "%)" << endl;//This line will basically put the output of the previous line in the file that has been chosen by the user
        }
    }

    outputFile.close();//This line will close the file that has been chosen by the user
}

void enterNewWords(const std::string& wordListFile)//This function will allow the user to enter new words
{
    std::ofstream wordListOutput(wordListFile);//This line of code will open the file that has been chosen by the user

    if (wordListOutput.is_open())//This if statement will check if the file is open and if it is open it will print the word occurrence of and if it is not open it will print an error message
    {
        std::string word;//This line of code will create a string variable called word
        std::cout << "Enter up to 5 search words, please make sure all of them are separated by spaces:" << std::endl;

        for (int i = 0; i < 5 && std::cin >> word; ++i)//This for loop will iterate through the words and if the user enters 5 words it will stop iterating
        {
            wordListOutput << word << std::endl;//This line of code will write the word to the file that has been chosen by the user
        }

        wordListOutput.close();//This line of code will close the file that has been chosen by the user (for writing the words that they would like to search)
        std::cout << "File created and words written successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error creating/opening word list file. Please enter a valid file name." << std::endl;
    }
}



int main()
{
    string inputFile, wordListFile, outputFile;//This line of code will create 3 string variables called inputFile, wordListFile and outputFile

    while (true)//This while loop will keep looping until the user enters a valid file name for the input file and it will break out of the loop if the file is successfully opened
    {
        cout << "Enter the name of the text file to be analyzed: ";
        cin >> inputFile;//This line of code will take the name of the file that the user would like to analyze and store it in the inputFile variable

        ifstream inputCheck(inputFile);//This line of code will open the file that the user would like to analyze and store it in the inputCheck variable
        if (inputCheck.is_open())//This if statement will check if the file is open and if it is open it will print the word occurrence of and if it is not open it will print an error message
        {
            inputCheck.close();//This line of code will close the file that the user would like to analyze and store it in the inputCheck variable
            break;
        }
        else
        {
            cout << "Error opening file. Please enter a valid file name." << endl;
        }
    }

        std::cout << "Do you want to enter new words again? (enter 'yes' or 'no'): ";
        std::string answer;
        std::cin >> answer;//This line of code will take the answer from the user and store it in the answer variable
        
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);//This line of code will convert the answer to lowercase and store it in the answer variable

        if (answer == "yes")//This if statement will check if the answer is yes and if it is yes it will call the enterNewWords function and if it is not yes it will print an error message
        {
            cout << "Enter the name of the file where you want to store the new words  : ";
            cin >> wordListFile;//This line of code will take the name of the file where the new words will be stored and store it in the wordListFile variabl
            enterNewWords(wordListFile);//This line of code will call the enterNewWords function and pass the wordListFile variable as an argument
        }
        else 
        {
            std::cout << "Enter the name of the file where the search words are stored : ";
            std::cin >> wordListFile;//This line of code will take the name of the file where the search words are stored and store it in the wordListFile variable
        }

    cout << "Enter the name of the output file: ";
    cin >> outputFile;//This line of code will take the name of the output file and store it in the outputFile variable

    ifstream wordList(wordListFile);//This line of code will open the file where the search words are stored and store it in the wordList variable
    if (wordList.is_open() == false)//This if statement will check if the file is open and if it is not open it will print an error message and return 1 from the main function
    {
        cerr << "Error opening word list file." << endl;//This line of code will print an error message and return 1 from the main function
        return 1;//This line of code will return 1 from the main function signifying that the code has had an error
    }

    vector<string> searchWords;//This line of code will create a vector called searchWord
    string word;
    while (wordList >> word)//This while loop will iterate through the words in the file and store them in the searchWords vector
    {
        searchWords.push_back(word);//This line of code will push the word into the searchWords vector
    }
    wordList.close();//This line of code will close the file where the search words are stored and store it in the wordList variable

    vector<int> wordOccurrences(searchWords.size(), 0);//This line of code will create a vector called wordOccurrences and initialize it with the size of the searchWords vector and all elements initialized to 0
    int totalWords = 0;//This line of code will initialize a variable called totalWords and set it to 0

    ReadWords reader(inputFile.c_str());//This line of code will create a ReadWords object called reader and pass the inputFile variable as an argument
    while (reader.is_Next())//This while loop will iterate through the words in the inputFile and store them in the reader object and increment the totalWords variable and the wordOccurrences vector accordingly
    {
        string currentWord = reader.get_Next();//This line of code will get the next word in the inputFile and store it in the currentWord variable

        for (size_t i = 0; i < searchWords.size(); i++)//This for loop will iterate through the searchWords vector and if the current word is equal to the search word it will increment the wordOccurrences vector and break out of the loop
        {
            if (currentWord == searchWords[i])//This if statement will check if the current word is equal to the search word and if it is it will increment the wordOccurrences vector and break out of the loop
            {
                wordOccurrences[i]++;//This line of code will increment the wordOccurrences vector at the current index i
                break;
            }
        }

        totalWords++;//This line of code will add 1 to the totalWords variable
    }
    reader.close();//This line will close the inputFile and store it in the reader object

    generateBarGraph(searchWords, wordOccurrences, totalWords,outputFile);//This line will call the generateBarGraph function and pass the searchWords, wordOccurrences, totalWords and outputFile variables as arguments

    return 0;//This line of code will return 0 from the main function signifying that the code has been executed successfully and no errors have been encountered.
}
