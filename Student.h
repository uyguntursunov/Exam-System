#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <cmath>
#include "Person.h"
#include <chrono>
//#include "Timer.h"

bool registerStudent(string *ID);
bool isAlreadyRegisteredStudent(string ID);

class Student : public Person {
    
private:
    string name, surname;
    
public:
    
    void infoAboutStudent(string ID) {
        takeInfoFromFile(ID);
        cout << "ID: " << ID << endl;
        cout << "Name: " << name << " " << surname << endl;
    }
    
    void takeInfoFromFile(string ID) {
        
        ifstream infoFile("StudentInformations.txt");
        string checker1;
        
        while(infoFile >> checker1) {
            
            if (checker1 == ID) {
                
                infoFile >> name;
                infoFile >> surname;
                break;
            }
        }
        infoFile.close();
    }
    
    void editInfoAboutStudent(string *ID) {
        
        string line;
        ifstream infile;
        ofstream outfile;
        infile.open("StudentInformations.txt");
        outfile.open("temp.txt");
        
        while(infile) {
            
            getline(infile, line);
            
            if(line == *ID) {
                for(int i = 0; i < 2; i++) {
                    getline(infile, line);
                }
            } else {
                outfile << line << endl;
            }
        }
        infile.close();
        
        rename("temp.txt", "StudentInformations.txt");
        remove("temp.txt");
        
        registerStudent(&(*ID));
    }
    
    // function for taking an exam
    
    bool test(string ID) {
        
        takeInfoFromFile(ID);
        
        cout << "Subject: ";
        cout << "\n1.OOP\t2.Calculus\t3.Physics" << endl;
        cout << "\n>> ";
        int s; cin >> s;
        
        string filename;
        string filename1;
        
        if(s == 1) {
            filename = "OOP.txt";
            filename1 = "OOPresults.txt";
        }else if(s == 2) {
            filename = "Calculus.txt";
            filename1 = "Calculusresults.txt";
        }else if (s == 3) {
            filename = "Physics.txt";
            filename1 = "Physicsresults.txt";
        }
        
        string line;
        string answer;
        string isMultipleChoice;
        
        ifstream infile(filename);
        float countQues = 0;
        float point = 0;
        
        chrono::time_point<chrono::system_clock> start_time;
        start_time = chrono::system_clock::now();
        
        while(infile) {
            
            ifstream timefile("Timer.txt");
            string linet;
            getline(timefile, linet);
            float timer = stof(linet);
            
            getline(infile, line);
            countQues += 1;
            if(line == "OQ") {
                getline(infile, line);
                cout << line << endl;
                int count = 0;
                getline(infile, line);
                while(line != "xxx") {
                    count += 1;
                    cout << line << endl;
                    getline(infile, line);
                }
                getline(infile, line);
                string correctAnswer = line;
                
                cout << "\nEnter the correct answer number: ";
                cin >> answer;
                
                // if (!answer.empty()) {
                if(correctAnswer == answer) {
                    point += 1;
                    cout << "\nCorrect!" << endl;
                } else {
                    cout << "\nIncorrect!" << endl;
                }
                // }
                
            } else if (line == "EQ"){
                getline(infile, line);
                cout << line << endl;
                getline(infile, line);
                string answer = line;
                string userAnswer;
                
                cout << "\nEnter the answer: ";
                cin >> userAnswer;
                if(answer == userAnswer) {
                    point += 1;
                    cout << "\nCorrect!" << endl;
                } else {
                    cout << "\nIncorrect!" << endl;
                }
            }
            
            chrono::time_point<chrono::system_clock> end_time;
            end_time = chrono::system_clock::now();
            chrono::duration<double> elapsed_time;
            elapsed_time = chrono::duration_cast<chrono::seconds>(end_time - start_time);
            
            
            if (elapsed_time.count() >= timer*60)
            {
                cout << timer*60 << " seconds have passed. Time is over!" << endl;
                break;
            }
            
        }
        
        chrono::time_point<chrono::system_clock> end_time;
        end_time = chrono::system_clock::now();
        chrono::duration<double> elapsed_time;
        elapsed_time = chrono::duration_cast<chrono::seconds>(end_time - start_time);
        cout << "You spent " << elapsed_time.count() << " seconds!" << endl;
        
        float percentage = round((point / float(countQues - 1)) * 1000.0)/10.0;
        
        ofstream outf(filename1, ios::app);
        outf << ID << endl;
        outf << point << "/" << (countQues - 1)  << " (" << float(percentage) << "%)" << endl;
        
        outf.close();
        
        
        infile.close();
        
        cout << "\n0. Back" << endl;
        cout << "\n>> ";
        int b;
        cin >> b;
        return false;
    }
    
    // function for viewing results
    
    bool viewResults(string ID) {
        takeInfoFromFile(ID);
        
        cout << "1. OOP" << endl;
        cout << "2. Calculus" << endl;
        cout << "3. Physics" << endl;
        cout << "\n>> ";
        
        int s; cin >> s;
        
        string filename1;
        
        if(s == 1) {
            filename1 = "OOPresults.txt";
        }else if(s == 2) {
            filename1 = "Calculusresults.txt";
        }else if (s == 3) {
            filename1 = "Physicsresults.txt";
        }
        
        ifstream inf(filename1);
        string line;
        
        while(line != ID) {
            getline(inf, line);
        }
        getline(inf, line);
        inf.close();
        
        cout << "Your result: " << line << endl;
        cout << "\n0. Back" << endl;
        cout << "\n>> ";
        
        int b;
        cin >> b;
        
        return false;
    }
    
    // function for view comments
    void viewComments() {
        ifstream infile("Comments.txt");
        string line;
        while(getline(infile, line)) {
            cout << line << endl;
        }
    }
    
};

// function for registering student

bool registerStudent(string *ID) {
    
    string name;
    string surname;
    string userID;
    
labelY:
    cout << "Enter new informations: " << endl;
    cout << "ID: "; cin >> userID;
    
    if(isAlreadyRegisteredStudent(userID)) {
        
        cout << "1. Try again\n2. Log In" << endl;
        cout << "\n>> ";
        
        int f;
        cin >> f;
        if(f == 1){
            goto labelY;
        }else{
            return true;
        }
    }
    
    
    *ID = userID;
    cout << "Name: ";   cin >> name;
    cout << "Surname: "; cin >> surname;
    
    ofstream outFile("StudentInformations.txt", ios::app);
    outFile << userID << endl;
    outFile << name << endl;
    outFile << surname << endl;
    
    outFile.close();
    return false;
}

bool isAlreadyRegisteredStudent(string ID) {
    string line;
    ifstream infile;
    infile.open("StudentInformations.txt");
    
    while(infile)
    {
        getline(infile,line);
        if(line == ID){
            cout << "You have already registered!" << endl;
            return true;
        }
    }
    infile.close();
    return false;
}

