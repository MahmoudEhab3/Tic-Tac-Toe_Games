// File: A3_S2_20230607_Problem3.cpp
// Purpose: Count words of a document
// Author: Mazen Abdelfattah
// Section: S2
// ID: 20230607
// TA: Khaled Ibrahim

#include <bits/stdc++.h>
using namespace std;

vector<string> splitstring(string &s) //You can do it with for loop, but it's more professional
{
    vector<string> words;
    istringstream iss(s); //Helps in extracting individual words  from a string
    string word;

    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}

int main() {

    ifstream fin("test_in.txt");
    ofstream fout("test_out.txt");
    map<string,int> mapOfWords;
    string s;
    getline(fin,s);
    for (int i = 0; i < s.size(); ++i) {
        if(s[i]==',' || s[i]=='.' || s[i]==';' || s[i]=='?')
        {
            replace(s.begin(),s.end(),s[i],' ');
        }
    }
    vector <string> words = splitstring(s);

    for (const auto &word: words) {
            mapOfWords[word]++;
    }

    for (const auto &it: mapOfWords) {
        fout<<it.first<<":"<<it.second<<"\n";
    }
    
    fin.close();
    fout.close();
    
}
