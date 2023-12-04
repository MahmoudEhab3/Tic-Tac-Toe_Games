// File: A3_S1_20220037_Problem1.cpp
// Purpose: Label Generator
// Author: Ahmed Elkholy
// Section: S1
// ID: 20220037
// TA: Khaled Ibrahim
#include <bits/stdc++.h>
using namespace std;
#include <fstream>
class LabelGenerator{
protected:
    string figure;
    int Index;
public:

LabelGenerator(string s,int x) : figure(s),Index(x) {}

virtual string nextLabel(){
    return figure+ to_string(Index++);
}

};

class FileLabelGenerator : public LabelGenerator{
private:
    ifstream file;
public:

    FileLabelGenerator(string s,int x,string filename) : LabelGenerator(s,x) , file(filename){}

    string nextLabel() override{
        string line;
        if(getline(file,line)){
            return LabelGenerator:: nextLabel() + " " + line;
        }else{
            return LabelGenerator::  nextLabel();
        }
    }

};

int main() {
    FileLabelGenerator F1 ("Figure",1,"Test.txt");

    cout<<"File :\n";

    for(int i=0;i<5;i++){
        (i==2) ? cout<<F1.nextLabel(): cout<<F1.nextLabel()<<',';
    }

    cout<<"\n";

    LabelGenerator figureNumbers("Figure ", 1);
    LabelGenerator pointNumbers("P", 0);

    cout << "Figure numbers: ";
    for (int i = 0; i < 5; i++) {
        (i==2) ? cout << figureNumbers.nextLabel() : cout << figureNumbers.nextLabel() << ", " ;
    }

    cout << "\nPoint numbers: ";
    for (int i = 0; i < 5; i++) {
        (i==4) ? cout << pointNumbers.nextLabel() : cout << pointNumbers.nextLabel() << ", ";
    }

    cout << "\nMore figures: ";
    for (int i = 0; i < 3; i++) {
        (i==2) ? cout << figureNumbers.nextLabel() : cout << figureNumbers.nextLabel() << ", ";
    }

    cout << endl;
    return 0;
}
