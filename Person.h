#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

class Person {
    
protected:
    
    string id, password;
    
public:
    
    void setID(string id) {
        this -> id = id;
    }
    
    void setPassword(string password) {
        this -> password = password;
    }
    
    void setData() {
        cout << "Enter ID: "; cin >> id;
        cout << "Enter password: "; cin >> password;
    }
    
    void getData() {
        cout << "ID: " << id << endl << "Password: " << password << endl;
    }
    
    string getID() {
        return id;
    }
    
    string getPassword() {
        return password;
    }
};
