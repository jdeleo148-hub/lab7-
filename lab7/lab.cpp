/////////////////////////////////////////////////////////////////////
// Name: Joel Deleon
// Date: 11/11/2026
// Class: CSCI 1470.0X
// Semester: Fall 2026
// Instructor: Dr. Jonatan Reyes
// Program Description:
// Spell checker program using Linear Search (sorted/unsorted)
// and Binary Search.
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// Global Constants
const int MAX_WORDS = 466551;

const string LINEAR_SEARCH_UNSORTED = "LINEAR_UNSORTED";
const string LINEAR_SEARCH_SORTED = "LINEAR_SORTED";
const string BINARY_SEARCH = "BINARY";

const bool DEBUG = true;

// Function Prototypes
void initializeArray(string words[], int size);
bool populateArray(string words[], int size, string fileName);
int countWords(string words[], int size);

bool linearSearchUnsorted(string words[],int size,string target);

bool linearSearchSorted(string words[],int size,string target);

bool binarySearchWord(string words[],int size,string target);

bool checkSpelling(string words[],int size,string target,string searchType);

int main()
{
ifstream file("dictionary.txt");

cout << (file ? "FOUND" : "NOT FOUND") << endl;

    string* dictionary = new string[MAX_WORDS];

    initializeArray(dictionary, MAX_WORDS);

    bool dictionaryLoaded =
        populateArray(dictionary, MAX_WORDS,"dictionary.txt");

    if (!dictionaryLoaded)
    {
        cout << "Error opening dictionary file."
             << endl;

        delete[] dictionary;
        return 1;
    }

    int totalWords =
        countWords(dictionary,MAX_WORDS);

    ifstream settingsFile("settings.txt");

    if (!settingsFile)
    {
        cout << "Error opening settings file."
             << endl;

        delete[] dictionary;
        return 1;
    }

    int maxMistakes;
    string searchType;

    settingsFile >> maxMistakes;
    settingsFile >> searchType;

    settingsFile.close();

    cout << "*****************************"
         << endl;

    cout << "Welcome to the spell checker!"
         << endl;

    cout << "*****************************"
         << endl;

    int mistakes = 0;
    bool firstWord = true;
    char continueChoice = 'Y';

    while (mistakes < maxMistakes &&
          (continueChoice == 'Y' ||
           continueChoice == 'y'))
    {
        string word;

        if (firstWord)
        {
            cout << "\nPlease enter a word: ";
        }
        else
        {
            cout << "\nEnter another word: ";
        }

        cin >> word;

        auto start =
            high_resolution_clock::now();

        bool found = checkSpelling(dictionary, totalWords,word, searchType);

        auto end = high_resolution_clock::now();

        duration<double, micro> elapsed =
            end - start;

        if (found)
        {
            cout << "The word " << word << " is spelled correctly!"
                 << endl;
        }
        else
        {
            cout << "Oops! It looks like '" << word << "' isn't quite right. " << "No worries, you're doing " << "great-let's try spelling it again." << endl;

            mistakes++;
        }

        if (DEBUG)
        {
            if (searchType == LINEAR_SEARCH_UNSORTED)
            {
                cout << "Linear search took " << elapsed.count() << " microseconds." << endl;
            }
            else if (searchType == LINEAR_SEARCH_SORTED)
            {
                cout << "Linear search took "<< elapsed.count()<< " microseconds." << endl;
            }
            else if (searchType ==  BINARY_SEARCH)
            {
                cout << "Binary search took "<< elapsed.count()<< " microseconds." << endl;
            }
        }

        if (mistakes >= maxMistakes)
        {
            break;
        }

        cout << "\nDo you want to continue (Y/N): ";
        cin >> continueChoice;

        firstWord = false;
    }

    if (mistakes >= maxMistakes)
    {
        cout << "\nYou have reached the maximum " << "number (" << maxMistakes<< ") of misspelled words allowed." << endl;
    }

    cout << "\nThank you for using the spell checker!" << endl;

    delete[] dictionary;

    return 0;
}

void initializeArray(string words[],int size)
{
    for (int i = 0; i < size; i++)
    {
        words[i] = "";
    }
}

bool populateArray(string words[], int size,string fileName)
{
    ifstream inputFile(fileName);

    if (!inputFile)
    {
        return false;
    }

    string word;
    int index = 0;

    while (inputFile >> word &&
           index < size)
    {
        words[index] = word;
        index++;
    }

    inputFile.close();

    return true;
}

int countWords(string words[],int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (words[i] != "")
        {
            count++;
        }
    }

    return count;
}

bool linearSearchUnsorted(string words[], int size,string target)
{
    for (int i = 0; i < size; i++)
    {
        if (words[i] == target)
        {
            return true;
        }
    }

    return false;
}

bool linearSearchSorted(string words[], int size,string target)
{
    sort(words, words + size);

    for (int i = 0; i < size; i++)
    {
        if (words[i] == target)
        {
            return true;
        }
    }

    return false;
}

bool binarySearchWord(string words[], int size,string target)
{
    sort(words, words + size);

    int first = 0;
    int last = size - 1;

    while (first <= last)
    {
        int middle =
            (first + last) / 2;

        if (words[middle] == target)
        {
            return true;
        }

        if (words[middle] < target)
        {
            first = middle + 1;
        }
        else
        {
            last = middle - 1;
        }
    }

    return false;
}

bool checkSpelling(string words[],int size, string target,string searchType)
{
    if (searchType == LINEAR_SEARCH_UNSORTED)
    {
        return linearSearchUnsorted( words,size, target);
    }

    if (searchType ==  LINEAR_SEARCH_SORTED)
    {
        return linearSearchSorted( words,size,target);
    }

    if (searchType == BINARY_SEARCH)
    {
        return binarySearchWord(words, size,target);
    }

    return false;
}
