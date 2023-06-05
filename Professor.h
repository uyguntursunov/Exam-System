#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

using namespace std;

bool registerProf(string *ID);
bool isAlreadyRegisteredProf(string ID);

void showQuestions(string sub);
void file();
void comment();

class Professor {
private:
    
    string name, surname, id, subject;
    
public:
    
    void infoAboutProf(string ID) {
        takeInfoFromFile(ID);
        cout << "ID: " << ID << endl;
        cout << "Name: " << name << " " << surname << endl;
        cout << "Subject: " << subject << endl;
    }
    
    void takeInfoFromFile(string ID) {
        
        ifstream infoFile("ProfessorInformations.txt");
        string checker0;
        
        while(infoFile >> checker0) {
            
            if (checker0 == ID) {
                
                infoFile >> name;
                infoFile >> surname;
                infoFile >> subject;
                break;
            }
        }
        infoFile.close();
    }
    
    void editInfoAboutProf(string *ID) {
        
        string line;
        ifstream infile;
        ofstream outfile;
        infile.open("ProfessorInformations.txt");
        outfile.open("temp.txt");
        
        while(infile) {
            
            getline(infile, line);
            
            if(line == *ID) {
                for(int i = 0; i < 3; i++) {
                    getline(infile, line);
                }
            } else {
                outfile << line << endl;
            }
        }
        infile.close();
        
        rename("temp.txt", "ProfessorInformations.txt");
        remove("temp.txt");
        
        registerProf(&(*ID));
    }
    
    // function for setting up objective questions
    
