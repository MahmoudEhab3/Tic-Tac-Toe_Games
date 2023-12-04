// File: A3_S1_20220457_Problem2.cpp
// Purpose: Document Similarity
// Author: Mahmoud Ehab
// Section: S1
// ID: 20220457
// TA: Khaled Ibrahim

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

// Main definition of class
class StringSet{
private:
    vector <string> mainSet;
public:
    // Getter function to get the mainSet vector
    vector <string> & getVector(){ return mainSet; };
    // Constructor to load the words in a given file
    StringSet(fstream & file);
    // Constructor to load the string passed & breaks it to tokens
    StringSet(string text = "");
    // Add a certain string to the set
    void addStr(string toAdd);
    // Remove a certain string from the set
    void removeStr(string toRemove);
    // Clear the entire set
    void clearSet();
    // Return number of strings in the set
    long strCount();
    // Output all strings in the set
    void printSet();
    // Overload the "+" operator to return the union of two sets
    StringSet operator + (StringSet & anotherSet);
    // Overload the "*" operator to return the intersection of two sets
    StringSet operator * (StringSet & anotherSet);
    // Check the similarity of two StringSet objects
    double checkSimilarity(StringSet & anotherSet);
};
//_____________________________________________________________________________________
// Convert the text entered into lowercase with no punctuation marks
string & modifyText(string & text){
    for(int i = 0; i < text.length(); ++i){
        // Check if the character is already lowercase, ignore it
        if((text[i] >= 97) && (text[i] <= 122))
        { continue; }
        // Check if the character is letter or number, convert it to lowercase
        if(isalnum(text[i]))
        { text[i] = tolower(text[i]); }
            // Check if the character is space and the next character
            // is not space make it only one space
        else if(isspace(text[i]) && !isspace(text[i + 1]))
        { text[i] = ' '; }
            // Convert any other character to null character
        else
        { text[i] = '\0'; }
    }
    // Remove all null characters from the string
    text.erase(remove(text.begin(), text.end(), '\0'), text.end());
    return text;
}

// Constructor to load text from file to the mainSet vector
StringSet :: StringSet(fstream & file){
    // Loop over the file and load each string to the vector
    string word;
    while(file >> word){
        // Check if the word is found before or not to take
        // only one instance of the word to prevent repeating
        if(find(mainSet.begin(), mainSet.end(), word) == mainSet.end())
        { mainSet.push_back(modifyText(word)); }
    }
}

// Constructor to load text from parameter to the mainSet vector
StringSet :: StringSet(string text){
    text = modifyText(text);
    // Convert the coming string into input string stream
    istringstream ss(text);
    string word;
    // Split the passed string into separate words
    while(ss >> word){
        // Check if the word is found before or not to take
        // only one instance of the word to prevent repeating
        if(find(mainSet.begin(), mainSet.end(), word) == mainSet.end())
        { mainSet.push_back(word); }
    }
}

// Add certain string to the set
void StringSet :: addStr(string toAdd){
    toAdd = modifyText(toAdd);
    // Convert the coming string into input string stream
    istringstream ss(toAdd);
    string word;
    // Split the passed string into separate words
    while(ss >> word){
        // Check if the word is found before or not to take
        // only one instance of the word to prevent repeating
        if(find(mainSet.begin(), mainSet.end(), word) == mainSet.end())
        { mainSet.push_back(word); }
    }
}

// Remove certain string from the set
void StringSet :: removeStr(string toRemove){
    // Loop over the set to check for the word to remove
    for(int i = 0; i < mainSet.size(); ++i){
        // If the word is found, remove it from the set
        if(mainSet[i] == toRemove){
            mainSet.erase(mainSet.begin() + i);
            cout << "The word \"" << toRemove << "\" is removed from the set.\n";
            return;
        }
    }
    // If the word is not found in the set
    cerr << "The word \"" << toRemove << "\" is NOT in the set!\n";
}

// Clear all elements in the set
void StringSet :: clearSet(){ mainSet.clear(); }

// Return current number of strings in the set
long StringSet :: strCount(){ return mainSet.size(); }

