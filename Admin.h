#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

bool registerAdmin(string *ID);
bool isAlreadyRegisteredAdmin(string ID);

class Admin {
    
private:
    string name, surname;
    
public:
    
    void infoAboutAdmin(string ID) {
        takeInfoFromFile(ID);
        cout << "ID: " << ID << endl;
        cout << "Name: " << name << " " << surname << endl;
    }
    
    void takeInfoFromFile(string ID) {
        
        ifstream infoFile("AdminInformations.txt");
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
    
// function for publishing test results and summary
    
    bool publishResults() {
        
        cout << "OOP exam results: " << endl;
        
        string line1;
        ifstream infile1("OOPresults.txt");
        while(getline(infile1, line1)) {
            
            if(line1.length() == 8) {
                cout << "ID: " << line1 << endl;
            }else {
                cout << "Result: " << line1 << endl;
            }
        }
        
        cout << "Calculus exam results: " << endl;
        
        string line2;
        ifstream infile2("Calculus");
        while(getline(infile2, line2)) {
            
            if(line2.length() == 8) {
                cout << "ID: " << line2 << endl;
            }else {
                cout << "Result: " << line2 << endl;
            }
        }
        
        cout << "Physics exam results: " << endl;
        
        string line3;
        ifstream infile3("Calculus");
        while(getline(infile3, line3)) {
            
            if(line2.length() == 8) {
                cout << "ID: " << line3 << endl;
            }else {
                cout << "Result: " << line3 << endl;
            }
            
        }
        cout << "\n0. Back" << endl;
        cout << "\n>> ";
        int b;
        cin >> b;
        
        return false;
    }
    
// function for showing information about registered professors or students
    
    bool showInfo() {
        
        cout << "1. Professors" << endl;
        cout << "2. Students" << endl;
        cout << "\n>> ";
        
        int p; cin >> p;
        if(p == 1) {
            cout << "Registered professors: " << endl;
            
            string line1;
            ifstream infile1("ProfessorInformations.txt");
            while(infile1) {
                getline(infile1, line1);
                if(line1 == "") {
                    break;
                }
                cout << "ID: " << line1 << endl;
                getline(infile1, line1);
                cout << "Name: " << line1 << endl;
                getline(infile1, line1);
                cout << "Surname: " << line1 << endl;
                getline(infile1, line1);
                cout << "Subject: " << line1 << endl;
                
            }
        }else if(p == 2) {
            cout << "Registered students: " << endl;
            
            string line2;
            ifstream infile2("StudentInformations.txt");
            while(infile2) {
                getline(infile2, line2);
                if(line2 == "") {
                    break;
                }
                cout << "ID: " << line2 << endl;
                getline(infile2, line2);
                cout << "Name: " << line2 << endl;
                getline(infile2, line2);
                cout << "Surname: " << line2 << endl;
                
            }
        }
        cout << "\n0. Back" << endl;
        cout << "\n>> ";
        int b; cin >> b;
        return false;
    }
    
};

// function for registering admin

bool registerAdmin(string *ID) {
    
    string name;
    string surname;
    string userID;
    
labelY:
    cout << "Enter new informations: " << endl;
    cout << "ID: "; cin >> userID;
    
    if(isAlreadyRegisteredAdmin(userID)) {
        
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
    
    ofstream outFile("AdminInformations.txt", ios::app);
    outFile << userID << endl;
    outFile << name << endl;
    outFile << surname << endl;
    
    outFile.close();
    return false;
}

bool isAlreadyRegisteredAdmin(string ID) {
    
    string line;
    ifstream infile;
    infile.open("AdminInformations.txt");
    
    while(infile)
    {
        getline(infile,line);
        if(line == ID) {
            cout << "You have already registered!" << endl;
            return true;
        }
    }
    infile.close();
    return false;
}