    bool setupObjectiveQuestions(string ID) {
        
        takeInfoFromFile(ID);
        
        int numQuestions = 0;
        int numOptions = 0;
        
        ifstream infile;
        ofstream outfile;
        infile.open("more.txt");
        outfile.open("temp.txt", ios::app);
        
        string line;
        int numOldQ = 0;
        while(infile) {
            getline(infile,line);
            if(subject == "OOP") {
                if(line == "OOPNofQ") {
                    getline(infile,line);
                    numOldQ = stoi(line);
                    break;
                }
            }else if(subject == "Calculus") {
                if(line == "CalNofQ") {
                    getline(infile,line);
                    numOldQ = stoi(line);
                    break;
                }
            }else if(subject == "Physics") {
                if(line == "PhyNofQ") {
                    getline(infile,line);
                    numOldQ = stoi(line);
                    break;
                }
            }
            
        }
        
        if(numOldQ != 0) {
            cout << "You have entered " << numOldQ << " questions so far" << endl;
            cout << "1. Continue" << endl;
            cout << "2. Delete and start from the beginning" << endl;
            cout << "\n>> ";
            
            int choice1;
            cin >> choice1;
            
            if(choice1 == 1) {
                cout << "Enter number of questions to add: ";
                
            } else if(choice1 == 2) {
                if(subject == "OOP") {
                    ofstream ofs("OOP.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    numOldQ = 0;
                    
                    infile.seekg(0);
                    
                    getline(infile,line);
                    outfile << line << endl;
                    getline(infile,line);
                    outfile << 0 << endl;
                    
                    for(int i = 0; i < 4; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    
                    outfile.close();
                    infile.close();
                    
                    cout << "Enter number of questions: ";
                }else if(subject == "Calculus") {
                    ofstream ofs("Calculus.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    numOldQ = 0;
                    
                    infile.seekg(0);
                    
                    for(int i = 0; i < 3; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    
                    getline(infile,line);
                    outfile << 0 << endl;
                    
                    for(int i = 0; i < 2; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    
                    outfile.close();
                    infile.close();
                    cout << "Enter number of questions: ";
                }else if(subject == "Physics") {
                    ofstream ofs("Physics.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    numOldQ = 0;
                    
                    infile.seekg(0);
                    
                    for(int i = 0; i < 5; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    
                    outfile << 0 << endl;
                    
                    outfile.close();
                    infile.close();
                    cout << "Enter number of questions: ";
                }
                remove("more.txt");
                rename("temp.txt", "more.txt");
            }
        }else {
            cout << "Enter number of questions: ";
        }
        
        cin >> numQuestions;
        numQuestions += numOldQ;
        string line1;
        ifstream inf;
        ofstream outf;
        
        inf.open("more.txt");
        outf.open("temp.txt", ios::app);
        
        while(inf) {
            if(subject == "OOP") {
                getline(inf,line1);
                outf << line1 << endl;
                getline(inf,line1);
                outf << numQuestions << endl;
                
                for(int i = 0; i < 4; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf.close();
                inf.close();
            }else if(subject == "Calculus") {
                for(int i = 0; i < 3; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                getline(inf,line1);
                outf << numQuestions << endl;
                
                for(int i = 0; i < 2; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf.close();
                inf.close();
            }else if(subject == "Physics") {
                for(int i = 0; i < 5; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf << numQuestions << endl;
                
                outf.close();
                inf.close();
            }
            rename("temp.txt", "more.txt");
            remove("temp.txt");
            
            string questions[100], options[100][100], correctAnswers[100];
            for (int i = numOldQ; i < numQuestions; i++) {
                
                cin.ignore();
                
                cout << "Enter question #" << i+1 << ": ";
                getline(cin, questions[i]);
                
                cout << "Enter number of options: ";
                cin >> numOptions;
                
                cin.ignore();
                
                for (int j = 0; j < numOptions; j++) {
                    cout << "Enter option #" << j+1 << ": ";
                    getline(cin, options[i][j]);
                    
                }
                cout << "\nEnter the correct option number: ";
                getline(cin, correctAnswers[i]);
            }
            
            if(subject == "OOP") {
                fstream outfile;
                outfile.open("OOP.txt", ios::app);
                for (int i = numOldQ; i < numQuestions; i++) {
                    
                    outfile << "OQ" << endl;
                    outfile << "Question #" << i + 1 << ": " << questions[i] << endl;
                    for (int j = 0; j < numOptions; j++) {
                        outfile << j+1 << ") " << options[i][j] << " " << endl;
                        
                    }
                    outfile << "xxx" << endl;
                    outfile << correctAnswers[i] << endl;
                }
                outfile.close();
                
                cout << "1. Show questions: " << endl;
                cout << "\n>> ";
                
                int sh;
                cin >> sh;
                if(sh == 1) {
                    showQuestions("OOP");
                    
                    cout << "\n0. Back" << endl;
                    cout << "\n>> ";
                    
                    int b; cin >> b;
                    return false;
                }
            }else if(subject == "Calculus") {
                fstream outfile;
                outfile.open("Calculus.txt", ios::app);
                for (int i = numOldQ; i < numQuestions; i++) {
                    
                    outfile << "OQ" << endl;
                    outfile << "Question #" << i+1 << ": " << questions[i] << endl;
                    for (int j = 0; j < numOptions; j++) {
                        outfile << j+1 << ") " << options[i][j] << " " << endl;
                    }
                    outfile << "xxx" << endl;
                    outfile << correctAnswers[i] << endl;
                }
                outfile.close();
                
                cout << "1. Show questions: " << endl;
                cout << "\n>> ";
                
                int sh;
                cin >> sh;
                if(sh == 1) {
                    showQuestions("Calculus");
                    
                    cout << "\n0. Back" << endl;
                    cout << "\n>> ";
                    int b; cin >> b;
                    return false;
                }
            }else if (subject == "Physics") {
                fstream outfile;
                outfile.open("Physics.txt", ios::app);
                for (int i = numOldQ; i < numQuestions; i++) {
                    
                    outfile << "OQ" << endl;
                    outfile << "Question #" << i+1 << ": " << questions[i] << endl;
                    for (int j = 0; j < numOptions; j++) {
                        outfile << j+1 << ") " << options[i][j] << " " << endl;
                    }
                    outfile << "xxx" << endl;
                    outfile << correctAnswers[i] << endl;
                }
                outfile.close();
                
                cout << "1. Show questions: " << endl;
                cout << "\n>> ";
                int sh;
                cin >> sh;
                if(sh == 1) {
                    showQuestions("Physics");
                    
                    cout << "\n0. Back" << endl;
                    cout << "\n>> ";
                    int b; cin >> b;
                    return false;
                }
            }
        }
        return true;
    }
    
    // function for setting up essay questions
    
    bool setupEssayQuestions(string ID) {
        
        takeInfoFromFile(ID);
        
        int numQuestions = 0;
        
        ifstream infile;
        ofstream outfile;
        string line;
        infile.open("more.txt");
        outfile.open("temp.txt", ios::app);
        int numOldQ = 0;
        
        while(infile) {
            if(subject == "OOP") {
                getline(infile,line);
                if(line == "OOPNofQ") {
                    getline(infile,line);
                    numOldQ = stoi(line);
                    break;
                }
            }else if (subject == "Calculus") {
                getline(infile,line);
                if(line == "CalNofQ") {
                    getline(infile,line);
                    numOldQ = stoi(line);
                    break;
                }
            }else if (subject == "Physics") {
                getline(infile,line);
                if(line == "PhyNofQ") {
                    getline(infile,line);
                    numOldQ = stoi(line);
                    break;
                }
            }
        }
        
        if(numOldQ != 0) {
            cout << "You have entered " << numOldQ << " questions so far" << endl;
            cout << "1. Continue" << endl;
            cout << "2. Delete and start from the beginning" << endl;
            
            int choice2;
            cin >> choice2;
            
            if(choice2 == 1) {
                cout << "Enter number of questions to add: ";
                
            }else if(choice2 == 2) {
                if(subject == "OOP") {
                    ofstream ofs("OOP.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    numOldQ = 0;
                    
                    infile.seekg(0);
                    
                    getline(infile,line);
                    outfile << line << endl;
                    getline(infile,line);
                    outfile << 0 << endl;
                    
                    for(int i = 0; i < 4; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    outfile.close();
                    infile.close();
                    
                    cout << "Enter number of questions: ";
                }else if(subject == "Calculus") {
                    ofstream ofs("Calculus.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    numOldQ = 0;
                    
                    infile.seekg(0);
                    
                    for(int i = 0; i < 3; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    
                    getline(infile,line);
                    outfile << 0 << endl;
                    
                    for(int i = 0; i < 2; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    
                    outfile.close();
                    infile.close();
                    
                    cout << "Enter number of questions: ";
                }else if(subject == "Physics") {
                    ofstream ofs("Physics.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    numOldQ = 0;
                    
                    infile.seekg(0);
                    
                    for(int i = 0; i < 5; i++) {
                        getline(infile,line);
                        outfile << line << endl;
                    }
                    
                    outfile << 0 << endl;
                    
                    outfile.close();
                    infile.close();
                    
                    cout << "Enter number of questions: ";
                }
                remove("more.txt");
                rename("temp.txt", "more.txt");
                
            }
        }else {
            cout << "Enter number of questions: ";
        }
        
        cin >> numQuestions;
        numQuestions += numOldQ;
        string line1;
        ifstream inf;
        ofstream outf;
        
        inf.open("more.txt");
        outf.open("temp.txt", ios::app);
        
        while(inf) {
            if(subject == "OOP") {
                
                getline(inf,line1);
                outf << line1 << endl;
                getline(inf,line1);
                outf << numQuestions << endl;
                
                for(int i = 0; i < 4; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf.close();
                inf.close();
            }else if(subject == "Calculus") {
                
                for(int i = 0; i < 3; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                getline(inf,line1);
                outf << numQuestions << endl;
                
                for(int i = 0; i < 2; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf.close();
                inf.close();
            }else if(subject == "Physics") {
                
                for(int i = 0; i < 5; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf << numQuestions << endl;
                
                outf.close();
                inf.close();
            }
        }
        remove("more.txt");
        rename("temp.txt", "more.txt");
        
        
        string questions[100], correctAnswers[100];
        
        for(int i = numOldQ; i < numQuestions; i++) {
            
            cin.ignore();
            
            cout << "Enter question #" << i+1 << ": ";
            getline(cin, questions[i]);
            
            cout << "\nEnter the correct answer: ";
            getline(cin, correctAnswers[i]);
        }
        
        
        if(subject == "OOP") {
            fstream outfile;
            outfile.open("OOP.txt", ios::app);
            for (int i = numOldQ; i < numQuestions; i++) {
                
                outfile << "EQ" << endl;
                outfile << "Question #" << i + 1 << ": " << questions[i] << endl;
                outfile << correctAnswers[i]<< endl;
            }
            outfile.close();
            
            cout << "1. Show questions: " << endl;
            cout << "\n>> ";
            
            int sh;
            cin >> sh;
            if(sh == 1) {
                showQuestions("OOP");
                
                cout << "\n0. Back" << endl;
                cout << "\n>> ";
                
                int b; cin >> b;
                return false;
            }
            
        }else if(subject == "Calculus") {
            
            fstream outfile;
            outfile.open("Calculus.txt", ios::app);
            for (int i = numOldQ; i < numQuestions; i++) {
                
                outfile << "EQ" << endl;
                outfile << "Question #" << i+1 << ": " << questions[i] << endl;
                outfile << correctAnswers[i]<< endl;
            }
            outfile.close();
            
            cout << "1. Show questions: " << endl;
            cout << "\n>> ";
            
            int sh;
            cin >> sh;
            if(sh == 1) {
                showQuestions("Calculus");
                
                cout << "\n0. Back" << endl;
                cout << "\n>> ";
                
                int b; cin >> b;
                return false;
            }
        }else if (subject == "Physics") {
            fstream outfile;
            outfile.open("Physics.txt", ios::app);
            for (int i = numOldQ; i < numQuestions; i++) {
                
                outfile << "EQ" << endl;
                outfile << "Question #" << i+1 << ": " << questions[i] << endl;
                outfile << correctAnswers[i]<< endl;
            }
            outfile.close();
            
            cout << "1. Show questions: " << endl;
            cout << "\n>> ";
            
            int sh;
            cin >> sh;
            if(sh == 1) {
                showQuestions("Physics");
                
                cout << "\n0. Back" << endl;
                cout << "\n>> ";
                
                int b; cin >> b;
                return false;
            }
        }
        
        return false;
    }
    
    // function for randomly selecting from large pool of questions
    
    bool selectRandomly(string ID) {
        
        takeInfoFromFile(ID);
        
        ifstream infl("more.txt");
        string checker;
        int numOldQ = 0;
        
        while(infl) {
            if(subject == "OOP") {
                getline(infl, checker);
                if(checker == "OOPNofQ") {
                    getline(infl, checker);
                    numOldQ = stoi(checker);
                    break;
                }
            }else if (subject == "Calculus") {
                getline(infl, checker);
                if(checker == "CalNofQ") {
                    getline(infl,checker);
                    numOldQ = stoi(checker);
                    break;
                }
            }else if (subject == "Physics") {
                getline(infl, checker);
                if(checker == "PhyNofQ") {
                    getline(infl, checker);
                    numOldQ = stoi(checker);
                    break;
                }
            }
        }
        
        string filename;
        if(subject == "OOP") {
            filename = "OOPquestions.txt";
        }else if(subject == "Calculus") {
            filename = "Calculusquestions.txt";
        }else if(subject == "Physics") {
            filename = "Physicsquestions.txt";
        }
        
        string filename1;
        if(subject == "OOP") {
            filename1 = "OOP.txt";
        }else if(subject == "Calculus") {
            filename1 = "Calculus.txt";
        }else if(subject == "Physics") {
            filename1 = "Physics.txt";
        }
        
        string line;
        string answer;
        string isMultipleChoice;
        
        ifstream infile;
        ofstream outfile;
        
        infile.open(filename);
        outfile.open(filename1, ios::app);
        cout << "Enter number of selection: " << endl;
        cout << "\n>> ";
        int countRandomQues;
        cin >> countRandomQues;
        int numQuestions = countRandomQues;
        numQuestions += numOldQ;
        
        string line1;
        ifstream inf;
        ofstream outf;
        
        inf.open("more.txt");
        outf.open("temp.txt", ios::app);
        
        while(inf) {
            if(subject == "OOP") {
                
                getline(inf,line1);
                outf << line1 << endl;
                getline(inf,line1);
                outf << numQuestions << endl;
                
                for(int i = 0; i < 4; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf.close();
                inf.close();
            }else if(subject == "Calculus") {
                
                for(int i = 0; i < 3; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                getline(inf,line1);
                outf << numQuestions << endl;
                
                for(int i = 0; i < 2; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf.close();
                inf.close();
            }else if(subject == "Physics") {
                
                for(int i = 0; i < 5; i++) {
                    getline(inf,line1);
                    outf << line1 << endl;
                }
                
                outf << numQuestions << endl;
                
                outf.close();
                inf.close();
            }
        }
        remove("more.txt");
        rename("temp.txt", "more.txt");
        
        int countRandom = 0;
        int random_num;
        
        bool* usedQuestions = new bool[1000]; // initialize array to keep track of used questions
        for(int i = 0; i < 1000; i++) {
            usedQuestions[i] = false;
        }
        
        while(countRandomQues != 0) {
            countRandom += 1;
            srand(time(NULL)); // seed the random number generator with the current timeI
            
            do {
                random_num = (rand() % 25) + 1; // generate a random number between 1 and 25
            } while(usedQuestions[random_num]); // continue generating random numbers until an unused one is found
            usedQuestions[random_num] = true;
            infile.seekg(0, ios::beg);
            int countQues = 0; // Reset the question counter
            
            while(infile) {
                
                getline(infile, line);
                countQues += 1;
                if(line == "OQ") {
                    if(random_num == countQues) {
                        outfile << line << endl;
                    }
                    getline(infile, line);
                    if(random_num == countQues) {
                        
                        outfile << "Question #" << (numOldQ + countRandom) << ". " << line << endl;
                    }
                    int count = 0;
                    getline(infile, line);
                    while(line != "xxx") {
                        count += 1;
                        if(random_num == countQues) {
                            outfile << count << ". " << line << endl;
                        }
                        getline(infile, line);
                    }if(random_num == countQues) {
                        outfile << line << endl;
                    }
                    getline(infile, line);
                    string correctAnswer = line;
                    if(random_num == countQues) {
                        outfile << correctAnswer << endl;
                    }
                } else if (line == "EQ") {
                    if(random_num == countQues) {
                        outfile << line << endl;
                    }
                    getline(infile, line);
                    if(random_num == countQues) {
                        
                        outfile << "Question #" << (numOldQ + countRandom) << ". " << line << endl;
                    }
                    getline(infile, line);
                    string answer = line;
                    if(random_num == countQues) {
                        outfile << answer << endl;
                    }
                }
            }
            
            if (infile.eof()) {
                infile.clear(); // clear the end-of-file flag and other error flags
                infile.seekg(0, ios::beg); // reset the file pointer to the beginning of the file
            }
            countRandomQues -= 1;
        }
        
        infile.close();
        outfile.close();
        
        cout << "1. Show questions" << endl;
        cout << "\n>> ";
        int b; cin >> b;
        showQuestions(subject);
        return false;
    }
    
    void setTimer() {
        
        float timer;
        
        cout << "\nEnter the duration of the Exam(minutes): " << endl;
        cout << ">> ";
        cin >> timer;
        
        ofstream outfile("Timer.txt");
        
        outfile << timer;
        outfile.close();
    }
    
    bool viewResults(string ID) {
        takeInfoFromFile(ID);
        
        string filename;
        if(subject == "OOP") {
            filename = "OOPresults.txt";
        }else if(subject == "Calculus") {
            filename = "Calculusresults.txt";
        }else if(subject == "Physics") {
            filename = "Physicsresults.txt";
        }
        
        string line;
        ifstream infile(filename);
        while(getline(infile, line)) {
            
            if(line.length() == 8) {
                cout << "ID: " << line << endl;
            }else {
                cout << "Result: " << line << endl;
            }
        }
        infile.close();
        
        cout << "1. Leaving a comment" << endl;
        cout << "\n>> ";
        
        int b;
        cin >> b;
        
        if(b == 1) {
            string comment;
            
            cout << "Write your comment: " << endl;
            cin.ignore();
            getline(cin, comment);
            ofstream outfile("Comments.txt", ios::app);
            outfile << comment << endl;
            outfile.close();
        
        }else {
            return false;
        }
        cout << "\n0. Back" << endl;
        cout << "\n>> ";
        
        int e; cin >> e;
        
        
        return false;
    }
    
};

void file() {
    
    ofstream file;
    file.open("more.txt");
    
    file << "OOPNofQ" << endl;
    file << 0 << endl;
    file << "CalNofQ" << endl;
    file << 0 << endl;
    file << "PhyNofQ" << endl;
    file << 0 << endl;
    
    file.close();
}
void showQuestions(string sub) {
    
    string filename;
    if(sub == "OOP") {
        filename = "OOP.txt";
    }else if (sub == "Calculus") {
        filename = "Calculus.txt";
    }else if (sub == "Physics") {
        filename = "Physics.txt";
    }
    
    string line;
    string answer;
    string isMultipleChoice;
    
    ifstream infile(filename);
    int coutQues = 0;
    
    while(infile) {
        getline(infile, line);
        coutQues += 1;
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
            cout << "Answer: " << correctAnswer << endl << endl;
        } else if (line == "EQ"){
            getline(infile, line);
            cout << line << endl;
            getline(infile, line);
            string answer = line;
            cout << "Answer: " << answer << endl << endl;
        }
    }
    
    infile.close();
}

// function for registering professor

bool registerProf(string *ID) {
    
    Professor p;
    string name;
    string surname;
    string subject;
    string userID;
    
labelY:
    cout << "Enter new informations: " << endl;
    cout << "ID: "; cin >> userID;
    
    if(isAlreadyRegisteredProf(userID)) {
        
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
    
    cout << "Subject: ";
    cout << "\n1.Calculus\t2.OOP\t3.Physics" << endl;
    cout << "\n>> ";
    int optionx;
    while(true) {
        
        cin >> optionx;
        if(optionx == 1){
            
            subject = "Calculus";
            
            break;
        }else if(optionx == 2) {
            
            subject = "OOP";
            break;
        }else if(optionx == 3){
            
            subject = "Physics";
            break;
        }else{
            cout << "Try again!" << endl;
        }
        
    }
    
    ofstream outFile("ProfessorInformations.txt", ios::app);
    outFile << userID << endl;
    outFile << name << endl;
    outFile << surname << endl;
    outFile << subject << endl;
    
    outFile.close();
    return false;
}

bool isAlreadyRegisteredProf(string ID) {
    string line;
    ifstream infile;
    infile.open("ProfessorInformations.txt");
    
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




