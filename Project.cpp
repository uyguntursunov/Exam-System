#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <string>
#include "Student.h"
#include "Professor.h"
#include "Admin.h"
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

void print();

// function for checking logIn
bool loggedInSuccesfully(string* userID) {
    Person per;
    
    ifstream infile;
    infile.open("Person.dat", ios::in | ios::binary);
    
    for(char c : "Enter ID: ") {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    string id;
    cin >> id;
    *userID = id;
    
    for(char c : "Enter password: ") {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    string password;
    cin >> password;
    
    infile.seekg(0);
    
    while(infile.read((char *)&per, sizeof(per)))
    {
        if (per.getID() == id && per.getPassword() == password)
        {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}

// function for register or login

string enteringSystem() {
    
    string userID;
    
label1:
    for(char c : "1. Register") {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    cout << endl;
    
    for(char c : "2. Log in") {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    cout << endl;
    
    for(char c : "0. Exit") {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    cout << endl;
    cout << "\n>> ";
    
    int choice;
    cin >> choice;
    
    while(1) {
        if(choice == 1) {
            while(true) {
                string id;
                cout << "\nChoose one: " << endl;
                cout << "1. Student" << endl;
                cout << "2. Professor" << endl;
                cout << "3. Administrator" << endl;
                cout << "\n>> ";
                
                int choice0;
                cin >> choice0;
                
                cout << "\nPlease, note that Student has 8 symbols in ID, Professor has 4 symbols in ID and Admin has 3 symbols in ID\n" << endl;
                
                if(choice0 == 1) {
                    
                    if(registerStudent(&id) == true) {
                        goto label1;
                    }
                }else if(choice0 == 2){
                    if(registerProf(&id) == true) {
                        goto label1;
                    }
                }else {
                    if(registerAdmin(&id) == true) {
                        goto label1;
                    }
                }
                cout << "\nPlease, enter new password: ";
                string password;
                cin >> password;
                
                Person per;
                fstream f;
                per.setID(id);
                per.setPassword(password);
                per.getData();
                f.open("Person.dat", ios::in | ios::out | ios::ate | ios::binary);
                f.write((char *)&per, sizeof(per));
                f.close();
                cout << "You registered succesfully!" << endl;
                goto label1;
                break;
            }
            
        }else if(choice == 2) {
            while(true) {
                if(loggedInSuccesfully(&userID)) {
                    cout << "You logged in successfully!" << endl;
                    break;
                }else {
                    cout << "\n\nWrong ID or Password. Please, try again!\n" << endl;
                    int a;
                    cout << "1. Enter again" << endl;
                    cout << "0. Back" << endl;
                    cout << "\n>> ";
                    
                    cin >> a;
                    if(a == 0) {
                        return enteringSystem();
                    }
                }
            }
            break;
        }else if(choice == 0) {
            exit(0);
        }
        
    }
    return userID;
}

// function for Main Menu

string mainMenu() {
    string userID;
    int control;
label2:
    for(char c : "1. Entering the Exam System") {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    cout << endl;
    
    for(char c : "0. Quit program") {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
    cout << "\n>> ";
    
    cin >> control;
    if(control == 1) {
        
        userID = enteringSystem();
    }
    
    return userID;
}

int main() {
    
    print();
    
mainLabel:
    string userID = mainMenu();
    //system("clear");
    if(userID.length() == 8) {
        
        Student student;
        
    labels:
        cout << "\n1. Show informations" << endl;
        cout << "2. Try exam" << endl;
        cout << "3. View results" << endl;
        cout << "4. View comments" << endl;
        cout << "0. Log out" << endl;
        cout << "\n>> ";
        
        int option0;
        int options;
        while(1) {
            cin >> option0;
            
            switch (option0) {
                case 1:
                {
                    student.infoAboutStudent(userID);
                    cout << "\n1. Edit info" << endl;
                    cout << "\n0. Back" << endl;
                    cout << "\n>> ";
                    cin >> options;
                    if(options == 0) {
                        goto labels;
                    }else if(options == 1) {
                        student.editInfoAboutStudent(&userID);
                        cout << "\n0. Back" << endl;
                        cout << "\n>> ";
                        int g; cin >> g;
                        if(g == 0) {
                            goto labels;
                        }
                        break;
                    }
                }
                    break;
                    
                case 2:
                    
                    student.test(userID);
                    goto labels;
                    break;
                    
                case 3:
                    student.viewResults(userID);
                    goto labels;
                    break;
                    
                case 4:
                    student.viewComments();
                    goto labels;
                    break;
                case 0:
                    goto mainLabel;
                    
                default:
                    break;
            }
        }
    }
    else if(userID.length() == 4) {
        
        Professor prof;
        
    labelp:
        cout << "\n1. Show informations" << endl;
        cout << "2. Set up tests" << endl;
        cout << "3. View and grade results" << endl;
        cout << "0. Log out" << endl;
        cout << "\n>> ";
        
        int option;
        int option1;
        
        while (1) {
            
            cin >> option;
            
            switch (option) {
                case 1:
                {
                    prof.infoAboutProf(userID);
                    cout << "\n1. Edit info" << endl;
                    cout << "\n0. Back" << endl;
                    cout << "\n>> ";
                    cin >> option1;
                    if(option1 == 0) {
                        goto labelp;
                    }else if(option1 == 1) {
                        prof.editInfoAboutProf(&userID);
                        cout << "\n0. Back" << endl;
                        cout << "\n>> ";
                        int g; cin >> g;
                        if(g == 0) {
                            goto labelp;
                        }
                        break;
                    }
                }
                    break;
                    
                case 2:
                {
                label2:
                    cout << "\n1. Set up tests with objective questions" << endl;
                    cout << "2. Set up tests with essay questions" << endl;
                    cout << "3. Select randomly from large pool of questions" << endl;
                    cout << "4. Set a timer" << endl;
                    cout << "\n0. Back" << endl;
                    cout << "\n>> ";
                    int optionq;
                    cin >> optionq;
                    
                    if(optionq == 1) {
                        
                        prof.setupObjectiveQuestions(userID);
                        goto label2;
                    }else if(optionq == 2) {
                        
                        prof.setupEssayQuestions(userID);
                        goto label2;
                    }else if(optionq == 3) {
                        prof.selectRandomly(userID);
                        goto label2;
                    }else if(optionq == 4) {
                        prof.setTimer();
                        goto label2;
                    }else {
                        goto labelp;
                    }
                }
                    break;
                    
                case 3:
                    prof.viewResults(userID);
                    goto labelp;
                    break;
                    
                case 0:
                {
                    goto mainLabel;
                }
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    if(userID.length() == 3) {
        
        Admin admin;
        
    labela:
        cout << "\n1. Show informations" << endl;
        cout << "2. Registered professors and students" << endl;
        cout << "3. Publish test results and summary" << endl;
        cout << "0. Log out" << endl;
        cout << "\n>> ";
        
        int option;
        int optiona;
        
        while(1) {
            cin >> option;
            
            switch (option) {
                case 1:
                {
                    admin.infoAboutAdmin(userID);
                    cout << "\n 0. Back" << endl;
                    cout << "\n>> ";
                    
                    cin >> optiona;
                    if(optiona == 0) {
                        goto labela;
                    }
                }
                    break;
                    
                case 2:
                    admin.showInfo();
                    goto labela;
                    break;
                    
                case 3:
                    admin.publishResults();
                    goto labela;
                    break;
                case 0:
                {
                    goto mainLabel;
                }
                    
                default:
                    break;
            }
        }
        
    }
    return 0;
}

void print() {
    
    cout << "               ***********************************" << endl;
    cout << "               *  ____ ____ ____ ____ ____ ____  *" << endl;
    cout << "               * ||  |||I |||N |||H |||A  |||  ||*" << endl;
    cout << "               * ||__|||__|||__|||__|||__|||__|| *" << endl;
    cout << "               * |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\| *" << endl;
    cout << "               *  ____ ____ ____ ____ ____ ____  *" << endl;
    cout << "               * ||  |||E |||X |||A |||M |||  || *" << endl;
    cout << "               * ||__|||__|||__|||__|||__|||__|| *" << endl;
    cout << "               * |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\| *" << endl;
    cout << "               *  ____ ____ ____ ____ ____ ____  *" << endl;
    cout << "               * ||S |||Y |||S |||T |||E |||M  ||*" << endl;
    cout << "               * ||__|||__|||__|||__|||__|||__|| *" << endl;
    cout << "               * |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\| *" << endl;
    cout << "               ***********************************" << endl;
    for(int i = 0; i < 5; i++) {
        cout << endl;
    }
}