// Output all strings in the set
void StringSet :: printSet(){
    for(string word : mainSet)
    { cout << word << " "; }
    cout << endl;
}

// Overload the "+" operator to return the union of two sets
StringSet StringSet :: operator + (StringSet & anotherSet){
    StringSet unionOfSets;
    // Copy strings from the current set to unionOfSets
    unionOfSets.mainSet = this->mainSet;
    // Copy strings from the passed set to unionOfSets
    for(string word : anotherSet.getVector())
    { unionOfSets.mainSet.push_back(word); }
    // Return the object after combining the sets in it
    return unionOfSets;
}

// Overload the "*" operator to return the intersection of two sets
StringSet StringSet :: operator * (StringSet & anotherSet){
    StringSet intersectionOfSets;
    // Loop over the two sets and check if there is common words
    for(string word : this->mainSet){
        for(string anotherWord : anotherSet.getVector()){
            // Add the common words to the intersectionOfSets
            if(word == anotherWord)
            { intersectionOfSets.mainSet.push_back(word); }
        }
    }
    // Return the common elements between the two sets
    return intersectionOfSets;
}

// Check the similarity of two StringSet objects
double StringSet :: checkSimilarity(StringSet & anotherSet){
    int commonWords = 0;
    double similarityFactor = 0.0;
    // Get the number of common words using methods in class StringSet
    commonWords = (*this * anotherSet).strCount();
    // (*this * anotherSet) returns an object with the common words between the two sets
    // strCount() returns the number of these common words
    cout << "Number of common Words = " << commonWords << endl;
    // Compute the similarity factor using the binary cosine coefficient equation
    similarityFactor = commonWords / (sqrt(this->strCount()) * sqrt(anotherSet.strCount()));
    cout << "Similarity Factor = ";
    return similarityFactor;


}


//_______________________________________________________________________________________________________
int main(){
    // Testing filename constructor
    string fileName;
    cout << "Enter filename: ";
    cin >> fileName;
    // Create filestream object to pass to the constructor
    fstream inputFile(fileName);
    // Check if the file exists or not
    if(!inputFile)
        cerr << "The file \"" << fileName << "\" is NOT found!\n";
    else{
        StringSet set0(inputFile);
        cout << "set0 contents: ";
        set0.printSet();
    }

    // Initializing objects with strings
    StringSet set1("Chocolate ice cream, chocolate milk, and chocolate bars are delicious.");
    StringSet set2("I love chocolate bars very much! They are delicious.");

    // Printing the contents of the two sets
    cout << "set1 contents: ";
    set1.printSet();
    cout << "set2 contents: ";
    set2.printSet();

    // Checking similarity using binary cosine coefficient
    cout << "Checking the similarity \n";
    cout << set1.checkSimilarity(set2) << endl;

    // Testing the addition of string to a set
    cout << "Adding text\n";
    set2.addStr("This is some more new text!");
    cout << "New content: ";
    set2.printSet();

    // Print the number of strings in the set
    cout << "Number of words in set2 is " << set2.strCount();

    // Removing all strings in the set and clearing its contents
    cout << "Cleared\n";
    set2.clearSet();

    // Initializing more objects
    StringSet set3("Chocolate is made out of cocoa seeds.");
    StringSet set4("Milk is a necessary ingredient in the ice cream.");
    cout << "set3 contents: ";
    set3.printSet();
    cout << "set4 contents: ";
    set4.printSet();

    // Testing the union of two sets by overloaded + operator
    set2 = set3 + set4;
    cout << "set2 now is the union of set3 and set4!\n";
    cout << "New content: ";
    set2.printSet();

    // Testing the intersection of two sets by overloaded * operator
    StringSet set5 = set1 * set2;
    cout << "set5 is the intersection of set1 and set2!\n";
    cout << "set5 contents: ";
    set5.printSet();

    // Testing the removal of string from a set
    StringSet set6("You are you test string and if you know you know");
    cout << "set6 contents: "; set6.printSet();
    cout << "Removing word from set6....\n"; set6.removeStr("you");
    cout << "New content: "; set6.printSet();
    return 0;
}