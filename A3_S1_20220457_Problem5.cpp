// File: A3_S1_20220457_Problem5.cpp
// Purpose: Task Manager
// Author: Mahmoud Ehab
// Section: S1
// ID: 20220457
// TA: Khaled Ibrahim

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// Class for each process and its (name, PID, memory used)
class process{
protected:
    string name;
    int PID;
    string memory;
public:
    // Constructor that takes process members
    process(string n, int p, string m){
        name = n;
        PID = p;
        memory = m;
    }

    // Getters
    string getMemory(){
        return memory;
    }
    int getID(){
        return PID;
    }
    string getName(){
        return name;
    }
};

// Class to manage running processes
class taskManager{
protected:
    vector<process> tasks;
public:

    // Constructor that stores process into vector
    void addProcess(process p){
        tasks.push_back(p);
    }

    // Function that displays all processes in tasks
    void print(){
        cout << left << setw(35) << "Program Name";
        cout << right << setw(10)<< "PID";
        cout << right << setw(15) << "MemoryUsed"<< endl;
        for(auto i : tasks){
            cout << left << setw(35) << i.getName();
            cout << right << setw(10)<< i.getID();
            cout << right << setw(15) << i.getMemory() << "K" << endl;
        }
    }

    // Function that gets all current processes and stores them in tasks
    void getCurrentTasks(){

        // Command to get all running processes and store them in text file
        system("tasklist > tasks.txt");
        ifstream file("tasks.txt"); // opening file
        string line;
        string trash;
        // ignoring first 3 lines
        getline(file, line);
        getline(file, line);
        getline(file, line);
        // using stringstream to get each word
        while(getline(file, line)){
            string name, memory;
            int id;
            // getting process name and removing extra spaces
            name = line.substr(0, 25);
            while(name.back() == ' '){
                name.pop_back();
            }
            line = line.substr(25, line.length() - 1); // removing name from line
            stringstream ss(line);

            // Getting PID and memory from line and neglecting other elements
            ss >> id >> trash >> trash >> memory;
            process p(name, id, memory); // creating process object
            addProcess(p); // adding process to tasks
        }
    }


    // Function that sorts tasks
    void sort_by_memory(){
            sort(tasks.begin(), tasks.end(), [](process a, process b){
                if(a.getMemory().size() > b.getMemory().size()){
                    return true;
                }
                else if(a.getMemory().size() == b.getMemory().size()){
                    return a.getMemory() > b.getMemory();
                }
                return false;
            });
        }



};

int main(){
    taskManager tm;
    tm.getCurrentTasks();
    tm.sort_by_memory();
    tm.print();
}
