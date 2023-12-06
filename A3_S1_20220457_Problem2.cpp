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
    // Add a certain string 
    void addStr(string toAdd);
    // Remove a certain string 
    void removeStr(string toRemove);
    // Clear the entire line
    void clearSet();
    // Return number of words
    long strCount();
    // Output all strings 
    void printSet();
    // Overload the "+" operator to return the union 
    StringSet operator + (StringSet & anotherSet);
    // Overload the "*" operator to return the intersection 
    StringSet operator * (StringSet & anotherSet);
    // Check the similarity
    double checkSimilarity(StringSet & anotherSet);
};
//_____________________________________________________________________________________
// Convert the text entered into lowercase with no punctuation marks
string & modifyText(string & text){
    for(int i = 0; i < text.length(); ++i){
        // Check if the character is already lowercase
        if((text[i] >= 97) && (text[i] <= 122))
        { continue; }
        // Check if the character is letter or number
        if(isalnum(text[i]))
        { text[i] = tolower(text[i]); }
           
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

// Add certain string 
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

// Remove a string 
void StringSet :: removeStr(string toRemove){
    for(int i = 0; i < mainSet.size(); ++i){
        if(mainSet[i] == toRemove){
            mainSet.erase(mainSet.begin() + i);
            cout << "The word \"" << toRemove << "\" is removed.\n";
            return;
        }
    }
    cerr << "The word \"" << toRemove << "\" is not found\n";
}

// Clear all elements 
void StringSet :: clearSet(){ mainSet.clear(); }

// Return current number of words
long StringSet :: strCount(){ return mainSet.size(); }

// Output all strings 
void StringSet :: printSet(){
    for(string word : mainSet)
    { cout << word << " "; }
    cout << endl;
}

// Overload the "+" operator to return the union
StringSet StringSet :: operator + (StringSet & anotherSet){
    StringSet unionOfSets;
    unionOfSets.mainSet = this->mainSet;
    for(string word : anotherSet.getVector())
    { unionOfSets.mainSet.push_back(word); }
    // Return the object after combining the sets in it
    return unionOfSets;
}

// Overload the "*" operator to return the intersection
StringSet StringSet :: operator * (StringSet & anotherSet){
    StringSet intersectionOfSets;
    for(string word : this->mainSet){
        for(string anotherWord : anotherSet.getVector()){
            // Add the common words to the intersectionOfSets
            if(word == anotherWord)
            { intersectionOfSets.mainSet.push_back(word); }
        }
    }
    return intersectionOfSets;
}

// Check the similarity
double StringSet :: checkSimilarity(StringSet & anotherSet){
    int commonWords = 0;
    double similarityFactor = 0.0;
    // Get the number of common words using methods in class StringSet
    commonWords = (*this * anotherSet).strCount();
    // (*this * anotherSet) returns an object with the common words 
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
        cerr << "The file \"" << fileName << "\" is not found!\n";
    else{
        StringSet set0(inputFile);
        cout << "set0 contents: ";
        set0.printSet();
    }

    // Initializing objects with strings
    StringSet line1("Football is popular because it has the power to unite people.");
    StringSet line2("Football is a fun exercise that may increase your fitness levels and boost your self-confidence.");
    StringSet line3("it aids in enhancement your system .");
    StringSet line4("it’s also a fantastic activity for people looking to enhance their cognitive function.");

    // Printing the contents of the two sets
    cout << "line1 content: ";
    line1.printSet();
    cout << "line2 content: ";
    line2.printSet();

    // Checking similarity using binary cosine coefficient
    cout << "The similarity between 1 and 2 is \n";
    cout << line1.checkSimilarity(line2) << endl;

    // Testing the addition of string 
    cout << "Adding text\n";
    line2.addStr("and it aids in muscle growth");
    cout << "New content: ";
    line2.printSet();

    // Print the number of words
    cout << "Number of words in line2 is " << line2.strCount();

    // Removing all strings 
    cout << "Cleared\n";
    line2.clearSet();

    // Testing the union of two sets by overloaded + operator
    line2 = line3 + line4;
    cout << "line2 now is the union of line3 and line4!\n";
    cout << "New content: ";
    line2.printSet();

    //  intersection  by overloaded * operator
    StringSet line5 = line1 * line2;
    cout << "line5 is the intersection of line1 and line2!\n";
    cout << "line5 contents: ";
    line5.printSet();

  // remove
    cout << "line2 contents: "; line2.printSet();
    cout << "Removing word from line2\n"; line2.removeStr("Football");
    cout << "New content: "; line2.printSet();
    return 0;
}
